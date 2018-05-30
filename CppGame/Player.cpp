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

bool Player::addEquipment(Equipment &equipment) {
	if (equipmentNum <= MAX_EQUIPMENT_NUM) {
		equipments[equipmentNum] = equipment;
		equipmentNum++;
		return true;
	}

	return false;
}

bool Player::removeEquipmentByIndex(const int index) {
	if (index > 0 && index < equipmentNum) {
		equipmentNum--;
		equipments[index] = equipments[equipmentNum];
		return true;
	}

	return false;
}

#endif
