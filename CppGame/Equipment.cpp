#include "Equipment.h"
#include <iostream>
#include <string>

using namespace std;

Equipment::Equipment(string name, int atk, int def, int maxHp, int maxMp) {
	Equipment::name = name;
	Equipment::attackAppend = atk;
	Equipment::defenceAppend = def;
	Equipment::maxHealthPointAppend = maxHp;
	Equipment::maxManaPointAppend = maxMp;
}

void Equipment::print() {
	cout << "[" << name << "]" << endl;
	if (attackAppend != 0)
		cout << "攻击加成:" << attackAppend << endl;
	if (defenceAppend != 0)
		cout << "防御加成:" << defenceAppend << endl;
	if (maxManaPointAppend != 0)
		cout << "生命上限加成:" << maxManaPointAppend << endl;
	if (maxHealthPointAppend != 0)
		cout << "魔法上限加成:" << maxHealthPointAppend << endl;
}

string Equipment::getName() { return name; }
int Equipment::getAttackAppend() { return attackAppend; }
int Equipment::getDefenceAppend() { return defenceAppend; }
int Equipment::getMaxHealthPointAppend() { return maxHealthPointAppend; }
int Equipment::getMaxManaPointAppend() { return maxManaPointAppend; }
