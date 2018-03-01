#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <iostream>
#include "Vector2d.h"


template<typename T>
class Node
{
public:

	Node() {};
	~Node() {};

	virtual double distance(const T& rhs) { return 0.0; }

	virtual void calculateHeuristic(const T&  end) { fValue = gValue + hValue; }

	virtual void setGValue(double value)
	{
		gValue = value;
		fValue = gValue + hValue;
	}
	virtual double getGValue()
	{
		return gValue;
	}

	virtual double getFValue()
	{
		return gValue + hValue;
	}
	virtual bool isBlocked()
	{
		return false;
	}

	std::vector<T*> getNeighbors() { return neighbors; }


	//Operators
	friend bool operator > (const Node &lhs, const Node &rhs) {
		return (lhs.fValue > rhs.fValue);
	}
	friend bool operator < (const Node &lhs, const Node &rhs) {
		return (lhs.fValue < rhs.fValue);
	}
	friend bool operator == (const Node &lhs, const Node &rhs) {
		//Needs to be implemented at derived
		return false;
	}
	Node<T>(const Node<T>&) = default;
	Node<T>& operator=(const Node<T>&) = default;

	T* This() { return static_cast<T*>(this); }

	//Adding neighbors
	template<typename First, typename ... Nodes>
	void addNeighbors(First arg, const Nodes&... rest) {
		neighbors.push_back(arg);
		arg->addNeighbor(This());
		addNeighbors(rest...);
	}
	void addNeighbors() {};
	void addNeighbor(T* n)
	{
		neighbors.push_back(n);
	}

	virtual std::string toString() { return ""; }


protected:
	std::vector<T*> neighbors;
	double gValue{};
	double hValue{};
	double fValue;
};
#endif