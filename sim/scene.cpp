// scene.cpp

#include <iostream>
using namespace std;

#include "scene.h"
#include "living.h"

Scene::Scene(World &w)
{
	world = &w;
}

void Scene::update()
{
	world->update();
}

void Scene::display()
{
	world->display();
}

void Scene::run()
{
	int run_choice = -1;
	int i = 0;
	while (run_choice != 0 && i < CYCLES)
	{
		cout << color(FOREGROUND_GREEN) << "* 0 - 退出模拟 *  * 1 - 退出系统 *  * 2 - 继续模拟 *" << endl;
		cout << color(FOREGROUND_GREEN) << "请输入你的选择：";
		cin >> run_choice;
		switch (run_choice)
		{
		case 0:
			return;
		case 1:
			system("pause");
			exit(0);
		case 2:
			update();
			display();
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
		}
		++i;
	}
	cout << color(FOREGROUND_GREEN) << "已达到最大步数，本轮模拟结束！！！" << endl
		 << endl;
}