#include "astar.h"
#include "Node.h"
#include "Map2d.h"
#include "Node2d.h"
#include "Vector2d.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sys/timeb.h>

int getMilliCount() {
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int getMilliSpan(int nTimeStart) {
	int nSpan = getMilliCount() - nTimeStart;
	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

int main()
{
	Map2d map(10, 10);
	std::vector <std::vector<int> > vec2D(10, std::vector<int>(10, 0));
	map.loadMapFrom2dVector(vec2D);

	map.printMap();
	int start = getMilliCount();
	astar<Node2d> a;
	std::vector<Node2d*> path;
	if (a.calculatePath(map.get(0, 1), map.get(9, 9))) {
		path = a.reconstructPath();

		int milliSecondsElapsed = getMilliSpan(start);
		std::cout << "T = " << milliSecondsElapsed << std::endl;
	}


	for (auto it = path.begin(); it != path.end(); ++it) {
		(*it)->printNeighbors();
	}

	//astar<Node<Vector2d<int>>> a;
	//Vector2d<int> v(0, 0);
	//Vector2d<int> v2(0, 1);
	//Vector2d<int> v3(0, -1);
	//Vector2d<int> v4(-1, 1);
	//Vector2d<int> v5(1, -1);
	//Vector2d<int> v6(-1, -1);
	//Vector2d<int> v7(1, 1);
	//Vector2d<int> v8(1, 0);
	//Vector2d<int> v9(-1, 0);
	//// 1-1| 10| 11
	//// 0-1| 00| 01
	////-1-1|-10|-11

	//Node2d n1(v);
	//Node2d n2(v2);
	//Node2d n3(v3);
	//Node2d n4(v4);
	//Node2d n5(v5);
	//Node2d n6(v6);
	//Node2d n7(v7);
	//Node2d n8(v8);
	//Node2d n9(v9);
	//n1.addNeighbors(&n2, &n3, &n4, &n5, &n6, &n7, &n8, &n9);
	//n2.addNeighbors(&n4, &n7, &n8, &n9);
	//n3.addNeighbors(&n5, &n6, &n8, &n9);
	//n4.addNeighbor(&n9);
	//n5.addNeighbor(&n8);
	//n6.addNeighbor(&n9);
	//n7.addNeighbor(&n8);
	//

	//int start = getMilliCount();
	//astar<Node2d> a;
	//std::vector<Node2d*> path;
	//if (a.calculatePath(&n3, &n2)) {
	//	path = a.reconstructPath();

	//	int milliSecondsElapsed = getMilliSpan(start);
	//	std::cout<< "T = " << milliSecondsElapsed << std::endl;
	//}

	//for (auto it = path.begin(); it != path.end(); ++it) {
	//	std::cout << "P - " << (*it)->toString() << "\n";
	//}
	
	system("Pause");
	return 0;
}
