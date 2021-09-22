#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "Menu.h"
#include "../Library/auxFuncs.h"

void Menu::output() {
	std::cout << "MENU FOR INTERACTING WITH KARDIOIDA\n";
	std::cout << "Current radius: " << line.get_radius() << std::endl;
	std::cout << "0) Quit [ q ]\n";
	std::cout << "1) Set radius\n";
	std::cout << "2) Count distance\n";
	std::cout << "3) Coords\n";
	std::cout << "4) Count radius of curvature\n";
	std::cout << "5) Count area\n";
	std::cout << "6) Count length\n";
}

bool get_answer_foo(int answer) { return answer < 0 || answer > 6; }

int Menu::get_answer() {
	int answer;

	bool status = getParam(answer, "Enter answer: -->", get_answer_foo);
	if (!status) return -1;

	return answer;
}

bool case1_foo(double a) { return a < 0; }

bool Menu::case_1() {
	double input_radius;

	bool status = getParam(input_radius, "Enter radius [ >= 0 ]: --> ", case1_foo);
	if (status) line.set_radius(input_radius);

	return status;
}

bool other_case_foo(double a) { return a < 0 || a > 2 * M_PI; }

bool Menu::case_2() {
	double phi;

	bool status = getParam(phi, "Enter phi [ 0 <= phi <= 2 * pi]: --> ", other_case_foo);
	if (status) std::cout << line.distance(phi) << std::endl;

	return status;
}

bool Menu::case_3() {
	Coords coords1, coords2;
	line.farthest_points(coords1, coords2);

	std::cout << coords1.x << ":" << coords1.y << std::endl;
	std::cout << coords2.x << ":" << coords2.y << std::endl;

	return true;
}

bool Menu::case_4() {
	double phi;

	bool status = getParam(phi, "Enter phi [ 0 <= phi <= 2 * pi]: --> ", other_case_foo);
	if (status) std::cout << line.curvature(phi) << std::endl;

	return status;
}

bool Menu::case_5() {
	double phi1, phi2;

	bool status1 = getParam(phi1, "Enter phi1 [ 0 <= phi1 <= 2 * pi]: --> ", other_case_foo);
	bool status2 = getParam(phi2, "Enter phi2 [ 0 <= phi2 <= 2 * pi]: --> ", other_case_foo);

	if (status1 && status2) std::cout << line.area(phi1, phi2) << std::endl;

	return status1 && status2;
}

bool Menu::case_6() {
	double phi1, phi2;

	bool status1 = getParam(phi1, "Enter phi1 [ 0 <= phi1 <= 2 * pi]: --> ", other_case_foo);
	bool status2 = getParam(phi2, "Enter phi2 [ 0 <= phi2 <= 2 * pi]: --> ", other_case_foo);

	if (status1 && status2) std::cout << line.length(phi1, phi2) << std::endl;

	return status1 && status2;
}

bool Menu::execute(int answer) {
	if (answer == 1) {
		return case_1();
	}
	else if (answer == 2) {
		return case_2();
	}
	else if (answer == 3) {
		return case_3();
	}
	else if (answer == 4) {
		return case_4();
	}
	else if (answer == 5) {
		return case_5();
	}
	else if (answer == 6) {
		return case_6();
	}
	return false;
}
