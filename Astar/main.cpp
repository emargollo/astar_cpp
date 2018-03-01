#include "astar.h"
#include "Node.h"
#include "Node2d.h"
#include "Vector2d.h"
#include <iostream>

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

	Node2d n1(v);
	Node2d n2(v2);
	Node2d n3(v3);
	Node2d n4(v4);
	Node2d n5(v5);
	Node2d n6(v6);
	Node2d n7(v7);
	Node2d n8(v8);
	Node2d n9(v9);
	n1.addNeighbors(&n2, &n3, &n4, &n5, &n6, &n7, &n8, &n9);
	n2.addNeighbors(&n4, &n7, &n8, &n9);
	n3.addNeighbors(&n5, &n6, &n8, &n9);
	n4.addNeighbors(&n9);
	n5.addNeighbors(&n8);
	n6.addNeighbors(&n9);
	n7.addNeighbors(&n8);
	

	astar<Node2d> a;
	if (a.calculatePath(&n3, &n2)) {
		std::vector<Node2d*> path = a.reconstructPath();
		for (auto it = path.begin(); it != path.end(); ++it) {
			std::cout << "P - " << (*it)->toString() << "\n";
		}
	}
	
	system("Pause");
	return 0;
}
