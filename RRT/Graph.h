#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include "Node.h"
#include "point2D.h"

using std::vector;
using namespace std;

class Graph {
public:
	Node* rootNode;
	Node* lastNode;

public:
	Graph(Node* node);
	Node* findNearest(point2D* point);
	Node* addNode(point2D* point);
	void setLastNode(Node* node);
	void traversal(Node* node);
	// ~Graph();
	pair<vector<double>, vector<double>> retracePath();

private:
	pair<Node*, double>  findNearest_internal(Node* node, point2D* point) ;

};


#endif /* GRAPH_ */