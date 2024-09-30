//
// Created by Luccas on 30/09/2024.
//

#ifndef ABILITY_H
#define ABILITY_H

#include "types.h"

#include <string>

enum class ABILITYTARGET { SELF, ALLY, ENEMY };
enum class ABILITYSCALER { NONE, STR, INT, AGI };

struct Ability {
    Ability(std::string name, abilityType cost, abilityType cd, ABILITYTARGET t, abilityType hpe, ABILITYSCALER s);
    std::string Name = "unnamed";
    abilityType Cost = 0u; //assume mp if there is a cost for now, will add logic for other types of points like energy or rage
    abilityType Cooldown = 1u; //number of rounds you have to wait
    ABILITYTARGET Target = ABILITYTARGET::SELF;
    abilityType HpEffect = 1u;
    ABILITYSCALER Scaler = ABILITYSCALER::NONE;
};

#endif //ABILITY_H
