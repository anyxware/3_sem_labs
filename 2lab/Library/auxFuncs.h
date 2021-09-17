#include <iostream>
#include <limits>

double foo1(double phi);
double foo2(double phi);

double integral(double phi1, double phi2, double (*foo)(double phi));

template <typename T>
T* safety_alloc(int size) {
	try {
		return new T[size];
	}
	catch (std::bad_alloc& ba) {
		return nullptr;
	}
}

template <typename T>
int getNum(T& a) {
	std::cin >> a;
	if (!std::cin.good())
		return -1;
	return 1;
}

template <typename T>
bool getParam(T& a, const char* msg, bool (*foo)(T)) {
	const char* pr = "";
	do {
		std::cout << pr << std::endl;
		std::cout << msg;
		pr = "You are wrong; repeat please!";

		if (getNum(a) < 0)
			return false;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (foo(a));

	return true;
}

