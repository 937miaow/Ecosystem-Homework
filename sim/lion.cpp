#include "lion.h"
#include "empty.h"
#include "rabbit.h"
#include <cstdlib>
#include <ctime>
using namespace std;

State LionUnit::getState()
{
    return LION;
}

State LionUnit::nextState()
{
    round();

    if (age > DLION) // 年龄大于最大年龄，返回EMPTY
    {
        return EMPTY;
    }
    else if (sum[LION] > TMLION) // 周围兔子数大于TMRAB，返回EMPTY
    {
        return EMPTY;
    }
    else if (sum[RABBIT] > 1) // 周围有兔子且有食物，选择一个位置吃掉兔子，并在该位置繁殖狮子
    {
        Position preyPos = findPrey(RABBIT);
        if (preyPos.row != -1 && preyPos.colum != -1)
        {
            world->setUnitAt(preyPos, LION); // 在该位置繁殖狮子
            world->setUnitAt(pos, EMPTY);    // 原位置变为空地
            return LION;
        }
    }
    else if (sum[LION] > 1) // 周围有同种狮子且有食物，选择一个位置吃掉兔子，并在该位置繁殖狮子
    {
        Position preyPos = findPrey(LION);
        if (preyPos.row != -1 && preyPos.colum != -1)
        {
            world->setUnitAt(preyPos, LION); // 在该位置繁殖狮子
            return LION;
        }
    }
    else
    {
        return LION; // 其他情况下保持为狮子
    }
}

void LionUnit::round()
{
    world->sums(pos, sum);
}

Position LionUnit::findPrey(State preyType)
{
    // 查找周围的食物（兔子或空地）
    vector<Position> preyPositions;

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
