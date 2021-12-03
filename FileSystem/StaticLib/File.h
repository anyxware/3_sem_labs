#pragma once

#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include "Map.h"
#include "FileSystem.h"
#include "BaseStructs.h"
#include "DiskIO.h"

class FileSystem;

struct INode
{
	time_t createTime;
	time_t modifyTime;
	uid UID;
	gid GID;
	bool mode[10]; // drwxrwxrwx mode[0] = true if dir
	size_t size; // file size
	size_t address;
	size_t externAddresses[8]; // 6 direct and 2 indirect
	size_t parentAddress; // parent directory descriptor adress in filesystem
	size_t hash;
	std::string name;

	size_t read(std::fstream& disk);
	size_t write(std::fstream& disk);
};

class FileSystem;

class Entry
{
private:
	INode inode;
	size_t inodeSize; // content % BLOCK_SZ is equal to inode size
	FileSystem& fs;
protected:
	size_t BLOCK_SZ = 1024;

	// get-set
	size_t getMaxSize();
	size_t getSize() { return inode.size; }
	void setSize(size_t newSize) { inode.size = newSize; }
	void incrSize(size_t size) { inode.size += size; }
	void decrSize(size_t size) { inode.size -= size; }
	size_t getAddress() { return inode.address; }
	size_t getInodeSize() { return inodeSize; }
	void modifyTime() { inode.modifyTime = time(nullptr); }

	size_t freeAddress(size_t curSize); // get external address and put it to free map
	size_t takeAddress(size_t curSize); // put address to external adresses from free map

	size_t getAddress(size_t position); // get external address
	//size_t putAddress(size_t curSize); // put address to external adresses

	// read-write
	std::string readName(size_t fileAddress);
	void read(size_t address, char* buffer, size_t BUF_SZ);
	void write(size_t address, const char* buffer, size_t BUF_SZ);

	// working with blocks
	size_t getBlock(); // get free block from fs
	void putBlock(size_t address); // put block to free map

	void writeInode();

public:
	Entry(const INode& inode, FileSystem& fs);
	Entry(size_t inodeAddress, FileSystem& fs);
	virtual ~Entry() {};

	size_t getParent() { return inode.parentAddress; }

	void name(std::string& out) {
		std::cout << inode.name << (inode.mode[0] ? "/" : "");
		out += inode.name + (inode.mode[0] ? "/" : "");
	}
	bool type() { // true if dir
		return inode.mode[0];
	}
	void remove();
};

class File : public Entry
{
private:
	size_t position = 0;
public:
	using Entry::Entry;

	//void fopen();
	void fread(size_t size = -1);
	void fwrite(const char* buffer, size_t size);
	void fseek(size_t newPosition);
	void fclose();
};

class Directory : public Entry
{
private:
	bool opened = false;
	Map<std::string, size_t> table;
public:
	using Entry::Entry;

	void open(); // from disk
	void close(); // to disk // false if file is too big

	void list(std::string& out);
	size_t getFileAddress(const std::string& fileName); // 0 if it isnt exist
	void addFile(size_t fileAddress); // return file address to erasing
	void rmvFile(size_t fileAddress);

	ConstIterator<std::string, size_t> begin();
	ConstIterator<std::string, size_t> end();
};

class Editor : public Entry
{
	std::string Mytext;
	size_t deltaSize;
public:
	using Entry::Entry;

	void open();
	void insert(size_t pos, const std::string& data);
	void insert(size_t pos, char token);
	void remove(size_t pos, size_t size);
	const std::string& show();
	void save();
	void close();
	void oldinsert(size_t pos, const char* buffer, size_t size);
	void oldremove(size_t pos, size_t size);
	void oldshow(size_t begin = -1, size_t end = -1);
};
