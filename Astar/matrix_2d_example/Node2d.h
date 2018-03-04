#ifndef NODE_2D_H
#define NODE_2D_H
#include "../astar/node.h"
#include "Vector2d.h"
#include <iostream>

class Node2d : public node<Node2d>
{
public:
	Node2d();
	Node2d(Vector2d<int> p) { pos = p; }
	~Node2d();

	double distance(const Node2d& rhs);
	void calculateHeuristic(const Node2d&  end);
	bool isBlocked() { return full; }
	void setFull(bool f) { full = f; }
	Vector2d<int> getPos() const { return pos; }
	std::string toString();
	void printNeighbors();

	friend bool operator == (const Node2d &lhs, const Node2d &rhs) {
		return (lhs.pos == rhs.pos);
	}
private:
	Vector2d<int> pos;
	bool full;
};
#endif /*NODE_2D_H*/