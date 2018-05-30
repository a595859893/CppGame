#include "Equipment.h"
#include <iostream>
#include <string>

using namespace std;

Equipment::Equipment(string name, int atk, int def, int maxHp, int maxMp) :
	name(name),
	attackAppend(atk),
	defenceAppend(def),
	maxHealthPointAppend(maxHp),
	maxManaPointAppend(maxMp)
{}

string Equipment::getName() { return name; }
int Equipment::getAttackAppend() { return attackAppend; }
int Equipment::getDefenceAppend() { return defenceAppend; }
int Equipment::getMaxHealthPointAppend() { return maxHealthPointAppend; }
int Equipment::getMaxManaPointAppend() { return maxManaPointAppend; }
