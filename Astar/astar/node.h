#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <iostream>
#include <memory>


template<typename T>
class node : public std::enable_shared_from_this<node<T>>
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

	std::vector<std::shared_ptr<T>> getNeighbors() { return neighbors; }
	T* This() { return static_cast<T*>(this); }
	//std::shared_ptr<T> This() { return this->shared_from_this(); }


	//Operators
	friend bool operator == (const node &lhs, const node &rhs)
	{
		//Needs to be implemented at derived
		return false;
	}
	/*bool operator()(const node<T>* lhs, const node<T>* rhs) const
	{
		return lhs->getFValue() > rhs->getFValue();
	}*/
	bool operator()(const std::shared_ptr<node<T>> lhs, const std::shared_ptr<node<T>> rhs) const
	{
		return lhs->getFValue() > rhs->getFValue();
	}

	//Adding neighbors
	template<typename First, typename ... Nodes>
	void addNeighbors(First arg, const Nodes&... rest) {
		neighbors.push_back(arg);
		std::shared_ptr<T> _this(This());
		arg->addNeighbor(_this);
		addNeighbors(rest...);
	}
	void addNeighbors() {};
	void addNeighbor(std::shared_ptr<T> n)
	{
		neighbors.push_back(n);
	}


protected:
	std::vector<std::shared_ptr<T>> neighbors;
	double gValue{};
	double hValue{};
	double fValue;
};
#endif