#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include <vector>
#include "point2D.h"

using std::vector;

class Obstacle{
public:
	static vector<int>  radius;
	static vector<point2D*> centre;
	static int verbose;

public:
	void addObstacle(double radius, point2D* centre);
	void printObs();
	bool checkCollision(point2D* point1, point2D* point2);
	// ~Obstacle();

private:
	bool checkCollision_Point(point2D* point);

};


#endif /* OBSTACLEH_ */