//
// Created by Luccas on 30/09/2024.
//

#include "headers/pointwell.h"

PointWell::PointWell() {Current = 1u; Max = 1u;}

PointWell::PointWell(welltype c, welltype m){
    Current = c;
    Max = m;

    if(Current > Max){
        Current = Max;
    }
}


bool PointWell::setMax(welltype newMax){
    if(newMax < 1)
        return false;

    Max = newMax;

    if(Current > Max)
        Current = Max;

    return true;
}

welltype PointWell::getMax(){
    return Max;
}

void PointWell::reduce(welltype ammount){
    if(ammount > (Current)){
        Current = 0;
        return;
    }

    Current -= ammount;
}

void PointWell::increase(welltype ammount){
    if((ammount + Current) > Max){
        Current = Max;
        return;
    }

    Current += ammount;
}

welltype PointWell::getCurrent(){
    return Current;
}

bool PointWell::isFull() {
    return (getCurrent() == getMax());
}

