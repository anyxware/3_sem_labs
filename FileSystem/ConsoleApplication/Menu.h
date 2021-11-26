#pragma once

#include <string>
#include <list>
#include <array>
#include <map>
#include "../StaticLib/FileSystem.h"

using cstr = const std::string&;



inline bool pwd(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) {
	fs.pwd();
	return true;
}

inline bool cd(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) {
	return fs.cd(str_a);
}

inline bool mkdir(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) {
	return fs.mkdir(str_a);
}

inline bool list(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) {
	return str_a == std::string() ? fs.list() : fs.list(str_a);
}

inline bool touch(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) {
	return fs.touch(str_a);
}

inline bool rm(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) {
	return fs.rm(str_a);
}

inline bool mv(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) {
	return fs.mv(str_a, str_b);
}

//struct command {
//	virtual bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const {}
//};
//
//struct pwd : command {
//	bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const override {
//		fs.pwd();
//		return true;
//	}
//};

//struct cd : command {
//	bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const override {
//		return fs.cd(str_a);
//	}
//};
//
//struct mkdir : command {
//	bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const override {
//		return fs.mkdir(str_a);
//	}
//};
//
//struct list : command {
//	bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const override {
//		return str_a == std::string() ? fs.list() : fs.list(str_a);
//	}
//};
//
//struct touch : command {
//	bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const override {
//		return fs.touch(str_a);
//	}
//};
//
//struct rm : command {
//	bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const override {
//		return fs.rm(str_a);
//	}
//};
//
//struct mv : command {
//	bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const override {
//		return fs.mv(str_a, str_b);
//	}
//};
//
//struct cp : command {
//	bool operator()(FileSystem& fs, cstr str_a = std::string(), cstr str_b = std::string()) const override {
//		return fs.cp(str_a, str_b);
//	}
//};

using pfunc = bool(*)(FileSystem&, cstr, cstr);


class Menu
{
private:
	std::map<std::string, std::pair<int, pfunc>> Commands = { {"pwd", {0, pwd}}, {"cd", {1, cd}}, {"mkdir", {1, mkdir}}, {"ls", {1, list}}, {"touch", {1, touch}}, {"rm", {1, rm}}, {"mv", {2, mv}} };
public:
	bool isExist(); // 0 if eof, 1 if exist, 2 if doesn't
	std::string getDiskName();
	bool checkParam(const std::string& diskName, bool isExist);
	std::string login();
	bool ReadAndExecute(FileSystem& fs);
};

