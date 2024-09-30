//
// Created by Luccas on 30/09/2024.
//

#include "headers/buff.h"

Buff::Buff(std::string name, statustype str, statustype intel, statustype agi, statustype ar,
    statustype er, durationtype dur, bool isdebuff) : Name(name), Duration(dur), isDebuff(isdebuff){
    BuffedStats.Strength = str;
    BuffedStats.Intellect = intel;
    BuffedStats.Agility = agi;
    BuffedStats.Armor = ar;
    BuffedStats.ElementRes = er;

}

Buff::Buff(std::string name, CoreStats cs, durationtype dur, bool isdebuff): Name(name), Duration(dur), isDebuff(isdebuff) {
    Name = "unnamed";
    BuffedStats = cs;
}

