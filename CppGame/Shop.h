#ifndef SHOP_H
#define SHOP_H

#include "Scene.h"
#include "Equipment.h"
#include "Hero.h" 
#include "TextArea.h"


#define MAX_SHOP_ROW 2
#define MAX_SHOP_COL 3
#define MAX_SHOP_ITEM (MAX_SHOP_ROW*MAX_SHOP_COL)
#define ITEM_BUTTON_HEIGHT 5
#define ITEM_BUTTON_WIDTH 18

#define SHOP_SELECT_BUTTON_WIDTH 12
#define SHOP_SELECT_BUTTON_HEIGHT (GAME_WINDOW_HEIGHT / 2)

#define MAX_ITEM_PREFIX 6
#define MAX_ITEM_MATERIAL 9

class Shop :public Scene {
public:
	Shop(string name, string description);
	bool onKeyDown(const int key);
private:
	//用于保存消息提示
	string tips;
	//可以购买的装备、价格和对应UI组件按钮
	Equipment items[MAX_SHOP_ITEM];
	int itemPrice[MAX_SHOP_ITEM];
	TextArea itemButton[MAX_SHOP_ITEM];

	//记录将要购买的物品索引
	int equipIndex;

	//穿上装备时选择英雄用界面
	TextArea heroButton[MAX_HERO_NUM];

	//判断是否处于商品购买阶段
	bool inBuying;
	//判断是否处于选择英雄阶段
	bool inSelecting;

	void refresh();

	//当装备将被购买时的动作，购买成功时返回装备指针，失败返回NULL
	Equipment* onBuyItem(int index);
	//随机生成一个可供加入管理的英雄
	void randomNewItem(int index);

	//初始化UI界面
	void initEquipementButton();
	void initHeroSelected();

	//刷新玩家英雄状态
	void refreshHero(int index);

	static string prefixName[MAX_ITEM_PREFIX];
	static string materialName[MAX_ITEM_MATERIAL];
};
#endif
