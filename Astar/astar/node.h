#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <iostream>


template<typename T>
class node
{
public:

	node() {};
	~node() {};

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
	T* This() { return static_cast<T*>(this); }


	//Operators
	friend bool operator == (const node &lhs, const node &rhs)
	{
		//Needs to be implemented at derived
		return false;
	}
	bool operator()(const node<T>* lhs, const node<T>* rhs) const
	{
		return lhs->getFValue() > rhs->getFValue();
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
	double gValue{};
	double hValue{};
	double fValue;
};
#endif