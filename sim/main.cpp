// main.cpp
//  一个简单的生态仿真系统
#include <iostream>
#include <fstream>
using namespace std;
#include "scene.h"

int world_choice = WORLD_OF_FOX; // 默认世界选择

void show_menu()
{
	cout << "##########################################################################################" << endl;
	cout << "##                               * 欢迎进入生态仿真系统 *                               ##" << endl;
	cout << "##########################################################################################" << endl;
	cout << "##                                * 退出系统 *      请按 0                              ##" << endl;
	cout << "##                                * 进入模拟 *      请按 1                              ##" << endl;
	cout << "##                              * 修改配置数据 *    请按 2                              ##" << endl;
	cout << "##########################################################################################" << endl;
	cout << "请输入你的选择：";
}

/****************以下为开始模拟模块代码*******************/
string WorldChoiceShow(int world_choice)
{
	switch (world_choice)
	{
	case WORLD_OF_RABBIT:
		return "兔子世界";
	case WORLD_OF_FOX:
		return "狐狸世界";
	case WORLD_OF_GRASS:
		return "草世界";
	case WORLD_OF_LION:
		return "狮子世界";
	default:
		return "未知世界";
	}
}

void choose_world(int &world_choice)
{
	system("cls");
	cout << "##########################################################################################" << endl;
	cout << "##                             * 生态仿真系统选择世界页面 *                             ##" << endl;
	cout << "##########################################################################################" << endl;
	cout << "##                               * 返回上一级 *      请按 0                             ##" << endl;
	cout << "##                                * 退出系统 *       请按 1                             ##" << endl;
	cout << "##                                * 兔子世界 *       请按 2                             ##" << endl;
	cout << "##                                * 狐狸世界 *       请按 3                             ##" << endl;
	cout << "##                                 * 草世界 *        请按 4                             ##" << endl;
	cout << "##                                * 狮子世界 *        请按 5                            ##" << endl;
	cout << "##########################################################################################" << endl;
	cout << "当前选择的世界是：" << WorldChoiceShow(world_choice) << endl;
	cout << "请输入你的选择：";

	int world_choice_input;
	cin >> world_choice_input;
	switch (world_choice_input)
	{
	case 0:
		break;
	case 1:
		system("pause");
		exit(0);
	case 2:
		world_choice = WORLD_OF_RABBIT;
		break;
	case 3:
		world_choice = WORLD_OF_FOX;
		break;
	case 4:
		world_choice = WORLD_OF_GRASS;
		break;
	case 5:
		world_choice = WORLD_OF_LION;
		break;
	default:
		break;
	}
}

void start_simulation_menu()
{
	int sim_choice = -1;

	while (sim_choice != 0)
	{
		system("cls");
		system("COLOR 0A");
		cout << "##########################################################################################" << endl;
		cout << "##                               * 生态仿真系统模拟菜单 *                               ##" << endl;
		cout << "##########################################################################################" << endl;
		cout << "##                               * 返回上一级 *      请按 0                             ##" << endl;
		cout << "##                                * 退出系统 *       请按 1                             ##" << endl;
		cout << "##                                * 选择世界 *       请按 2                             ##" << endl;
		cout << "##                                * 开始模拟 *       请按 3                             ##" << endl;
		cout << "##########################################################################################" << endl;
		cout << "当前选择的世界是：" << WorldChoiceShow(world_choice) << endl;
		cout << "请输入你的选择：";
		cin >> sim_choice;
		switch (sim_choice)
		{
		case 1:
			system("pause");
			exit(0);
		case 2:
			choose_world(world_choice);
			break;
		case 3:
		{
			World world(world_choice);
			Scene scene(world);
			scene.run();
			system("pause");
			break;
		}
		default:
			break;
		}
	}
}
/***********************************************/

/****************以下为修改配置数据模块代码*******************/
void modify_data()
{
	int mod_choice = -1;
	while (mod_choice != 0)
	{
		system("cls");
		cout << "##########################################################################################" << endl;
		cout << "##                           * 生态仿真系统修改配置数据页面 *                           ##" << endl;
		cout << "##########################################################################################" << endl;
		cout << "##                                * 输入0 以返回上一级 *                                ##" << endl;
		cout << "##                              * 输入对应数字以修改配置 *                              ##" << endl;
		cout << "##########################################################################################" << endl;
		ShowConfig();
		cout << endl;
		cout << "请输入你要修改的配置数据的键值：";
		cin >> mod_choice;
		switch (mod_choice)
		{
		case 0:
			break;
		case DRAB_KEY:
		{
			int value;
			cout << "请输入新的兔子寿命：";
			cin >> value;
			modifyConfig("config.txt", "DRAB", value);
			break;
		}
		case DFOX_KEY:
		{
			int value;
			cout << "请输入新的狐狸寿命：";
			cin >> value;
			modifyConfig("config.txt", "DFOX", value);
			break;
		}
		case DLION_KEY:
		{
			int value;
			cout << "请输入新的狮子寿命：";
			cin >> value;
			modifyConfig("config.txt", "DLION", value);
			break;
		}
		case TMRAB_KEY:
		{
			int value;
			cout << "请输入新的太多的兔子数：";
			cin >> value;
			modifyConfig("config.txt", "TMRAB", value);
			break;
		}
		case TMFOX_KEY:
		{
			int value;
			cout << "请输入新的太多的狐狸数：";
			cin >> value;
			modifyConfig("config.txt", "TMFOX", value);
			break;
		}
		case TMLION_KEY:
		{
			int value;
			cout << "请输入新的太多的狮子数：";
			cin >> value;
			modifyConfig("config.txt", "TMLION", value);
			break;
		}
		case CYCLES_KEY:
		{
			int value;
			cout << "请输入新的仿真总步数：";
			cin >> value;
			modifyConfig("config.txt", "CYCLES", value);
			break;
		}
		default:
			break;
		}
	}
}

void modify_data_menu()
{
	int modmenu_choice = -1;
	readConfig("config.txt");
	while (modmenu_choice != 0)
	{
		system("cls");
		system("COLOR 0A");
		cout << "##########################################################################################" << endl;
		cout << "##                           * 生态仿真系统修改配置数据菜单 *                           ##" << endl;
		cout << "##########################################################################################" << endl;
		cout << "##                               * 返回上一级 *      请按 0                             ##" << endl;
		cout << "##                                * 退出系统 *       请按 1                             ##" << endl;
		cout << "##                                * 修改数据 *       请按 2                             ##" << endl;
		cout << "##########################################################################################" << endl;
		ShowConfig();
		cout << endl;
		cout << "请输入你的选择：";
		cin >> modmenu_choice;
		switch (modmenu_choice)
		{
		case 0:
			break;
		case 1:
			system("pause");
			exit(0);
		case 2:
			modify_data();
			break;
		}
	}
}
/***********************************************/

int main()
{
	system("COLOR 0A");
	int choice = -1;

	while (choice != 0)
	{
		system("cls");
		show_menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			start_simulation_menu();
			break;
		case 2:
			modify_data_menu();
			break;
		default:
			break;
		}
	}
}