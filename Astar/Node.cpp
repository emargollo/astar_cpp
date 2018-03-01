#include "Node.h"


Node::Node()
{
}

Node::~Node()
{
}

double Node::distance(const Node & rhs)
{
	return Vector2d<int>::Distance(pos, rhs.pos);
}

void Node::calculateHeuristic(const Node& end)
{
	hValue = distance(end);
	fValue = gValue + fValue;
}

void Node::setGValue(double value)
{
	gValue = value;
	fValue = gValue + fValue;
}

double Node::getGValue()
{
	return gValue;
}

double Node::getFValue()
{
	return gValue + hValue;
}

bool Node::isBlocked()
{
	return false;
}

void Node::addNeighbor(Node * n)
{
	neighbors.push_back(n);
}

std::string Node::toString()
{
	return pos.toString();
}

void Node::printNeighbors()
{
	std::cout << toString() << ": ";
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		std::cout << (*it)->toString() << "-";
	}
	std::cout << "\n";
}
