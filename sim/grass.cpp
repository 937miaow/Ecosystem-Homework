// grass.cpp
#include "grass.h"
#include "empty.h"

State GrassUnit::getState()
{
	return GRASS;
}

State GrassUnit::nextState()
{
	round();
	if (sum[RABBIT] > 0)
		return EMPTY;
	else if (sum[GRASS] > 0 && sum[RABBIT] == 0)
		return GRASS;
	else
		return EMPTY;
}

void GrassUnit::round() // 更新 将代码移到living.h基类中
{
	updateSums();
}