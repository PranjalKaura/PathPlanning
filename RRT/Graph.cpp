#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(Node* node) {
	this->rootNode = node;
}

Node* Graph::findNearest(point2D* point) {
	auto [closestNode, dist] = findNearest_internal(rootNode, point);
	return closestNode;
}

pair<Node*, double>  Graph::findNearest_internal(Node* node, point2D* point) {
	double cur_minDist = node->point->Euc_Dist(point);
	Node* closestNode = node;
	for (int i = 0; i < node->children.size(); i++) {
		auto [childNode, child_dist] = findNearest_internal(node->children[i], point);
		if (child_dist < cur_minDist) {
			closestNode = childNode;
			cur_minDist = child_dist;
		}
	}
	return {closestNode, cur_minDist};
}

Node* Graph::addNode(point2D* point) {
	Node* closestNode = findNearest(point);
	Node* newNode = new Node(point);
	closestNode->connectNode(newNode);
	return newNode;
}

void Graph::setLastNode(Node* node) {
	lastNode = node;
}

void Graph::traversal(Node* node) {
	node->point->disp();
	cout << "Now children" << endl;
	for (int i = 0; i < node->children.size(); i++) {
		traversal(node->children[i]);
	}
	cout << "END children"<< endl;
}

pair<vector<double>, vector<double>> Graph::retracePath() {
	vector<double> path_x;
	vector<double> path_y;
	Node* node = this->lastNode;
	while(node != NULL) {
		// cout << "NOW AT " << flush;
		// node->point->disp();
		path_x.push_back(node->point->x);
		path_y.push_back(node->point->y);
		node = node->parent;
	}
	return {path_x, path_y};
}

// Graph::~Graph() {
// 	delete rootNode;
// 	delete lastNode;
// }