// basic.h
#ifndef _BASIC_H_
#define _BASIC_H_

// 和程序实现相关的一些基础的常量、函数声明

enum State
{
    EMPTY,
    GRASS,
    RABBIT,
    FOX,
    LION,
    STATES
};

enum Config
{
    Placeholder, // 占位符
    DRAB_KEY,
    DFOX_KEY,
    DLION_KEY,
    TMRAB_KEY,
    TMFOX_KEY,
    TMLION_KEY,
    CYCLES_KEY
};

extern int DRAB;   // 兔子的寿命
extern int DFOX;   // 狐狸的寿命
extern int DLION;  // 狮子的寿命
extern int TMRAB;  // 太多的兔子数
extern int TMFOX;  // 太多的狐狸数
extern int TMLION; // 太多的狮子数
extern int CYCLES; // 仿真总步数
const int N = 40;  // 世界的大小

void readConfig(const char *filename);
void modifyConfig(const char *filename, const char *key, int value);
void ShowConfig();

struct Position // 位置
{
    int row;   // 行
    int colum; // 列
};

#include <iostream>
using namespace std;

// 用于在控制台窗口显示彩色的字体
#include <windows.h>
struct color
{
    color(WORD attribute) : m_color(attribute){};
    WORD m_color; // 颜色值
};

// 使用模板函数
template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits> &
operator<<(std::basic_ostream<_Elem, _Traits> &i, const color &c)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出句柄
    SetConsoleTextAttribute(hStdout, c.m_color);      // 设置文本颜色
    return i;
}

#endif