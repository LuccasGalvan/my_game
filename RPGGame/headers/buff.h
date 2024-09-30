//
// Created by Luccas on 30/09/2024.
//

#ifndef BUFF_H
#define BUFF_H


#include "types.h"
#include "corestats.h"

#include <string>


struct Buff {

    Buff(std::string name = "unnamed", statustype str = 0u, statustype intel = 0u, statustype agi = 0u,
        statustype ar = 0u, statustype er = 0u, durationtype dur = 2u, bool isdebuff = false);

    Buff(std::string name, CoreStats cs, durationtype dur = 2u, bool isdebuff = false);


    std::string Name;
    durationtype Duration;
    bool isDebuff;

    CoreStats BuffedStats;
};


#endif //BUFF_H
