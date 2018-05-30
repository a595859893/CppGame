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
		cout << "�����ӳ�:" << attackAppend << endl;
	if (defenceAppend != 0)
		cout << "�����ӳ�:" << defenceAppend << endl;
	if (maxManaPointAppend != 0)
		cout << "�������޼ӳ�:" << maxManaPointAppend << endl;
	if (maxHealthPointAppend != 0)
		cout << "ħ�����޼ӳ�:" << maxHealthPointAppend << endl;
}

string Equipment::getName() { return name; }
int Equipment::getAttackAppend() { return attackAppend; }
int Equipment::getDefenceAppend() { return defenceAppend; }
int Equipment::getMaxHealthPointAppend() { return maxHealthPointAppend; }
int Equipment::getMaxManaPointAppend() { return maxManaPointAppend; }
