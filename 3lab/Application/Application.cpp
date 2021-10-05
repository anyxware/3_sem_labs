#include <iostream>
#include "Menu.h"

int main()
{
	std::cout << "Static[1]/Dynamic[2]\n";
	int ns;
	std::cin >> ns;

	if (ns == 1) {
		using namespace Static;
		Menu menu;
		int answer;
		do{
			menu.output();
			if ((answer = menu.getAnswer()) < 0) break;
		} while (menu.execute(answer));
	}
	else {
		using namespace Dynamic;
		Menu menu;
		int answer;
		do {
			menu.output();
			if ((answer = menu.getAnswer()) < 0) break;
		} while (menu.execute(answer));
	}
	return 0;
}
