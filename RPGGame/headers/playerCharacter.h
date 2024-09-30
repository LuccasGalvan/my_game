//
// Created by Luccas on 30/09/2024.
//

#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#pragma once

#include "types.h"
#include "item.h"
#include "statblock.h"
#include "pointwell.h"
#include "ability.h"

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

//macro for initializing character stats
#define PCCONSTRUCT \
HP->setMax(BASEHP);\
HP->increase(BASEHP);\
if(MP){ \
MP->setMax(BASEMP); \
MP->increase(BASEMP); \
}\
increaseStats(BASESTR, BASEINT, BASEAGI);

//macro for the levelup function
//doesn't full heal on lvl up, only gives you however much you gained on lvl up
#define LEVELUP \
HP->setMax((welltype)((BASEHP / 2.f) + HP->getMax()));\
HP->increase((welltype)(BASEHP / 2.f));\
if(MP){ \
MP->setMax((welltype)((BASEMP / 2.f) + MP->getMax()));\
MP->increase((welltype)(BASEMP / 2.f));\
}\
if(EP){ \
EP->setMax((welltype)((BASEEP / 2.f) + EP->getMax()));\
EP->increase((welltype)(BASEEP / 2.f));\
}\
increaseStats((statustype)((BASESTR + 1u) / 2.f), (statustype)((BASEINT + 1u) / 2.f), (statustype)((BASEAGI + 1u) / 2.f));

class PlayerCharacterDelegate : public StatBlock{
public:
	static const leveltype LEVELSCALAR = 2u; //necessary xp for level up multiplier
	static const leveltype LEVEL2AT = 100u; //necessary xp for lvl 2

	PlayerCharacterDelegate();

	void gainEXP(exptype gained_exp);

	leveltype getLevel() const;

	exptype getEXP() const;

	exptype getEXPTillNextLevel() const;

	void applyBuff(Buff b);

	std::vector<Buff> getBuffList();

	virtual void LevelUp() = 0;
	virtual std::string getClassName() = 0;

	std::unique_ptr<PointWell> HP; //Hit points
	std::unique_ptr<PointWell> MP; //Mana points
	std::unique_ptr<PointWell> EP; // Energy points
	std::unique_ptr<PointWell> RP; // Rage points

	std::vector<Ability> Abilities;


protected:
	leveltype CurrentLevel;
	exptype CurrentEXP;
	exptype EXPTillNextLevel;

	bool check_if_lvlup();
};

//macro for class creation, to simplify the addition of new classes
//commented because ill maybe implement monsters like this,
//but the skill tree system wont work with macros.

//#define CHARACTERCLASS(classname, basehp, basestr, baseint, baseagi)
//class classname : public PlayerCharacterDelegate {
//public:
//	static const welltype BASEHP = (welltype)basehp;
//	static const statustype BASESTR = (statustype)basestr;
//	static const statustype BASEINT = (statustype)baseint;
//	static const statustype BASEAGI = (statustype)baseagi;
//	std::string getClassName() override { return std::string(#classname); }
//	classname() PCCONSTRUCT
//private:
//	LEVELUP
//};

//CHARACTERCLASS(Warrior, 18, 6, 2, 2)
//CHARACTERCLASS(Rogue, 12, 3, 3, 5)
//CHARACTERCLASS(Wizard, 10, 1, 8, 1)
//CHARACTERCLASS(Cleric, 14, 3, 5, 1)
//CHARACTERCLASS(Berserker, 20, 7, 2, 3) //meant as an easteregg, supposed to add a secret code to get access to this class later


class Warrior : public PlayerCharacterDelegate {
public:
	static constexpr welltype BASEHP = (welltype)18u;
	static constexpr welltype BASEMP = (welltype)0u;
	static constexpr welltype BASEEP = (welltype)0u;
	static constexpr welltype BASERP = (welltype)0u;
	static constexpr statustype BASESTR = (statustype)6u;
	static constexpr statustype BASEINT = (statustype)2u;
	static constexpr statustype BASEAGI = (statustype)2u;
	std::string getClassName() override;
	Warrior();
private:
	void LevelUp() override;
};

class Cleric : public PlayerCharacterDelegate {
public:
	static constexpr welltype BASEHP = (welltype)14u;
	static constexpr welltype BASEMP = (welltype)10u;
	static constexpr welltype BASEEP = (welltype)0u;
	static constexpr welltype BASERP = (welltype)0u;
	static constexpr statustype BASESTR = (statustype)3u;
	static constexpr statustype BASEINT = (statustype)5u;
	static constexpr statustype BASEAGI = (statustype)1u;
	std::string getClassName() override;
	Cleric();
private:
	void LevelUp() override;
};

class Wizard : public PlayerCharacterDelegate {
public:
	static constexpr welltype BASEHP = (welltype)10u;
	static constexpr welltype BASEMP = (welltype)14u;
	static constexpr welltype BASEEP = (welltype)0u;
	static constexpr welltype BASERP = (welltype)0u;
	static constexpr statustype BASESTR = (statustype)1u;
	static constexpr statustype BASEINT = (statustype)8u;
	static constexpr statustype BASEAGI = (statustype)2u;
	std::string getClassName() override;
	Wizard();
private:
	void LevelUp() override;
};

class Rogue : public PlayerCharacterDelegate {
public:
	static constexpr welltype BASEHP = (welltype)12u;
	static constexpr welltype BASEMP = (welltype)0u;
	static constexpr welltype BASEEP = (welltype)12u;
	static constexpr welltype BASERP = (welltype)0u;
	static constexpr statustype BASESTR = (statustype)4u;
	static constexpr statustype BASEINT = (statustype)2u;
	static constexpr statustype BASEAGI = (statustype)6u;
	std::string getClassName() override;
	Rogue();
private:
	void LevelUp() override;
};

class Berserker : public PlayerCharacterDelegate {
public:
	static constexpr welltype BASEHP = (welltype)22u;
	static constexpr welltype BASEMP = (welltype)0u;
	static constexpr welltype BASEEP = (welltype)10u;
	static constexpr welltype BASERP = (welltype)1u;
	static constexpr statustype BASESTR = (statustype)4u;
	static constexpr statustype BASEINT = (statustype)2u;
	static constexpr statustype BASEAGI = (statustype)6u;
	std::string getClassName() override;
	Berserker();
private:
	void LevelUp() override;
};

class PlayerCharacter {
	PlayerCharacterDelegate* pcclass;

	//unsigned long long cause compiler wanted it
	Item* EquippedArmor[(unsigned long long)ARMORSLOT::NUM_SLOTS];
	Item* EquippedWeapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];

	std::vector<Item*> Backpack;
	void cleanup_backpack();

	friend class ItemFactory;
public:
	PlayerCharacter(PlayerCharacterDelegate* pc);

	~PlayerCharacter();

	//getters
	std::string getClassName() const;
	leveltype getLevel() const;
	exptype getEXP() const;
	exptype getEXPTillNextLevel() const;
	welltype getCurrentHP() const;
	welltype getMaxHP() const;
	welltype getCurrentMP() const;
	welltype getCurrentEP() const;
	welltype getCurrentRP() const;
	welltype getMaxMP() const;
	welltype getMaxEP() const;
	welltype getMaxRP() const;
	statustype getBaseSTR() const;
	statustype getBaseINT() const;
	statustype getBaseAGI() const;
	statustype getBaseARM() const;
	statustype getBaseRES() const;
	statustype getSTR() const;
	statustype getINT() const;
	statustype getAGI() const;
	statustype getARM() const;
	statustype getRES() const;

	std::vector<Ability> getAbilityList() const;
	std::vector<Buff> getBuffList() const;
	std::vector<Item*> getBackpack() const;

	EquipmentDelegate* getEquippedArmor(unsigned long long i) const;

	EquipmentDelegate* getEquippedWeapon(unsigned long long i) const;

	//modifiers
	void gainEXP(exptype ammount);
	void takeDMG(welltype ammount);
	void Heal(welltype ammount);
	void applyBuff(Buff buff);

	//deleted constructors
	PlayerCharacter() = delete;
	PlayerCharacter(const PlayerCharacter&) = delete;
	PlayerCharacter(const PlayerCharacter&&) = delete;
};

#endif //PLAYERCHARACTER_H