//
// Created by Luccas on 30/09/2024.
//

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "item.h"
#include "types.h"
#include "playerCharacter.h"


class ItemFactory {
public:
	static Item* createArmor(std::string name, CoreStats cstats, ARMORSLOT slot);

	static Item* createWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, dmgtype min, dmgtype max, bool twohanded = false);

	static Item* createPotion(std::string name, welltype heal = 1u, itemCount quant = 1u, Buff* buff = nullptr);

	//equips a weapon or armor and returns true :)
	//if theres an item already equipped in that slot, puts old item in the backpack
	static bool equip(Item* item_to_equip, PlayerCharacter* player);

	static bool use(Item* item_to_use, PlayerCharacter* player);

	static bool moveToBackpack(Item* item_to_move, PlayerCharacter* player);
};



#endif //ITEMFACTORY_H
