//
// Created by Luccas on 30/09/2024.
//

#include "headers/ability.h"

Ability::Ability(std::string name, abilityType cost, abilityType cd,
    ABILITYTARGET t, abilityType hpe, ABILITYSCALER s) :
    Name(name), Cost(cost), Cooldown(cd), Target(t), HpEffect(hpe), Scaler(s) {

}