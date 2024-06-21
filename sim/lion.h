#ifndef LION_H
#define LION_H

#include "living.h"

class LionUnit : public LivingUnit
{
public:
    LionUnit(World *w, int r, int c, int a = 0) : age(a)
    {
        pos.row = r;
        pos.colum = c;
        world = w;
    }

    State getState() override;
    State nextState() override;
    void round() override;
    Position findPrey(State preyType);

protected:
    int age;
};

#endif // LION_H
