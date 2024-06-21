// living.h
#ifndef _LIVING_H_
#define _LIVING_H_

#include "basic.h"
#include "world.h"

class World; // 前向声明 World 类

class LivingUnit // 单元格对象，分为 空的，草，兔、狐狸 等
{
public:
	virtual State getState() = 0;  // 获取生物所在位置的当前仿真时刻状态
	virtual State nextState() = 0; // 该单元下一个仿真时刻的状态
	virtual void round() = 0;	   // 周围态势，得到各类生物数目统计

protected:
	Position pos;	 // 所在的位置
	World *world;	 // 所在的世界
	int sum[STATES]; // 所在位置附近的各类生物数目统计

	// 新增保护方法
	// 通用功能给子类调用 避免在子类中重复代码
	// 同时，World类会在更新循环开始时计算每个位置的周围生物数目，并将结果缓存起来。
	// 每个单元在更新状态时会使用缓存的结果，从而避免了重复计算
	void updateSums()
	{
		for (int i = 0; i < STATES; ++i)
		{
			sum[i] = world->cachedSums[pos.row][pos.colum][i];
		}
	}
};
#endif