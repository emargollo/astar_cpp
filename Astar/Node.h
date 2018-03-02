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

	virtual void calculateHeuristic(const T&  end) {}

	virtual void setGValue(double value)
	{
		gValue = value;
	}
	virtual double getGValue() { return gValue; } 
	virtual double getHValue() { return hValue; }
	virtual double getFValue() const { return gValue + hValue; }
	virtual bool isBlocked() { return false; }

	std::vector<T*> getNeighbors() { return neighbors; }
    void setPrev(T* p) { prev = p; }
    T* getPrev() { return prev; }
	T* This() { return static_cast<T*>(this); }


	//Operators
	friend bool operator > (const Node &lhs, const Node &rhs) {
		return (lhs.getFValue() > rhs.getFValue());
	}
	friend bool operator < (const Node &lhs, const Node &rhs) {
		return (lhs.getFValue() < rhs.getFValue());
	}
	friend bool operator == (const Node &lhs, const Node &rhs) {
		//Needs to be implemented at derived
		return false;
	}

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


protected:
	std::vector<T*> neighbors;
	T* prev;
	double gValue{};
	double hValue{};
	double fValue;
};

template<typename T>
struct CmpNodePtrs
{
	template<typename T>
	bool operator()(const Node<T>* lhs, const Node<T>* rhs) const
	{
		return lhs->getFValue() > rhs->getFValue();
	}
};
#endif