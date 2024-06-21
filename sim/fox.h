// fox.h
#ifndef FOX_H
#define FOX_H
#include "living.h"

class FoxUnit : public LivingUnit
{
public:
	FoxUnit(World *w, int r, int c, int a = 0) : age(a)
	{
		pos.row = r;
		pos.colum = c;
		world = w;
	}
	State getState();
	State nextState();
	void round();
	Position findPrey(State preyType);

protected:
	int age;
};
#endif