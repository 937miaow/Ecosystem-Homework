// world.h

#ifndef _WORLD_H_
#define _WORLD_H_

#include "basic.h"
#include <vector>
#include <array>
// 与程序内部实现相关的一些变量定义

typedef vector<vector<State>> Map;

class LivingUnit;
class EmptyUnit;
class GrassUnit;
class RabbitUnit;
class FoxUnit;

enum SimWorld
{
	WORLD_OF_GRASS,
	WORLD_OF_RABBIT,
	WORLD_OF_FOX,
	WORLD_OF_LION
}; // 仿真的世界

class World
{
public:
	World(int index);
	void update();							   // 更新世界
	void display();							   // 显示世界
	void sums(Position pos, int sum[STATES]);  // 指定位置周围的各类生物的总数的列表，返回结果保存在数组int sum[STATES]中
	int cachedSums[N][N][STATES];			   // 新增 缓存周围生物数目统计结果
	void setUnitAt(Position pos, State state); // 新增 设置指定位置的生物状态
	State getUnitAt(Position pos);			   // 新增 获取指定位置的生物状态

private:
	void worldOfGrass();					// 配置青草的世界
	void worldOfRabbit();					// 配置兔子的世界
	void worldOfFox();						// 配置狐狸的世界
	void worldOfLion();						// 新增 配置狮子的世界
	void initWorld();						// 初始化世界
	LivingUnit *locate(int row, int colum); // 根据指定位置返回指向存在于该位置的对象的指针
	vector<vector<State>> curMap;			// 当前的世界地图 修改为vector 提升内存管理效率
};

#endif