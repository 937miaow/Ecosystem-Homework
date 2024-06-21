// world.cpp
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;

#include "basic.h"

#include "empty.h"
#include "grass.h"
#include "rabbit.h"
#include "fox.h"
#include "lion.h"

#include "world.h"

World::World(int index) : curMap(N, vector<State>(N, EMPTY))
{
	initWorld();

	switch (index)
	{
	case WORLD_OF_GRASS:
		worldOfGrass();
		break;

	case WORLD_OF_RABBIT:
		worldOfRabbit();
		break;
	case WORLD_OF_FOX:
		worldOfFox();
		break;
	case WORLD_OF_LION:
		worldOfLion();
		break;
	}
}

void World::initWorld()
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			curMap[i][j] = EMPTY;
}

void World::worldOfGrass()
{
	srand(time(0)); // 使用当前时间作为随机数种子

	// 计算需要生成草的总数，大约占据地图八分之一的位置
	int grass_count = (N * N) / 8;
	int generated_grass = 0;

	while (generated_grass < grass_count)
	{
		int row = rand() % (N - 4) + 2; // 确保不会在最外围生成
		int col = rand() % (N - 4) + 2;

		// 如果当前位置为空，则生成草
		if (curMap[row][col] == EMPTY)
		{
			curMap[row][col] = GRASS;
			++generated_grass;

			// 在周围8格生成草
			for (int i = -1; i <= 1; ++i)
				for (int j = -1; j <= 1; ++j)
					if (!(i == 0 && j == 0)) // 排除自身位置
						if (curMap[row + i][col + j] == EMPTY)
						{
							curMap[row + i][col + j] = GRASS;
							++generated_grass;
						}
		}
	}
	display();
	cout << endl;
}

void World::worldOfRabbit()
{
	srand(time(0)); // 使用当前时间作为随机数种子

	// 随机生成几只兔子
	int rabbit_count = rand() % 3 + 3; // 生成3到5只兔子
	vector<Position> rabbit_positions;

	for (int i = 0; i < rabbit_count; ++i)
	{
		int row = rand() % (N - 4) + 2; // 确保不会在边界生成
		int col = rand() % (N - 4) + 2;

		// 确保不会生成在相同位置
		while (curMap[row][col] == RABBIT)
		{
			row = rand() % (N - 4) + 2;
			col = rand() % (N - 4) + 2;
		}

		curMap[row][col] = RABBIT;
		rabbit_positions.push_back({row, col});

		// 在兔子旁边生成另一只兔子
		int direction = rand() % 4;
		switch (direction)
		{
		case 0:
			row = max(2, row - 1);
			break; // up
		case 1:
			row = min(N - 3, row + 1);
			break; // down
		case 2:
			col = max(2, col - 1);
			break; // left
		case 3:
			col = min(N - 3, col + 1);
			break; // right
		}
		curMap[row][col] = RABBIT;
		rabbit_positions.push_back({row, col});
	}

	// 剩余的位置生成草
	for (int i = 1; i < N - 1; ++i)
	{
		for (int j = 1; j < N - 1; ++j)
		{
			if (curMap[i][j] == EMPTY)
			{
				curMap[i][j] = GRASS;
			}
		}
	}
	display();
	cout << endl;
}

void World::worldOfFox()
{
	// 使用当前时间作为随机数生成器的种子
	srand(time(0));

	// 生成狐狸的位置
	int foxCount = N / 5; // 假设地图大小是 N x N，生成 N/5 只狐狸
	for (int i = 0; i < foxCount; ++i)
	{
		int row = rand() % (N - 4) + 2; // 随机生成的位置范围是 [2, N-3]
		int col = rand() % (N - 4) + 2;

		// 放置狐狸
		curMap[row][col] = FOX;

		// 放置旁边的一只狐狸
		int direction = rand() % 4;
		switch (direction)
		{
		case 0:
			curMap[row - 1][col] = FOX;
			break; // 上
		case 1:
			curMap[row + 1][col] = FOX;
			break; // 下
		case 2:
			curMap[row][col - 1] = FOX;
			break; // 左
		case 3:
			curMap[row][col + 1] = FOX;
			break; // 右
		}

		// 放置周围的兔子
		for (int dr = -1; dr <= 1; ++dr)
		{
			for (int dc = -1; dc <= 1; ++dc)
			{
				if ((dr != 0 || dc != 0) && curMap[row + dr][col + dc] != FOX)
				{
					curMap[row + dr][col + dc] = RABBIT;
				}
			}
		}
	}

	// 填充剩余位置为草
	for (int i = 1; i < N - 1; ++i)
	{
		for (int j = 1; j < N - 1; ++j)
		{
			if (curMap[i][j] == EMPTY)
			{
				curMap[i][j] = GRASS;
			}
		}
	}
	display();
	cout << endl;
}

void World::worldOfLion()
{
	// 随机生成几只狮子，每一只狮子的周围再生成一只狮子，周围生成兔子，剩下的地方生成草
	srand(time(0));

	int numLions = N / 5; // 生成 N/5 只狮子

	for (int k = 0; k < numLions; k++)
	{
		int i = rand() % (N - 4) + 2; // 确定狮子的位置
		int j = rand() % (N - 4) + 2;

		curMap[i][j] = LION; // 在指定位置生成狮子

		// 放置旁边的一只狮子
		int direction = rand() % 4;
		switch (direction)
		{
		case 0:
			curMap[i - 1][j] = LION;
			break; // 上
		case 1:
			curMap[i + 1][j] = LION;
			break; // 下
		case 2:
			curMap[i][j - 1] = LION;
			break; // 左
		case 3:
			curMap[i][j + 1] = LION;
			break; // 右
		}
		// 放置周围的兔子
		for (int dr = -1; dr <= 1; ++dr)
		{
			for (int dc = -1; dc <= 1; ++dc)
			{
				if ((dr != 0 || dc != 0) && curMap[i + dr][j + dc] != FOX)
				{
					curMap[i + dr][j + dc] = RABBIT;
				}
			}
		}
	}

	// 剩余位置生成草
	for (int i = 2; i < N - 2; i++)
	{
		for (int j = 2; j < N - 2; j++)
		{
			if (curMap[i][j] == EMPTY)
			{
				curMap[i][j] = GRASS;
			}
		}
	}
	display();
	cout << endl;
}

void World::update() // 有更新
{
	// 先计算周围生物数目统计结果
	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < N - 1; j++)
		{
			sums(Position{i, j}, cachedSums[i][j]);
		}

	// 更新各单元状态
	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < N - 1; j++)
		{
			LivingUnit *p = locate(i, j);
			curMap[i][j] = p->nextState();
		}
}

void World::display()
{
	for (int i = 0; i < N; ++i)
	{
		cout << endl;
		for (int j = 0; j < N; ++j)
		{
			switch (curMap[i][j]) // 修改了显示方式
			{
			case EMPTY:
				cout << color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED) << '0';
				break;
			case GRASS:
				cout << color(FOREGROUND_GREEN) << 'G';
				break;
			case RABBIT:
				cout << color(FOREGROUND_RED | FOREGROUND_GREEN) << 'R';
				break;
			case FOX:
				cout << color(FOREGROUND_RED) << 'F';
				break;
			case LION:
				cout << color(FOREGROUND_RED | FOREGROUND_BLUE) << 'L';
				break;
			}
		}
	}
	cout << endl
		 << endl;
}

LivingUnit *World::locate(int row, int colum)
{
	switch (curMap[row][colum])
	{
	case EMPTY:
		return (new EmptyUnit(this, row, colum));
		break;
	case GRASS:
		return (new GrassUnit(this, row, colum));
		break;
	case RABBIT:
		return (new RabbitUnit(this, row, colum));
		break;
	case FOX:
		return (new FoxUnit(this, row, colum));
		break;
	case LION:
		return (new LionUnit(this, row, colum));
	default:
		return nullptr; // 新增
	}
}

void World::sums(Position pos, int sum[STATES])
{
	sum[EMPTY] = sum[GRASS] = sum[RABBIT] = sum[FOX] = 0;

	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0)
				continue;
			State state = curMap[pos.row + i][pos.colum + j];
			sum[state]++;
		}
}

void World::setUnitAt(Position pos, State state)
{
	curMap[pos.row][pos.colum] = state;
}

State World::getUnitAt(Position pos)
{
	if (pos.row >= 0 && pos.row < N && pos.colum >= 0 && pos.colum < N)
		return curMap[pos.row][pos.colum];
	else
		return EMPTY;
}
