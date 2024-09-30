#include <iostream>

#include "headers/playercharacter.h"
#include "headers/itemFactory.h"

int main() {
    PlayerCharacter player(new Warrior());

    //testing instantiating items
    Item* CamisaCBJR = ItemFactory::createArmor("Camisa do tchali brau", CoreStats(0, 0, 0, 420, 0), ARMORSLOT::CHEST);
    Item* CamisaMatanza = ItemFactory::createArmor("Camisa do Matanza", CoreStats(0, 0, 0, 666, 0), ARMORSLOT::CHEST);
    Item* Chains = ItemFactory::createArmor("Corrente Meio Besta", CoreStats(0, 0, 0, 0, 333), ARMORSLOT::NECK);
    Item* LongSword = ItemFactory::createWeapon("Long Sword", CoreStats(), WEAPONSLOT::MELEE, 3, 9);
    Item* HandAxe = ItemFactory::createWeapon("Hand Axe", CoreStats(), WEAPONSLOT::MELEE, 5, 12);

    ItemFactory::equip(CamisaCBJR, &player);
    ItemFactory::equip(CamisaMatanza, &player);
    ItemFactory::equip(Chains, &player);
    ItemFactory::equip(LongSword, &player);


    for (int i = 0; i <= 2; i++) {
        std::cout << "\n" << player.getClassName() << " Level: " << player.getLevel() << " \nEXP: " << player.getEXP() << " / " << player.getEXPTillNextLevel()
            << "\n-HP: " << player.getCurrentHP() << " / " << player.getMaxHP()
            << "\n-Mana: " << player.getCurrentMP() << " / " << player.getMaxMP()
            << "\n-Energy: " << player.getCurrentEP() << " / " << player.getMaxEP()
            << "\n-Rage: " << player.getCurrentRP() << " / " << player.getMaxRP() <<
            "\n" << "-Srength: " << player.getSTR() <<
            "\n" << "-Intellect: " << player.getINT() <<
            "\n" << "-Agility: " << player.getAGI() <<
            "\n" << "-Armor: " << player.getARM() <<
            "\n" << "-Elemental Resistance: " << player.getRES() << std:: endl;


        std::cout << "\nBuffs:\n";
        auto AllBuffs = player.getBuffList();

        for (auto& buff : AllBuffs) {
            std::cout << " Name: " << buff.Name << "\n";
            std::cout << " Duration: " << buff.Duration << "\n";
        }

        std::cout << "\nAbilities:\n";
        auto AllAbilities = player.getAbilityList();

        for (auto& abil : AllAbilities) {
            std::cout << " -" << abil.Name << "\n";
        }

        std::cout << "\nArmor:\n";
        for (int i = 0; i < (int)ARMORSLOT::NUM_SLOTS; i++) {
            const Armor* tmp = dynamic_cast<Armor*>(player.getEquippedArmor(i));

            if (tmp) {
                std::cout << " " << tmp->Name << ", A:(" << tmp->Stats.Armor << ") R:(" << tmp->Stats.Armor << ")\n";
            }
        }

        std::cout << "\nWeapons:\n";
        for (int i = 0; i < (int)WEAPONSLOT::NUM_SLOTS; i++) {
            const Weapon* tmp = dynamic_cast<Weapon*>(player.getEquippedWeapon(i));

            if (tmp) {
                std::cout << " " << tmp->Name << ", D:(" << tmp->minDmg << "-" << tmp->maxDmg << ")\n";
            }
        }

        if (i == 1) {
            player.gainEXP(100u);
            //name, str, int, agi, arm, er, dur, isDebuff
            Buff arm_buff("StoneShield", 0, 0, 0, 5u, 0, 2u, 0);
            player.applyBuff(arm_buff);
        }

    }

    //testing some cases
     std::cout << "\nHealth before taking dmg " << player.getCurrentHP() << "/" << player.getMaxHP() << "\n";
     player.takeDMG(5);
     std::cout << "\nHealth after taking dmg " << player.getCurrentHP() << "/" << player.getMaxHP() << "\n";

     Item* HealPotion = ItemFactory::createPotion("Minor healing potion", 3u, 3u);

     ItemFactory::moveToBackpack(HealPotion, &player);
     ItemFactory::use(HealPotion, &player);
     std::cout << "\nHealth after healing potion " << player.getCurrentHP() << "/" << player.getMaxHP() << "\n";

     ItemFactory::moveToBackpack(HandAxe, &player);

     auto inv = player.getBackpack();

     std::cout << "\nInventory:\n";
     for(auto item : inv) {
         std::cout << *item << std::endl;
     }

    return 0;
}