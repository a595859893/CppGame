#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"

Player::Player() :money(1000), heroNum(0), equipmentNum(0) {}

int Player::getMoney() const { return money; }
void Player::appendMoney(const int delta) { money += delta; }

int Player::getHeroNum()const { return heroNum; }
Hero& Player::getHero(const int index) { return heros[index]; }

bool Player::addHero(const Hero &hero) {
	if (heroNum < MAX_HERO_NUM) {
		heros[heroNum] = hero;
		heroNum++;
		return true;
	}

	return false;
}

bool Player::removeHeroByIndex(const int index) {
	if (index > 0 && index < heroNum) {
		heroNum--;
		heros[index] = heros[heroNum];
		return true;
	}

	return false;
}

int Player::getEquipmentNum()const { return equipmentNum; }
Equipment& Player::getEquipment(int index) { return equipments[index]; }

Equipment* Player::addEquipment(Equipment &equipment) {
	if (equipmentNum < MAX_EQUIPMENT_NUM) {
		equipments[equipmentNum] = equipment;
		equipmentNum++;
		return &equipments[equipmentNum - 1];
	}

	return false;
}

bool Player::removeEquipmentByIndex(const int index) {
	if (index > 0 && index < equipmentNum) {
		equipmentNum--;
		equipments[index] = equipments[equipmentNum];
		return true;
	}
	int i, j;
	for (i = 0; i < heroNum; i++) {
		for (j = 0; j < MAX_EQUIPMENT_NUM; j++) {
			if (&heros[i].getEquip(j) == &equipments[index]) {
				heros[i].unequip(j);
			}

			if (&heros[i].getEquip(j) == &equipments[equipmentNum]) {
				heros[i].unequip(j);
				heros[i].equip(equipments[index]);
			}

		}

	}

	return false;
}

#endif
