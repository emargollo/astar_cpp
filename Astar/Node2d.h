#ifndef NODE_2D_H
#define NODE_2D_H
#include "Node.h"
#include <iostream>

class Node2d : public Node<Node2d>
{
public:
	Node2d();
	Node2d(Vector2d<int> p) { pos = p; }
	~Node2d();

	double distance(const Node2d& rhs);
	void calculateHeuristic(const Node2d&  end);
	Vector2d<int> getPos() const { return pos; }
	std::string toString();
	void printNeighbors();

	friend bool operator == (const Node2d &lhs, const Node2d &rhs) {
		return (lhs.pos == rhs.pos);
	}
private:
	Vector2d<int> pos;
};
#endif /*NODE_2D_H*/