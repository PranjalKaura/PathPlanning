#ifndef NODE_H_
#define NODE_H_
#include <vector>
#include "point2D.h"

using std::vector;

class Node {
public:
	point2D* point;
	Node* parent;
	vector<Node*> children;

public:
	Node(point2D* point);
	void connectNode(Node* node);
	// ~Node();
};


#endif /* NODEH_ */