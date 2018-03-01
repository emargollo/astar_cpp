#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <unordered_map>
#include "Node.h"
#include "custom_queue.h"

template<class N>
class astar
{
public:
	astar() {};

	~astar() {};

	std::vector<N*> reconstructPath()
	{
		std::vector<N*> path;
		N* current = closedList.back();
		for (auto it = closedList.begin(); it != closedList.end(); ++it) {
			std::cout << "R - " << (*it)->toString() << std::endl;
		}

		path.push_back(current);
		while (current != current->getPrev())
		{
			current = current->getPrev();
			path.push_back(current);
		}
		std::reverse(path.begin(), path.end());
		return path;
	}

	bool calculatePath(N *begin, N *end)
	{
		openList.push(begin);
		begin->setPrev(begin);
		while (!openList.empty())
		{
			N* current = openList.top();
			openList.pop();
			closedList.push_back(current);


			if (*current == *end)
			{
				return true;
			}

			std::vector<N*> neighbors = current->getNeighbors();
			current->printNeighbors();
			for (auto it = neighbors.begin(); it != neighbors.end(); ++it)
			{
				double cost = current->getGValue() + current->distance(**it);
				if ((*it)->isBlocked()) continue;

				if (std::find(closedList.begin(), closedList.end(), *it) != closedList.end()) continue;

				auto openIt = openList.find(*it);
				if (openIt != openList.end() && cost < (*it)->getGValue())
				{
					std::cout << "HERE!";
					(*it)->setGValue(cost);
					(*it)->setPrev(current);

				}

				if (openIt == openList.end())
				{
					(*it)->setGValue(cost);
					(*it)->calculateHeuristic(*end);
					std::cout << "PAIR - " << (*it)->toString() << ", " << current->toString() << std::endl;
					(*it)->setPrev(current);
					openList.push(*it);
				}
			}
		}
		return false;
	}
private:
	custom_queue<N*, std::vector<N*>, std::less<N*>> openList;
	std::vector<N*> closedList;
};
#endif /*ASTAR_H*/
