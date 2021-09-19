#include "Obstacle.h"
#include <cmath>
#include <iostream>

using namespace std;

vector<int>  Obstacle::radius = {};
vector<point2D*> Obstacle::centre = {};
int Obstacle::verbose = 0;

void Obstacle::addObstacle(double radius, point2D* centre) {
	this->radius.push_back(radius);
	this->centre.push_back(centre);
}

void Obstacle::printObs() {
	for (int i = 0; i < radius.size(); i++) {
		centre[i]->disp();
		cout << "Radius: " << radius[i] << endl;
	}
}

bool Obstacle::checkCollision(point2D* point1, point2D* point2) {
	// Referenced from https://stackoverflow.com/a/1079478

	if(checkCollision_Point(point1) || checkCollision_Point(point2) ) {
		return true;
	}
	double slope1 = point1->slope(point2);

	for (int i = 0; i < radius.size(); i++) {
		double slope2 = point1->slope(centre[i]);
		double Theta = 0;
		if (slope1*slope2 == -1) {
			Theta = -M_PI/2;
		}
		else {
			Theta = atan((slope1 - slope2)/(1 + slope1*slope2));
		}

		double dist = centre[i]->Euc_Dist(point1);
		if (dist*sin(Theta) <= radius[i] & dist*cos(Theta) <= point1->Euc_Dist(point2)){
			// See figure from link: CD > r and AD < AB
			if (verbose == 1){
				cout << "Collision with " << centre[i]->x << " " << centre[i]->y << endl;
			}
			return true;
		}

	}
	return false;

}

bool Obstacle::checkCollision_Point(point2D* point1) {
	for (int i = 0; i < radius.size(); i++) {
		if(radius[i] >= point1->Euc_Dist(centre[i])) {
			if (verbose == 1) {
				cout << "Collision of " << endl;
				point1->disp();
				cout << "Collision with" << endl;
				centre[i]->disp();
				cout << "radius: " << radius[i] << endl;
			}
			return true;
		}
	}
	return false;
}
