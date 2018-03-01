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
		for (auto &it : cameFrom) {
			N t = it.first;
			std::cout << "M - " << t.toString() << ", " << it.second.toString() << std::endl;
		}
		std::cout << "L - " << cameFrom.size() << std::endl;

		while (current != &cameFrom.at(*current))
		{
			N* prev = &cameFrom.at(*current);
			std::cout << "~ - " << current->toString() << prev->toString() << std::endl;
			path.push_back(current);
			current = &cameFrom.at(*current);
		}
		std::reverse(path.begin(), path.end());
		return path;
	}

	bool calculatePath(N *begin, N *end)
	{
		openList.push(begin);
		cameFrom.insert(std::make_pair(*begin, *begin));
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
					cameFrom.at(**it) = *current;

				}

				if (openIt == openList.end())
				{
					(*it)->setGValue(cost);
					(*it)->calculateHeuristic(*end);
					std::cout << "PAIR - " << (*it)->toString() << ", " << current->toString() << std::endl;
					std::cout << "LENGHT - " << cameFrom.size() << std::endl;
					cameFrom.insert(std::make_pair(**it, *current));
					openList.push(*it);
				}
			}
		}
		return false;
	}
private:


	std::map<N, N> cameFrom;
	custom_queue<N*, std::vector<N*>, std::less<N*>> openList;
	std::vector<N*> closedList;
};
#endif /*ASTAR_H*/
