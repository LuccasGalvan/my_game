//
// Created by Luccas on 23/09/2024.
//

#ifndef STATBLOCK_H
#define STATBLOCK_H

#include "types.h"
#include "buff.h"
#include "corestats.h"

#include <vector>

class StatBlock{
    CoreStats base;
    CoreStats statsFromBuffs;
public:
    explicit StatBlock(statustype s = 1u, statustype i = 1u, statustype a = 1u, statustype ar = 0u, statustype er = 0u);

    statustype getBaseSTR();
    statustype getBaseINT();
    statustype getBaseAGI();
    statustype getBaseARM();
    statustype getBaseRES();

    statustype getTotalSTR();
    statustype getTotalINT();
    statustype getTotalAGI();
    statustype getTotalARM();
    statustype getTotalRES();


protected:
    std::vector<Buff> Buffs;
    void addNewBuff(Buff b);

    void increaseStats(statustype s = 0u, statustype i = 0u, statustype a = 0u, statustype ar = 0u, statustype er = 0u);

    void increaseStats(CoreStats cs);

private:
    void recalculate_buffs();
};

#endif //STATBLOCK_H
