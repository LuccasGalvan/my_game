//
// Created by Luccas on 30/09/2024.
//

#ifndef POINTWELL_H
#define POINTWELL_H

#include "types.h"
//Point well started as a simple HP system for the characters, but it was turned into an _anything that involves points_
//system, it will probably futurely be used for mana/rage/energy systems as well. haha. as .... well.

class PointWell{
public:
    PointWell();

    PointWell(welltype c, welltype m);

    bool setMax(welltype newMax);

    welltype getMax();

    void reduce(welltype ammount);

    void increase(welltype ammount);

    welltype getCurrent();

    bool isFull();

private:
    welltype Current;
    welltype Max;
};



#endif //POINTWELL_H
