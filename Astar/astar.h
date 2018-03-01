#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include "Node.h"
#include "custom_queue.h"

class astar
{
public:
	astar();
	~astar();
	std::vector<Node*> reconstructPath();
	bool calculatePath(Node *begin, Node *end);
private:
	std::map<Node, Node> cameFrom;
	custom_queue<Node*, std::vector<Node*>, std::less<Node*>> openList;
	std::vector<Node*> closedList;
	
};
#endif /*ASTAR_H*/
