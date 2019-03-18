#include "astar/astar.h"
#include "astar/node.h"
#include "matrix_2d_example/Map2d.h"
#include "matrix_2d_example/Node2d.h"
#include "matrix_2d_example/Vector2d.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sys/timeb.h>
#include <chrono>

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
	srand(time(NULL));
	Map2d::executeTest(100, 100);
	
	system("Pause");
	return 0;
}
