#ifndef POINT2D_H_
#define POINT2D_H_

class point2D {
public:
	double x;
	double y;
public:
	point2D(double x, double y);
	double Euc_Dist(point2D* point);
	void disp();
	double slope(point2D* point);
};


#endif /* POINT2DH_ */