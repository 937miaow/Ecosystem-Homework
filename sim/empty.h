// empty.h
#ifndef EMPTY_H
#define EMPTY_H
#include "living.h"

class EmptyUnit : public LivingUnit
{
public:
	EmptyUnit(World *const w, int r, int c)
	{
		pos.row = r;
		pos.colum = c;
		world = w;
	}

	State getState();
	State nextState();
	void round();
};
#endif