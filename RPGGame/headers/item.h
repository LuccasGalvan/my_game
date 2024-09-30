//
// Created by Luccas on 30/09/2024.
//

#ifndef ITEM_H
#define ITEM_H

#include "types.h"
#include "corestats.h"
#include "buff.h"

#include <string>
#include <typeinfo>
#include <iostream>//for testing purposes

class ItemDelegate {
public:
	std::string Name;
	virtual const char* GetType() = 0; //so you cant instantiate
protected:
	ItemDelegate(std::string name);
};

#define GETTYPE virtual const char* GetType() override { return typeid(*this).name(); }

class Potion final : public ItemDelegate {
public:
	Buff* buff;
	welltype healAmmount;
	itemCount Quantity;

	~Potion();
	GETTYPE
private:
	Potion(std::string name, welltype hp_heal = 1u, itemCount quant = 1u, Buff* buff = nullptr);

	friend class ItemFactory;
};

class EquipmentDelegate : public ItemDelegate {
public:
	const idtype UniqueId;
	CoreStats Stats;

protected:
	EquipmentDelegate(std::string name, CoreStats cstats);
};

//num_slot is for array indexing purposes, so it has the actual number of items on the ARMORSLOT enum on playercharacter
enum class ARMORSLOT { HELMET, CHEST, LEGS, FEET, GLOVES, RING1, RING2, NECK, NUM_SLOTS };

//final = no one else can inherit from armor
class Armor final : public EquipmentDelegate{
public:
	ARMORSLOT Slot;

	GETTYPE

private:
	Armor(std::string name, CoreStats cstats, ARMORSLOT slot);

	Armor() = delete; //no default constructor
	Armor(const Armor&) = delete; //no copying
	Armor(const Armor&&) = delete; //no moving

	friend class ItemFactory;
};

enum class WEAPONSLOT{ MELEE, RANGED, NUM_SLOTS };

class Weapon final : public EquipmentDelegate {
public:
	WEAPONSLOT Slot;
	dmgtype minDmg;
	dmgtype maxDmg;
	bool isTwoHanded;

	GETTYPE

private:
	Weapon(std::string name, CoreStats cstats, WEAPONSLOT slot, dmgtype min, dmgtype max, bool twohanded = false);

	Weapon() = delete; //no default constructor
	Weapon(const Weapon&) = delete; //no copying
	Weapon(const Weapon&&) = delete; //no moving

	friend class ItemFactory;
};

//use this on runtime code
class Item {
public:
	const ItemDelegate* getData();
	~Item();

	bool getMarkedForDeletion() const;
private:
	ItemDelegate* _data;
	bool marked_for_deletion = false;
	Item(ItemDelegate* item);
	friend class ItemFactory;
	friend class PlayerCharacter;

	friend std::ostream& operator<<(std::ostream& os, const Item& item) {
		Armor* tmp_cast = dynamic_cast<Armor*>(item._data);
		if(tmp_cast) {
			return os << tmp_cast->Name << "\n - (A: " << tmp_cast->Stats.Armor << ")" << "\n - (ER: " << tmp_cast->Stats.ElementRes << ")\n";
		}
		Weapon* tmp_cast2 = dynamic_cast<Weapon*>(item._data);
		if(tmp_cast2) {
			return os << tmp_cast2->Name << "\n - (min dmg: " << tmp_cast2->minDmg << ")" << "\n - (max dmg: " << tmp_cast2->maxDmg << ")\n";
		}
		Potion* tmp_cast3 = dynamic_cast<Potion*>(item._data);
		if(tmp_cast3) {
			return os << tmp_cast3->Name << "\n - (Quantity: " << tmp_cast3->Quantity << ")\n";
		}
		return os;
	}

	static void free(ItemDelegate* data);
};
#endif //ITEM_H
