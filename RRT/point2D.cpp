#include <iostream>
#include <cmath>
#include "point2D.h"

using namespace std;


point2D::point2D(double x, double y) {
	this->x = x;
	this->y = y;
}

double point2D::Euc_Dist(point2D* point) {
	return sqrt(pow(x - point->x,2) + pow(y - point->y,2));
}

void point2D::disp() {
	cout << "X: " << x << " Y: " << y << endl;
}

double point2D::slope(point2D* point) {
	double slope = 0;
	if (point->x == x) {
		slope = double(point->y - y)/(point->x - (x - 0.00001));
	}
	else {
		slope = double(point->y - y)/(point->x - x);
	}
	return slope;
}