#ifndef PLAYER_H
#define PLAYER_H

#define MAX_HERO_NUM 4
#define MAX_EQUIPMENT_NUM 20

#include "Hero.h"
#include "Equipment.h"

class Player {
public:
	//构造函数 
	Player();

	//为玩家添加一个可以操控的英雄，可操控英雄数已满时不会添加并返回false 
	bool addHero(const Hero &hero);
	//使用索引来删除管理的英雄，若该英雄不属于玩家可操控英雄则返回false
	bool removeHeroByIndex(const int index);

	//让玩家持有装备，成功返回装备指针，持有装备已满导致无法添加时返回NULL
	Equipment* addEquipment(Equipment &equipment);
	//使用索引来进行物品的删除 
	bool removeEquipmentByIndex(const int index);


	//数值增量函数（可通过传入负值以减少）
	void appendMoney(const int delta);

	//数据获取函数
	int getMoney() const;
	int getHeroNum()const;
	int getEquipmentNum()const;
	//通过数组下标来获取数据
	Hero& getHero(const int index);
	Equipment& getEquipment(const int index);

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
