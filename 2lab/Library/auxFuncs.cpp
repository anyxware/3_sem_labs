#include <cmath>
#include "auxFuncs.h"

double lengthCounter(double phi) {
	return sin(phi / 2);
}

double areaCounter(double phi) {
	return (1 - cos(phi)) * (1 - cos(phi));
}

double integral(double phi1, double phi2, double (*foo)(double phi)) {
	int n = 1000000;
	double dphi = (phi2 - phi1) / n;
	double cur_phi = phi1;;

	double I = 0;

	for (int i = 0; i < n; i++) {
		I += (foo(cur_phi) + foo(cur_phi + dphi)) / 2 * dphi;
		cur_phi += dphi;
	}
	return I;
}

