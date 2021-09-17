#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "Line.h"
#include "auxFuncs.h"

Line::Line(double input_radius) {
	if (input_radius < 0) {
		radius = 1;
		throw std::exception("invalid radius");
	}
	else radius = input_radius;
}

bool Line::set_radius(double input_radius) {
	if (input_radius < 0) {
		return false;
	}
	radius = input_radius;
	return true;
}

double Line::distance(double phi) const {
	return 2.0 * radius * (1 - cos(phi));
}

Coords* Line::farthest_points() const {
	double phi1 = -2 * M_PI / 3;
	double phi2 = -4 * M_PI / 3;

	Coords coords1, coords2;

	coords1.x = 2.0 * radius * cos(phi1) - radius * cos(2 * phi1);
	coords1.y = 2.0 * radius * sin(phi1) - radius * sin(2 * phi1);
	coords2.x = 2.0 * radius * cos(phi2) - radius * cos(2 * phi2);
	coords2.y = 2.0 * radius * sin(phi2) - radius * sin(2 * phi2);

	Coords* coords_array = safety_alloc<Coords>(2);

	if (!coords_array) return nullptr;

	coords_array[0] = coords1;
	coords_array[1] = coords2;

	return coords_array;
}

double Line::curvature(double phi) const {
	return 8.0 * radius * sin(phi / 2) / 3;
}

double Line::length(double phi1, double phi2) const {
	return 4.0 * radius * integral(phi1, phi2, foo1);

}

double Line::area(double phi1, double phi2) const {
	return 2.0 * radius * radius * integral(phi1, phi2, foo2);
}
