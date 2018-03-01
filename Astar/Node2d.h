#pragma once
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
	bool operator() (const char& lhs, const char& rhs) const
	{
		return lhs<rhs;
	}
	Node2d(const Node2d&) = default;
	Node2d& operator=(const Node2d&) = default;
private:
	Vector2d<int> pos;
};

namespace std
{
  template <> struct hash<Node2d> //hash is not a class template
  { //explicit specialization of non-template std::hash
    size_t operator()(const Node2d& node) const
    {
      return hash<int>()(node.getPos().X())^hash<int>()(node.getPos().Y()); //std::hash is not a template
    }
  };
}
