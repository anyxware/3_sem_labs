#include <iostream>
#include "Menu.h"
#include "../Library/auxFuncs.h"

namespace Static {
	void Menu::output() {
		std::cout << "Currnet vectors:\n";
		v1.getArray(std::cout);
		v2.getArray(std::cout);
		std::cout << "1) Set array;\n";
		std::cout << "2) Add;\n";
		std::cout << "3) Substract;\n";
		std::cout << "4) Multiply;\n";
		std::cout << "5) Vector's norm;\n";
		std::cout << "6) Append element;\n";
	}

	int Menu::getAnswer() {
		int answer;
		const char* pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter answer: ";
			pr = "You are wrong; repeat please!";

			if (!getNum(answer, std::cin))
				return -1;;

		} while (answer < 0 || answer > 6);
		return answer;
	}

	bool Menu::case1() {
		std::cout << "Set 1st array;\n";
		std::cout << "Set 2nd array;\n";
		std::cout << "1 / 2 : "; 
		int answer;
		if (!getNum(answer, std::cin)) {
			std::cout << "Bad number\n";
			return false;
		}
		if (answer == 1) v1.setArray(std::cin);
		else v2.setArray(std::cin);
		return true;
	}

	bool Menu::case2() {
		(v1 + v2).getArray(std::cout);
		return true;
	}

	bool Menu::case3() {
		(v1 - v2).getArray(std::cout);
		return true;
	}

	bool Menu::case4() {
		std::cout << v1 * v2;
		return true;
	}

	bool Menu::case5() {
		std::cout << "1st array norma;\n";
		std::cout << "2nd array norma;\n";
		std::cout << "1 / 2 : ";
		int answer;
		if (!getNum(answer, std::cin)) {
			std::cout << "Bad number\n";
			return false;
		}
		double norma;
		bool status;
		if (answer == 1) status = v1.normOfVector(norma); 
		else status = v2.normOfVector(norma);
		if (status) std::cout << norma << std::endl;
		else std::cout << "Bad vector\n";
		return true;
	}

	bool Menu::case6() {
		std::cout << "1st array append;\n";
		std::cout << "2nd array append;\n";
		std::cout << "1 / 2 : ";
		int answer;
		if (!getNum(answer, std::cin)) {
			std::cout << "Bad number\n";
			return false;
		}
		double number;
		std::cout << "Enter number: ";
		if (!getNum(number, std::cin)) {
			std::cout << "Bad number\n";
			return false;
		}
		if (answer == 1) v1.append(number);
		else v2.append(number);
		return true;
	}

	bool Menu::execute(int answer) {
		if (answer == 1) {
			return case1();
		}
		else if(answer == 2) {
			return case2();
		}
		else if (answer == 3) {
			return case3();
		}
		else if (answer == 4) {
			return case4();
		}
		else if (answer == 5) {
			return case5();
		}
		else if (answer == 6) {
			return case6();
		}
		else {
			return false;
		}
	}
}

namespace Dynamic {
	void Menu::output() {
		std::cout << "Currnet vectors:\n";
		std::cout << v1;
		std::cout << v2;
		std::cout << "1) Set array;\n";
		std::cout << "2) Add;\n";
		std::cout << "3) Substract;\n";
		std::cout << "4) Multiply;\n";
		std::cout << "5) Vector's norm;\n";
		std::cout << "6) Append element;\n";
	}

	int Menu::getAnswer() {
		int answer;
		const char* pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter answer: ";
			pr = "You are wrong; repeat please!";

			if (!getNum(answer, std::cin))
				return -1;;

		} while (answer < 0 || answer > 6);
		return answer;
	}

	bool Menu::case1() {
		std::cout << "Set 1st array;\n";
		std::cout << "Set 2nd array;\n";
		std::cout << "1 / 2 [default] : ";
		int answer;
		if (!getNum(answer, std::cin)) {
			std::cout << "Bad number\n";
			return false;
		}
		if (answer == 1) v1.setArray(std::cin);
		else v2.setArray(std::cin);
		return true;
	}

	bool Menu::case2() {
		Vector v3 = v1 + v2;
		std::cout << v3;
		return true;
	}

	bool Menu::case3() {
		Vector v3 = v1 - v2;
		std::cout << v3;
		return true;
	}

	bool Menu::case4() {
		Vector v3 = v1 * v2;
		std::cout << v3;
		return true;
	}

	bool Menu::case5() {
		std::cout << "1st array norma;\n";
		std::cout << "2nd array norma;\n";
		std::cout << "1 / 2 : ";
		int answer;
		if (!getNum(answer, std::cin)) {
			std::cout << "Bad number\n";
			return false;
		}
		double norma;
		bool status;
		if (answer == 1) { status = v1.normOfVector(norma); }
		else status = v2.normOfVector(norma);
		if (status) std::cout << norma << std::endl;
		else std::cout << "Bad vector\n";
		return true;
	}

	bool Menu::case6() {
		std::cout << "1st array norma;\n";
		std::cout << "2nd array norma;\n";
		std::cout << "1 / 2 : ";
		int answer;
		if (!getNum(answer, std::cin)) {
			std::cout << "Bad number\n";
			return false;
		}
		double number;
		std::cout << "Enter number: ";
		if (!getNum(number, std::cin)) {
			std::cout << "Bad number\n";
			return false;
		}
		if (answer == 1) v1.append(number);
		else v2.append(number);
		return true;
	}

	bool Menu::execute(int answer) {
		if (answer == 1) {
			return case1();
		}
		else if (answer == 2) {
			return case2();
		}
		else if (answer == 3) {
			return case3();
		}
		else if (answer == 4) {
			return case4();
		}
		else if (answer == 5) {
			return case5();
		}
		else if (answer == 6) {
			return case6();
		}
		else {
			return false;
		}
	}
}