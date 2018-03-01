#include "Node2d.h"



Node2d::Node2d()
{
}


Node2d::~Node2d()
{
}

double Node2d::distance(const Node2d & rhs)
{
	return Vector2d<int>::Distance(pos, rhs.pos);
}

void Node2d::calculateHeuristic(const Node2d & end)
{
	hValue = distance(end);
	fValue = gValue + hValue;
}

std::string Node2d::toString()
{
	return pos.toString();
}



void Node2d::printNeighbors()
{
	std::cout << toString() << ": ";
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		std::cout << (*it)->toString() << "-";
	}
	std::cout << "\n";
}