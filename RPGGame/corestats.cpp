//
// Created by Luccas on 23/09/2024.
//

#include "headers/corestats.h"

CoreStats::CoreStats() {
        statustype Strength = 0;
        statustype Intellect = 0;
        statustype Agility = 0;
        statustype Armor = 0;
        statustype ElementRes = 0;
}

CoreStats& CoreStats::operator=(const statustype rhs) {
        this->Strength = rhs;
        this->Intellect = rhs;
        this->Agility = rhs;
        this->Armor = rhs;
        this->ElementRes = rhs;

        return *this;
}

CoreStats& CoreStats::operator-=(const CoreStats &rhs) {
        CoreStats tmp = *this;

        this->Strength -= rhs.Strength;
        this->Intellect -= rhs.Intellect;
        this->Agility -= rhs.Agility;
        this->Armor -= rhs.Armor;
        this->ElementRes -= rhs.ElementRes;

        if (this->Strength > tmp.Strength)
                this->Strength = 0u;

        if (this->Intellect > tmp.Intellect)
                this->Intellect = 0u;

        if (this->Agility > tmp.Agility)
                this->Agility = 0u;

        if (this->Armor > tmp.Armor)
                this->Armor = 0u;

        if (this->ElementRes > tmp.ElementRes)
                this->ElementRes = 0u;

        return *this;
}

CoreStats& CoreStats::operator+=(const CoreStats &rhs) {
        this->Strength += rhs.Strength;
        this->Intellect += rhs.Intellect;
        this->Agility += rhs.Agility;
        this->Armor += rhs.Armor;
        this->ElementRes += rhs.ElementRes;

        return *this;
}
