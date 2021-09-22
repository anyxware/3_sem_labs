#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "Line.h"
#include "auxFuncs.h"

Line::Line(double input_radius) {
	if (input_radius < 0) {
		throw std::exception("invalid radius");
	}
	else radius = input_radius;
}

void Line::set_radius(double input_radius) {
	if (input_radius < 0) {
		throw std::exception("Bad radius"); 
	}
	radius = input_radius;
}

double Line::distance(double phi) const {
	return 2.0 * radius * (1 - cos(phi));
}

void Line::farthest_points(Coords& coords1, Coords& coords2) const { 
	double phi1 = -2 * M_PI / 3;
	double phi2 = -4 * M_PI / 3;

	coords1.x = 2.0 * radius * cos(phi1) - radius * cos(2 * phi1);
	coords1.y = 2.0 * radius * sin(phi1) - radius * sin(2 * phi1);
	coords2.x = 2.0 * radius * cos(phi2) - radius * cos(2 * phi2);
	coords2.y = 2.0 * radius * sin(phi2) - radius * sin(2 * phi2);
}

double Line::curvature(double phi) const {
	return 8.0 * radius * sin(phi / 2) / 3;
}

double Line::length(double phi1, double phi2) const {
	return 4.0 * radius * integral(phi1, phi2, lengthCounter);

}

double Line::area(double phi1, double phi2) const {
	return 2.0 * radius * radius * integral(phi1, phi2, areaCounter);
}
