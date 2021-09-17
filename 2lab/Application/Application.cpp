#include <iostream>
#include "Menu.h"

int main() {
	Menu menu;
	int answer;

	do {
		menu.output();
		answer = menu.get_answer();
		if (answer == -1) break;
	} while (menu.execute(answer));

	return 0;
}
