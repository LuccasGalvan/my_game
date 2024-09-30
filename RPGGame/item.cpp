//
// Created by Luccas on 30/09/2024.
//

#include "headers/item.h"

static idtype EQUIPMENTUNIQUEIDITERATOR = 0u;

EquipmentDelegate::EquipmentDelegate(std::string name, CoreStats cstats)
	: ItemDelegate(name), Stats(cstats), UniqueId(++EQUIPMENTUNIQUEIDITERATOR) {

}

ItemDelegate::ItemDelegate(std::string name) : Name(name) {}

//Potion destructor & constructor
Potion::~Potion() {
    free(buff);
}

Potion::Potion(std::string name, welltype hp_heal, itemCount quant, Buff *buff)
		: ItemDelegate(name), healAmmount(hp_heal), Quantity(quant), buff(buff) {

}

//Armor constructor
Armor::Armor(std::string name, CoreStats cstats, ARMORSLOT slot): EquipmentDelegate(name, cstats), Slot(slot) {

}

//Weapon constructor
Weapon::Weapon(std::string name, CoreStats cstats, WEAPONSLOT slot, dmgtype min, dmgtype max, bool twohanded)
		: EquipmentDelegate(name, cstats), Slot(slot), minDmg(min), maxDmg(max), isTwoHanded(twohanded) {

}

const ItemDelegate *Item::getData() { return _data; }

Item::~Item() {
	free(_data);
}

bool Item::getMarkedForDeletion() const { return marked_for_deletion; }

Item::Item(ItemDelegate *item) : _data(item) {}

void Item::free(ItemDelegate *data) {
	if (data) {
		delete data;
		data = nullptr;
	}
}

