#include "fox.h"
#include "empty.h"
#include "rabbit.h"
#include <cstdlib>
#include <ctime>

State FoxUnit::getState()
{
	return FOX;
}

State FoxUnit::nextState()
{
	round();

	if (age > DFOX) // 年龄大于最大年龄，返回EMPTY
	{
		return EMPTY;
	}
	else if (sum[FOX] > TMFOX) // 周围狐狸数大于TMRAB，返回EMPTY
	{
		return EMPTY;
	}
	else if (sum[RABBIT] > 1) // 周围有兔子且有食物，选择一个位置吃掉兔子，并在该位置繁殖狐狸
	{
		Position preyPos = findPrey(RABBIT);
		if (preyPos.row != -1 && preyPos.colum != -1)
		{
			world->setUnitAt(preyPos, FOX); // 在该位置繁殖狐狸
			world->setUnitAt(pos, EMPTY);	// 原位置变为空地
			return FOX;
		}
	}
	else if (sum[FOX] > 1) // 周围有同种狐狸且有食物，选择一个位置吃掉兔子，并在该位置繁殖狐狸
	{
		Position preyPos = findPrey(FOX);
		if (preyPos.row != -1 && preyPos.colum != -1)
		{
			world->setUnitAt(preyPos, FOX); // 在该位置繁殖狐狸
			return FOX;
		}
	}
	else
	{
		return FOX; // 其他情况下保持为狐狸
	}
}

void FoxUnit::round()
{
	world->sums(pos, sum);
}

Position FoxUnit::findPrey(State preyType)
{
	// 查找周围的食物（兔子或空地）
	std::vector<Position> preyPositions;

	for (int i = pos.row - 1; i <= pos.row + 1; ++i)
	{
		for (int j = pos.colum - 1; j <= pos.colum + 1; ++j)
		{
			if (i == pos.row && j == pos.colum)
				continue;

			if (world->getUnitAt(Position{i, j}) == preyType)
			{
				preyPositions.push_back(Position{i, j});
			}
		}
	}

	// 随机选择一个食物位置返回
	if (!preyPositions.empty())
	{
		int index = rand() % preyPositions.size();
		return preyPositions[index];
	}

	return Position{-1, -1}; // 没有找到合适的食物位置
}
