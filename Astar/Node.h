#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <iostream>
#include "Vector2d.h"

class Node
{
public:
	Node();
	Node(Vector2d<int> p) { pos = p; }
	~Node();

	virtual double distance( const Node& rhs);
	virtual void calculateHeuristic(const Node&  end);
	virtual void setGValue(double value);
	virtual double getGValue();
	virtual double getFValue();
	virtual bool isBlocked();
	std::vector<Node*> getNeighbors() { return neighbors; }
	Vector2d<int> getPos() { return pos; }

	std::string toString();
	void printNeighbors();

	//Operators
	friend bool operator > (const Node &lhs, const Node &rhs) {
		return (lhs.fValue > rhs.fValue);
	}
	friend bool operator < (const Node &lhs, const Node &rhs) {
		return (lhs.fValue < rhs.fValue);
	}
	friend bool operator == (const Node &lhs, const Node &rhs) {
		return (lhs.pos == rhs.pos);
	}

	//Adding neighbors
	template<typename First, typename ... Nodes>
	void addNeighbors(First arg, const Nodes&... rest) {
		neighbors.push_back(arg);
		arg->addNeighbor(this);
		addNeighbors(rest...);
	}
	void addNeighbors() {};
	void addNeighbor(Node* n);



private:
	std::vector<Node*> neighbors;
	Vector2d<int> pos;
	double gValue{};
	double hValue{};
	double fValue;
};
#endif