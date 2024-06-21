// rabbit.cpp

#include "rabbit.h"
#include "empty.h"

State RabbitUnit::getState()
{
	return RABBIT;
}

State RabbitUnit::nextState()
{
	round();
	if (age > DRAB) // 年龄大于最大年龄，返回EMPTY
	{
		return EMPTY;
	}
	else if (sum[RABBIT] > TMRAB) // 周围兔子数大于TMRAB，返回EMPTY
	{
		return EMPTY;
	}
	else if (sum[RABBIT] > 1) // 周围有同种兔子且有食物，选择一个位置吃掉食物，并在该位置繁殖兔子
	{
		Position preyPos = findPreyPosition();
		world->setUnitAt(preyPos, RABBIT); // 在该位置繁殖兔子
		return RABBIT;					   // 返回兔子状态
	}
	else
	{
		return RABBIT; // 其他情况下保持为兔子
	}
}

void RabbitUnit::round() // 更新 将代码移到living.h基类中
{
	updateSums();
}

Position RabbitUnit::findPreyPosition()
{
	// 寻找周围有兔子的位置，并且该位置有食物（草）
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0)
				continue;
			Position newPos = {pos.row + i, pos.colum + j};
			if (world->getUnitAt(newPos) == RABBIT && world->getUnitAt(newPos) == GRASS)
			{
				return newPos;
			}
		}
	}
	return pos;
}