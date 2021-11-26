#include <iostream>
#include "../StaticLib/FileSystem.h"
#include "Menu.h"
#include <string>
#include <map>
#include <fstream>
//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
//#include <crtdbg.h>

// read time std::asctime(std::localtime(&result));
void print() { std::cout << '\n'; }

template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail) {
	std::cout << head << " ";
	print(tail...);
}


int main()
{
	// start
	 
	Menu menu;
	bool isExist = menu.isExist();

	std::string diskName = menu.getDiskName();
	if (!menu.checkParam(diskName, isExist))
		return 0;


	FileSystem fs;
	if (!fs.start(diskName, isExist))
		return 0;
	std::string userName = menu.login();
	if (!fs.login(userName)) {
		fs.end();
		return 0;
	}

	// running

	menu.ReadAndExecute(fs);

	fs.end();

}



