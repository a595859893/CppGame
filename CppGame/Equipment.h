#ifndef _EQUIPMENT
#define _EQUIPMENT

#include <iostream>
using namespace std;

class Equipment {
public:
	//构造函数，创建一个物品，具有name名字，atc攻击力加成，def防御力加成，maxHp生命上限加成，maxMp魔法上限加成 
	explicit Equipment(string name = "以太", int atk = 0, int def = 0, int maxHp = 0, int maxMp = 0);

	//获取物品攻击力加成 
	int getAttackAppend();
	//获取物品防御力加成 
	int getDefenceAppend();
	//获取物品生命上限加成 
	int getMaxHealthPointAppend();
	//获取物品魔法上限加成 
	int getMaxManaPointAppend();
	//获取物品名字 
	string getName();

	//输出物品属性文本 
	void print();

private:
	//物品名字 
	string name;
	//攻击力加成 
	int attackAppend;
	//防御力加成 
	int defenceAppend;
	//生命上限加成 
	int maxHealthPointAppend;
	//魔法上限加成 
	int maxManaPointAppend;
};

#endif
