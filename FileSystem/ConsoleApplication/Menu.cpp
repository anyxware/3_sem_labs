#include <iostream>
#include <fstream>
#include <sstream>
#include "Menu.h"

bool Menu::isExist()
{
	const char* pr = "";
	bool badAnswer = true;
	char answer;
	do {
		std::cout << pr;
		pr = "Bad input\n";
		std::cout << "Use existing Filesystem[1] / Create new[2]: ";
		std::cin >> answer;
		if (std::cin.eof()) {
			break;
		}
		if (answer == '1' || answer == '2') badAnswer = false;
	} while (badAnswer);

	if (std::cin.eof()) exit(0);
	return  answer == '1' ? true : false;
}

std::string Menu::getDiskName()
{
	std::string diskName;
	std::cout << "Input disk name: ";
	std::cin >> diskName;

	if (std::cin.eof()) exit(0);
	return diskName;
}

bool Menu::checkParam(const std::string& diskName, bool isExist)
{
	std::ifstream file;
	file.open(diskName);
	bool status = file.is_open() ? true : false;
	file.close();
	return status;
}

std::string Menu::login()
{
	std::string userName;
	std::cout << "Input user name: ";
	std::cin >> userName;

	if (std::cin.eof()) exit(0);
	return userName;
}

bool Menu::ReadAndExecute(FileSystem& fs)
{
	std::string unpreparedString;
	std::string command;
	std::string arg1;
	std::string arg2;

	std::getline(std::cin, unpreparedString);

	while (std::cin.good()) {
		std::cout << "myfs> ";
		std::getline(std::cin, unpreparedString);
		if (std::cin.eof()) {
			fs.end();
			exit(0);
		}

		std::stringstream stream(unpreparedString);

		stream >> command;

		try {
			Commands.at(command);
		}
		catch (std::exception& e) {
			std::cout << command << ": No such command\n";
			continue;
		}

		if (stream.eof() && command == "ls") arg1 = ".";

		if (Commands[command].first > 0) {
			stream >> arg1;
		}

		if (Commands[command].first > 1) {
			stream >> arg2;
		}

		if (!stream.eof()) {
			std::cout << "Bad file or directory name\n";
			continue;
		}

		if (!Commands[command].second(fs, arg1, arg2)) {
			std::cout << "Bad file or directory name\n";
		}
	}

	return true;
}







