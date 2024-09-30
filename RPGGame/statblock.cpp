//
// Created by Luccas on 23/09/2024.
//

#include "headers/statblock.h"


    StatBlock::StatBlock(statustype s, statustype i, statustype a, statustype ar, statustype er){
        base.Strength = s;
        base.Intellect = i;
        base.Agility = a;
        base.Armor = ar;
        base.ElementRes = er;
    }

    statustype StatBlock::getBaseSTR(){return base.Strength;}
    statustype StatBlock::getBaseINT(){return base.Intellect;}
    statustype StatBlock::getBaseAGI(){return base.Agility;}
    statustype StatBlock::getBaseARM(){return base.Armor;}
    statustype StatBlock::getBaseRES(){return base.ElementRes;}

    statustype StatBlock::getTotalSTR(){return base.Strength   + statsFromBuffs.Strength;}
    statustype StatBlock::getTotalINT(){return base.Intellect  + statsFromBuffs.Intellect;}
    statustype StatBlock::getTotalAGI(){return base.Agility    + statsFromBuffs.Agility;}
    statustype StatBlock::getTotalARM(){return base.Armor      + statsFromBuffs.Armor;}
    statustype StatBlock::getTotalRES(){return base.ElementRes + statsFromBuffs.ElementRes;}



    std::vector<Buff> Buffs;
    void StatBlock::addNewBuff(Buff b) {
        for (auto& buff : Buffs) {
            if (b.Name == buff.Name) {
                buff.Duration = b.Duration;
                return;
            }
        }
        Buffs.push_back(b);
        recalculate_buffs();
    }

    void StatBlock::increaseStats(statustype s, statustype i, statustype a, statustype ar, statustype er) {
        base.Strength += s;
        base.Intellect += i;
        base.Agility += a;
        base.Armor += ar;
        base.ElementRes += er;
    }

    void StatBlock::increaseStats(CoreStats cs) {
        base += cs;
    }

    void StatBlock::recalculate_buffs() {
        CoreStats tmp_total;

        for (const auto& b : Buffs) {
            if (b.isDebuff) {
                tmp_total -= b.BuffedStats;
            } else {
                tmp_total += b.BuffedStats;
            }
        }

        statsFromBuffs = tmp_total;
    }
