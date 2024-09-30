//
// Created by Luccas on 30/09/2024.
//

#include "headers/playerCharacter.h"

PlayerCharacterDelegate::PlayerCharacterDelegate() : StatBlock(0u, 0u, 0u){
    CurrentLevel = (leveltype)1u;
    CurrentEXP = (exptype)0u;
    EXPTillNextLevel = LEVEL2AT;

    //point well started as regular HP, but it was pointed out it could be recycled for
    //a mana/energy/rage system, and now is treated as a well of points.
    HP = std::make_unique<PointWell>(1u,1u);
}

void PlayerCharacterDelegate::gainEXP(exptype gained_exp)  {
    CurrentEXP += gained_exp;
    while (check_if_lvlup()) {};
}

leveltype PlayerCharacterDelegate::getLevel() const  {
    return CurrentLevel;
}

exptype PlayerCharacterDelegate::getEXP() const {
    return CurrentEXP;
}

exptype PlayerCharacterDelegate::getEXPTillNextLevel() const {
    return EXPTillNextLevel;
}

void PlayerCharacterDelegate::applyBuff(Buff b)  {
    addNewBuff(b);
}

std::vector<Buff> PlayerCharacterDelegate::getBuffList()  { return Buffs; }

bool PlayerCharacterDelegate::check_if_lvlup() {
    //lvl 1 = 0 xp needed
    //lvl 2 = LEVEL2AT (100) xp needed
    //lvl 3 = prev_required * LEVELSCALAR xp needed
    //. . .

    if (CurrentEXP >= EXPTillNextLevel) {
        exptype overflowEXP = CurrentEXP - EXPTillNextLevel;
        CurrentLevel++;
        LevelUp();
        EXPTillNextLevel *= LEVELSCALAR;
        CurrentEXP = 0u;
        gainEXP(overflowEXP);
        return true;
    }
    return false;
}

//WARRIOR
std::string Warrior::getClassName() { return std::string("Warrior"); }

Warrior::Warrior()  : PlayerCharacterDelegate() {
    //MP = std::make_unique<PointWell>(BASEMP, BASEMP);
    //EP = std::make_unique<PointWell>(BASEEP, BASEEP);
    PCCONSTRUCT
}

void Warrior::LevelUp() {
    LEVELUP
        if (CurrentLevel == 2u) {
            Abilities.emplace_back("PowerAttack", 0u, 3u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::STR);

            HP->setMax(1u + HP->getMax());
            HP->increase(1u);

            increaseStats(1u, 0u, 0u);
        }
        else {
            //TODO: think of more abilities and stuff
        }
}

//CLERIC
std::string Cleric::getClassName() { return std::string("Cleric"); }

Cleric::Cleric() : PlayerCharacterDelegate() {
    MP = std::make_unique<PointWell>(BASEMP, BASEMP);
    PCCONSTRUCT

    Abilities.emplace_back("Heal", 2u, 1u, ABILITYTARGET::ALLY, 2u, ABILITYSCALER::INT);
}

void Cleric::LevelUp()  {
    LEVELUP
    if (CurrentLevel == 2u) {
        Abilities.emplace_back("Smite", 2u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALER::INT);
    } else {
        //TODO: think of more abilities and stuff
    }
}

//WIZARD
std::string Wizard::getClassName()  { return std::string("Wizard"); }

Wizard::Wizard()  : PlayerCharacterDelegate() {
    MP = std::make_unique<PointWell>(BASEMP, BASEMP);
    PCCONSTRUCT

        Abilities.emplace_back("Icebolt", 2u, 1u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::INT);
}

void Wizard::LevelUp()  {
    LEVELUP
            if (CurrentLevel == 2u) {
                Abilities.emplace_back("Fireball", 3u, 1u, ABILITYTARGET::ENEMY, 6u, ABILITYSCALER::INT);

                MP->setMax(1u + MP->getMax());
                MP->increase(1u);

                increaseStats(0u, 1u, 0u);
            }
            else {
                //TODO: think of more abilities and stuff
            }
}

//ROGUE
std::string Rogue::getClassName()  { return std::string("Rogue"); }

Rogue::Rogue()  : PlayerCharacterDelegate() {
    EP = std::make_unique<PointWell>(BASEEP, BASEEP);
    PCCONSTRUCT

        Abilities.emplace_back("PreciseAttack", 1u, 1u, ABILITYTARGET::ENEMY, 3u, ABILITYSCALER::AGI);
}

void Rogue::LevelUp()  {
    LEVELUP
        if (CurrentLevel == 2u) {
            Abilities.emplace_back("DaggerThrow", 2u, 2u, ABILITYTARGET::ENEMY, 5u, ABILITYSCALER::AGI);

            EP->setMax(1u + EP->getMax());
            EP->increase(1u);

            increaseStats(0u, 0u, 1u);
        }
        else {
            //TODO: think of more abilities and stuff
        }
}

//BERSERKER
std::string Berserker::getClassName()  { return std::string("Berserker"); }

Berserker::Berserker()  : PlayerCharacterDelegate() {
    EP = std::make_unique<PointWell>(BASEEP, BASEEP);
    RP = std::make_unique<PointWell>(BASERP, (BASERP*100));
    PCCONSTRUCT

        Abilities.emplace_back("Charge", 2u, 1u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::STR);
}

void Berserker::LevelUp()  {
    LEVELUP
        if (CurrentLevel == 2u) {
            Abilities.emplace_back("RAGE", 2u, 2u, ABILITYTARGET::ENEMY, 5u, ABILITYSCALER::STR);

            EP->setMax(1u + EP->getMax());
            EP->increase(1u);

            increaseStats(0u, 0u, 1u);
        }
        else {
            //TODO: think of more abilities and stuff
        }
}

PlayerCharacter::PlayerCharacter(PlayerCharacterDelegate *pc)  : pcclass(pc){
    for (int i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
        EquippedArmor[i] = nullptr;
    }

    for (int j = 0; j < (unsigned long long)WEAPONSLOT::NUM_SLOTS; j++) {
        EquippedWeapons[j] = nullptr;
    }
}

PlayerCharacter::~PlayerCharacter() {
    delete pcclass;
    pcclass = nullptr;
    for (int i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
        if (EquippedArmor[i]) {
            delete EquippedArmor[i];
            EquippedArmor[i] = nullptr;
        }
    }

    for (int j = 0; j < (unsigned long long)WEAPONSLOT::NUM_SLOTS; j++) {
        if (EquippedWeapons[j]) {
            delete EquippedWeapons[j];
            EquippedWeapons[j] = nullptr;
        }
    }
}

void PlayerCharacter::cleanup_backpack()  {
    //puts all items marked to deletion at the end
    const auto to_remove = std::stable_partition(Backpack.begin(), Backpack.end(),
        [](const Item* i) -> bool {return !i->getMarkedForDeletion(); });

    //removes every item starting on the first item marked to deletion till the end of the vector
    std::for_each(to_remove, Backpack.end(), [](Item* i) {delete i;});

    //proper cleanup dealing with the dangling pointers
    Backpack.erase(to_remove, Backpack.end());
}

//getters
std::string PlayerCharacter::getClassName() const { return pcclass->getClassName(); }
leveltype PlayerCharacter::getLevel() const { return pcclass->getLevel(); }
exptype PlayerCharacter::getEXP() const { return pcclass->getEXP(); }
exptype PlayerCharacter::getEXPTillNextLevel() const { return pcclass->getEXPTillNextLevel(); }
welltype PlayerCharacter::getCurrentHP() const { return pcclass->HP->getCurrent(); }
welltype PlayerCharacter::getMaxHP() const { return pcclass->HP->getMax(); }

welltype PlayerCharacter::getCurrentMP() const {
    if (pcclass->MP) {
        return pcclass->MP->getCurrent();
    }
    return 0;
}
welltype PlayerCharacter::getCurrentEP() const {
    if (pcclass->EP) {
        return pcclass->EP->getCurrent();
    }
    return 0;
}
welltype PlayerCharacter::getCurrentRP() const {
    if (pcclass->RP) {
        return pcclass->RP->getCurrent();
    }
    return 0;
}
welltype PlayerCharacter::getMaxMP() const {
    if (pcclass->MP) {
        return pcclass->MP->getMax();
    }
    return 0;
}
welltype PlayerCharacter::getMaxEP() const {
    if (pcclass->EP) {
        return pcclass->EP->getMax();
    }
    return 0;
}
welltype PlayerCharacter::getMaxRP() const {
    if (pcclass->RP) {
        return pcclass->RP->getMax();
    }
    return 0;
}

//getters for base attributes
statustype PlayerCharacter::getBaseSTR() const { return pcclass->getBaseSTR(); }
statustype PlayerCharacter::getBaseINT() const { return pcclass->getBaseINT(); }
statustype PlayerCharacter::getBaseAGI() const { return pcclass->getBaseAGI(); }
statustype PlayerCharacter::getBaseARM() const { return pcclass->getBaseARM(); }
statustype PlayerCharacter::getBaseRES() const { return pcclass->getBaseRES(); }

//getters for total attributes
statustype PlayerCharacter::getSTR() const {
    //get all strength from equipped armor & weapons
    statustype str_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
        if (EquippedArmor[i]) {
            Armor* armor = dynamic_cast<Armor*>(EquippedArmor[i]->_data);
            str_from_armor += armor->Stats.Strength;
        }
    }
    statustype str_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
        if (EquippedWeapons[i]) {
            Weapon* weapon = dynamic_cast<Weapon*>(EquippedWeapons[i]->_data);
            str_from_weapons += weapon->Stats.Strength;
        }
    }
    return pcclass->getTotalSTR() + str_from_armor + str_from_weapons;
}
statustype PlayerCharacter::getINT() const {
    //get all intellect from equipped armor & weapons
    statustype int_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
        if (EquippedArmor[i]) {
            Armor* armor = dynamic_cast<Armor*>(EquippedArmor[i]->_data);
            int_from_armor += armor->Stats.Intellect;
        }
    }
    statustype int_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
        if (EquippedWeapons[i]) {
            Weapon* weapon = dynamic_cast<Weapon*>(EquippedWeapons[i]->_data);
            int_from_weapons += weapon->Stats.Intellect;
        }
    }
    return pcclass->getTotalINT() + int_from_armor + int_from_weapons;
}
statustype PlayerCharacter::getAGI() const {
    //get all agility from equipped armor & weapons
    statustype agi_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
        if (EquippedArmor[i]) {
            Armor* armor = dynamic_cast<Armor*>(EquippedArmor[i]->_data);
            agi_from_armor += armor->Stats.Agility;
        }
    }
    statustype agi_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
        if (EquippedWeapons[i]) {
            Weapon* weapon = dynamic_cast<Weapon*>(EquippedWeapons[i]->_data);
            agi_from_weapons += weapon->Stats.Agility;
        }
    }
    return pcclass->getTotalAGI() + agi_from_armor + agi_from_weapons;
}
statustype PlayerCharacter::getARM() const {
    //get all armor from equipped armor & weapons
    statustype arm_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
        if (EquippedArmor[i]) {
            Armor* armor = dynamic_cast<Armor*>(EquippedArmor[i]->_data);
            arm_from_armor += armor->Stats.Armor;
        }
    }
    statustype arm_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
        if (EquippedWeapons[i]) {
            Weapon* weapon = dynamic_cast<Weapon*>(EquippedWeapons[i]->_data);
            arm_from_weapons += weapon->Stats.Armor;
        }
    }
    return pcclass->getTotalARM() + arm_from_armor + arm_from_weapons;
}
statustype PlayerCharacter::getRES() const {
    //get all element resistance from equipped armor & weapons
    statustype elres_from_armor = 0;
    for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++) {
        if (EquippedArmor[i]) {
            Armor* armor = dynamic_cast<Armor*>(EquippedArmor[i]->_data);
            elres_from_armor += armor->Stats.ElementRes;
        }
    }
    statustype elres_from_weapons = 0;
    for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
        if (EquippedWeapons[i]) {
            Weapon* weapon = dynamic_cast<Weapon*>(EquippedWeapons[i]->_data);
            elres_from_weapons += weapon->Stats.ElementRes;
        }
    }
    return pcclass->getTotalRES() + elres_from_armor + elres_from_weapons;
}

//getters for lists
std::vector<Ability> PlayerCharacter::getAbilityList() const { return pcclass->Abilities; }
std::vector<Buff> PlayerCharacter::getBuffList() const { return pcclass->getBuffList(); }
std::vector<Item *> PlayerCharacter::getBackpack() const { return Backpack; }

EquipmentDelegate *PlayerCharacter::getEquippedArmor(unsigned long long i) const {
    if (!EquippedArmor[i]) return nullptr;
    return (dynamic_cast<Armor*>(EquippedArmor[i]->_data));
}

EquipmentDelegate *PlayerCharacter::getEquippedWeapon(unsigned long long i) const {
    if (!EquippedWeapons[i]) return nullptr;

    return (dynamic_cast<Weapon*>(EquippedWeapons[i]->_data));
}

//modifiers
void PlayerCharacter::gainEXP(exptype ammount) { pcclass->gainEXP(ammount); }
void PlayerCharacter::takeDMG(welltype ammount) { pcclass->HP->reduce(ammount); }
void PlayerCharacter::Heal(welltype ammount)  { pcclass->HP->increase(ammount); }
void PlayerCharacter::applyBuff(Buff buff)  {
    pcclass->applyBuff(buff);
}
