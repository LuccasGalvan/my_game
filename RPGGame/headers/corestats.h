//
// Created by Luccas on 23/09/2024.
//

#ifndef CORESTATS_H
#define CORESTATS_H

#include "types.h"

struct CoreStats {
    statustype Strength = 0;
    statustype Intellect = 0;
    statustype Agility = 0;
    statustype Armor = 0;
    statustype ElementRes = 0;

    CoreStats(statustype str, statustype intel, statustype agi, statustype arm, statustype eres)
    : Strength(str), Intellect(intel), Agility(agi), Armor(arm), ElementRes(eres) {}

    CoreStats();

    //right hand side
    CoreStats& operator+=(const CoreStats& rhs);

    CoreStats& operator-=(const CoreStats& rhs);

    CoreStats& operator=(statustype rhs);

};


#endif //CORESTATS_H
