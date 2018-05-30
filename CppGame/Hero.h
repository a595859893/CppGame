#ifndef HERO_H
#define HERO_H

#define MAX_EQUIP_NUM 6

#include <iostream>

#include "Equipment.h"


using namespace std;

class Hero {
public:
	//创建一个英雄，具有name姓名，maxHp的生命上限，maxMp的魔法上限,atk的攻击力，def的防御力 
	explicit Hero(string name = "无名氏", int maxHp = 100, int maxMp = 100, int atk = 0, int def = 0);


	//消耗魔法值，对target英雄释放一个魔法，造成非物理伤害(不会被defence减免)，返回魔法是否成功释放 
	bool useMagicTo(Hero &target, int damage, int manaCost);
	//攻击target英雄，减少target英雄的生命值，值取决于自己的攻击力和对方的防御力 
	void attackTo(Hero &target);
	//受到来自attacker英雄的攻击，减少自己的生命值，值取决于target英雄的攻击力和自己的防御力 
	void defenceFrom(Hero &attacker);


	//装备equipment，获得它提供的属性加成，返回被装备的位置（装备失败返回-1） 
	int equip(Equipment &equipment);
	//卸下对应物品栏位置的装备，英雄将不再享受这个物品提供的属性加成 
	void unequip(int index);
	//输入英雄身上物品栏位置，返回这个位置上的装备 
	Equipment& getEquip(int index);


	//数据获取函数
	int getMaxHealthPoint() const;
	int getMaxManaPoint() const;
	int getHealthPoint() const;
	int getManaPoint() const;
	int getAttackPoint() const;
	int getDefencePoint() const;
	string getName() const;

	//数据设置函数
	void setHealthPoint(int value);
	void setManaPoint(int value);
	void setName(string const value);

	//数值增量函数（可通过传入负值以减少）
	void appendHealthPoint(int value);
	void appendManaPoint(int value);
	void appendAttackPoint(int value);
	void appendDefencePoint(int value);
	//体力、魔力上限进行增量变化时，当前体力、魔力值将会按比例跟随变化 
	void appendMaxHealthPoint(int value);
	void appendMaxManaPoint(int value);

private:
	//检查英雄是否死亡 
	bool deathCheck(Hero &lastAttacker);

	//对target英雄造成伤害，这会让target的生命值减少damage点
	//如果isPhysics为true,则伤害会计算对方defence减免，此时实际伤害值为max(0,damage-defence)点 
	int damageTo(Hero &target, int damage, bool isPhysics);


	//英雄姓名 
	string name;
	//生命上限 
	int maxHealthPoint;
	//魔法上限 
	int maxManaPoint;
	//当前生命值 
	int healthPoint;
	//当前魔法值 
	int manaPoint;
	//攻击力 
	int attackPoint;
	//防御力 
	int defencePoint;
	//是否死亡 
	bool deathFlag;
	//物品栏 
	Equipment *equipped[MAX_EQUIP_NUM];

};
#endif 
