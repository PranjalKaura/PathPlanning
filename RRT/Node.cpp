#include "Node.h"

Node::Node(point2D* point) {
	this->point = point;
	this->parent = NULL;
}

void Node::connectNode(Node* node) {
	children.push_back(node);
	node->parent = this;
}

// Node::~Node() {
// 	delete children;
// }