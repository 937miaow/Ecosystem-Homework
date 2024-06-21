// empty.cpp
#include "empty.h"

State EmptyUnit::getState()
{
	return EMPTY;
}

State EmptyUnit::nextState()
{
	round();

	if (sum[GRASS] > 1)
		return GRASS;
	else
		return EMPTY;
}

void EmptyUnit::round() // 更新 将代码移到living.h基类中
{
	updateSums();
}