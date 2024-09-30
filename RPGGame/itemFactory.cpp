//
// Created by Luccas on 30/09/2024.
//

#include "headers/itemFactory.h"


Item *ItemFactory::createArmor(std::string name, CoreStats cstats, ARMORSLOT slot) {
    Item* temp_item = new Item(new Armor(name, cstats, slot));
    return temp_item;
}

Item *ItemFactory::createWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot,
    dmgtype min, dmgtype max, bool twohanded)  {
    Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
    return temp_item;
}

Item *ItemFactory::createPotion(std::string name, welltype heal, itemCount quant, Buff *buff)  {
    //ternary operator so if quant = 0, itll create 1 anyway, otherwise itll pass the value
    Item* temp_item = new Item(new Potion(name, heal, (quant == 0) ? 1 : quant, buff));
    return temp_item;
}

bool ItemFactory::equip(Item *item_to_equip, PlayerCharacter *player)  {
    //checking if its a null pointer
    if (!item_to_equip->getData() || !item_to_equip || !player)
        return false;

    Armor* armor = dynamic_cast<Armor*>(item_to_equip->_data);
    if (armor) {
        unsigned long long slot_num = (unsigned long long)armor->Slot;
        if (player->EquippedArmor[slot_num]) {
            //move old item to backpack
            moveToBackpack(player->EquippedArmor[slot_num], player);
            //equips new armor at slot_num
            player->EquippedArmor[slot_num] = item_to_equip;
        }
        else {
            player->EquippedArmor[slot_num] = item_to_equip;
        }

        return true;
    }

    Weapon* weapon = dynamic_cast<Weapon*>(item_to_equip->_data);
    if (weapon) {
        unsigned long long slot_num = (unsigned long long)weapon->Slot;
        if (player->EquippedWeapons[slot_num]) {
            //move old item to backpack
            moveToBackpack(player->EquippedWeapons[slot_num], player);
            //equips new armor at slot_num
            player->EquippedWeapons[slot_num] = item_to_equip;
        }
        else {
            player->EquippedWeapons[slot_num] = item_to_equip;
        }

        return true;
    }
    return false; //something bad happened if reached here cause you cant even instantiate an equipment that isnt armor or weapon
}

bool ItemFactory::use(Item *item_to_use, PlayerCharacter *player){
    //checking if its a null pointer
    if (!item_to_use->getData() || !item_to_use || !player)
        return false;

    Potion* potion = dynamic_cast<Potion*>(item_to_use->_data);
    if (potion) {
        if (potion->buff) {
            player->applyBuff(*potion->buff);
        }

        if (player->pcclass->HP->isFull() && !potion->buff) {
            return false; //dont use potion if hp is full and there isnt a buff
        }

        player->pcclass->HP->increase(potion->healAmmount);

        potion->Quantity--;

        if (potion->Quantity == 0) {
            item_to_use->marked_for_deletion = true;
            player->cleanup_backpack();
        }
        return true;
    }
    return false;
}

bool ItemFactory::moveToBackpack(Item *item_to_move, PlayerCharacter *player)  {
    //checking if its a null pointer
    if (!item_to_move->getData() || !item_to_move || !player)
        return false;

    player->Backpack.push_back(item_to_move);
    return true;
}
