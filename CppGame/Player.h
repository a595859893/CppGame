#ifndef PLAYER_H
#define PLAYER_H

#define MAX_HERO_NUM 4
#define MAX_EQUIPMENT_NUM 12

#include "Hero.h"
#include "Equipment.h"

class Player {
public:
	//构造函数 
	Player();


	//获取玩家拥有的金钱 
	int getMoney() const;
	//为金钱添加一个增量(可以为负数)  
	void appendMoney(const int delta);


	//获取玩家当前拥有的英雄数量 
	int getHeroNum()const;
	//获取玩家管理的英雄，以数组下标为索引 
	Hero& getHero(const int index);
	//为玩家添加一个英雄，让这个英雄可以被玩家管理，可管理英雄已满导致无法添加时返回false 
	bool addHero(const Hero &hero);
	//使用索引来删除管理的英雄的
	bool removeHeroByIndex(const int index);


	//获取玩家当前持有的装备数量 
	int getEquipmentNum()const;
	//获取玩家持有的装备，以数组下标为索引 
	Equipment& getEquipment(const int index);
	//让玩家持有装备，成功返回装备指针，持有装备已满导致无法添加时返回NULL
	Equipment* addEquipment(Equipment &equipment);
	//使用索引来进行管理英雄的删除 
	bool removeEquipmentByIndex(const int index);
private:
	//玩家持有的金钱 
	int money;

	//玩家管理的英雄，可以调整他们的装备获得让他们参战 
	int heroNum;
	Hero heros[MAX_HERO_NUM];

	//玩家持有的装备，储存备用或让玩家管理的英雄装备上以提高属性  
	int equipmentNum;
	Equipment equipments[MAX_EQUIPMENT_NUM];
};
#endif
