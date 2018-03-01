#include "astar.h"
#include "Node.h"
#include "Vector2d.h"
#include <iostream>

astar::astar()
{
}

astar::~astar()
{
}

std::vector<Node*> astar::reconstructPath()
{
	std::vector<Node*> path;
	Node* current = closedList.back();
	for (auto it = closedList.begin(); it != closedList.end(); ++it) {
	}

	while (current != &cameFrom.at(*current))
	{
		path.push_back(current);
		current = &cameFrom.at(*current);
	}
	std::reverse(path.begin(), path.end());
	return path;
}

bool astar::calculatePath(Node* begin, Node* end)
{
	openList.push(begin);
	cameFrom.insert(std::make_pair(*begin, *begin));
	while (!openList.empty())
	{
		Node* current = openList.top();
		openList.pop();
		closedList.push_back(current);


		if (*current == *end) 
		{
			return true;
		}

		std::vector<Node*> neighbors = current->getNeighbors();
		current->printNeighbors();
		for (auto it = neighbors.begin(); it != neighbors.end(); ++it)
		{
			double cost = current->getGValue() + current->distance(**it);

			if ((*it)->isBlocked()) continue;
			
			if (std::find(closedList.begin(), closedList.end(), *it) != closedList.end()) continue;

			auto openIt = openList.find(*it);
			if (openIt != openList.end() && cost < (*it)->getGValue())
			{
				(*it)->setGValue(cost);
				cameFrom.at(**it) = *current;
				
			}

			if (openIt == openList.end())
			{
				(*it)->setGValue(cost);
				(*it)->calculateHeuristic(*end);
				cameFrom.insert(std::make_pair(**it, *current));
				openList.push(*it);
			}
		}
	}
	return false;
}

int main() {

	//astar<Node<Vector2d<int>>> a;
	Vector2d<int> v(0, 0);
	Vector2d<int> v2(0, 1);
	Vector2d<int> v3(0, -1);
	Vector2d<int> v4(-1, 1);
	Vector2d<int> v5(1, -1);
	Vector2d<int> v6(-1, -1);
	Vector2d<int> v7(1, 1);
	Vector2d<int> v8(1, 0);
	Vector2d<int> v9(-1, 0);
	// 1-1| 10| 11
	// 0-1| 00| 01
	//-1-1|-10|-11

	Node n1(v);
	Node n2(v2);
	Node n3(v3);
	Node n4(v4);
	Node n5(v5);
	Node n6(v6);
	Node n7(v7);
	Node n8(v8);
	Node n9(v9);
	n1.addNeighbors(&n2, &n3, &n4, &n5, &n6, &n7, &n8, &n9);
	n2.addNeighbors(&n4, &n7, &n8, &n9);
	n3.addNeighbors(&n5, &n6, &n8, &n9);
	n4.addNeighbors(&n9);
	n5.addNeighbors(&n8);
	n6.addNeighbors(&n9);
	n7.addNeighbors(&n8);
	

	astar a;
	if (a.calculatePath(&n3, &n2)) {
		std::vector<Node*> path = a.reconstructPath();
		for (auto it = path.begin(); it != path.end(); ++it) {
			std::cout << "P - (" << (*it)->getPos().X() << ", " << (*it)->getPos().Y() << ")\n";
		}
	}
	
	system("Pause");
	return 0;
}
