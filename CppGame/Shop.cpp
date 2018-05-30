#ifndef SHOP_CPP
#define SHOP_CPP
#include "Shop.h"

Shop::Shop(string name, string description) :Scene(name, description)
{
	equipIndex = -1;
	inBuying = true;
	inSelecting = false;

	initEquipementButton();
	initHeroSelected();
}

void Shop::initEquipementButton()
{
	int interval = (width - ITEM_BUTTON_WIDTH * MAX_SHOP_COL) / (MAX_SHOP_COL + 2);
	int intervalRaw = 2;
	int startWidth = (width - (interval + ITEM_BUTTON_WIDTH) * MAX_SHOP_COL + 1) / 2;
	int startHeight = height / 5;

	int i, j, index;
	for (i = 0; i < MAX_SHOP_ROW; i++) {
		for (j = 0; j < MAX_SHOP_COL; j++) {
			index = i * MAX_SHOP_COL + j;
			itemButton[index].init(
				startWidth + (interval + ITEM_BUTTON_WIDTH) * j,
				startHeight + (ITEM_BUTTON_HEIGHT + intervalRaw) *i,
				ITEM_BUTTON_WIDTH,
				ITEM_BUTTON_HEIGHT
			);
		}
	}

	int upI, downI, leftI, rightI;
	for (i = 0; i < MAX_SHOP_ROW; i++) {
		for (j = 0; j < MAX_SHOP_COL; j++) {
			index = i * MAX_SHOP_COL + j;

			upI = (MAX_SHOP_ROW + i - 1) % MAX_SHOP_ROW;
			leftI = (MAX_SHOP_COL + j - 1) % MAX_SHOP_COL;

			downI = (i + 1) % MAX_SHOP_ROW;
			rightI = (j + 1) % MAX_SHOP_COL;
			UIElement *up = &itemButton[upI*MAX_SHOP_COL + j];
			UIElement *down = &itemButton[downI*MAX_SHOP_COL + j];
			UIElement *left = &itemButton[i*MAX_SHOP_COL + leftI];
			UIElement *right = &itemButton[i*MAX_SHOP_COL + rightI];

			itemButton[index].link(up, UIElement::NEAR_UP);
			itemButton[index].link(down, UIElement::NEAR_DOWN);
			itemButton[index].link(right, UIElement::NEAR_RIGHT);
			itemButton[index].link(left, UIElement::NEAR_LEFT);

			randomNewItem(index);
		}
	}
}

void Shop::initHeroSelected()
{
	int interval = (width - SHOP_SELECT_BUTTON_WIDTH * MAX_HERO_NUM) / (MAX_HERO_NUM + 2);
	int startWidth = (width - (interval + SHOP_SELECT_BUTTON_WIDTH) * MAX_HERO_NUM + 1) / 2;
	int i;
	for (i = 0; i < MAX_HERO_NUM; i++) {
		heroButton[i].init(
			startWidth + (interval + SHOP_SELECT_BUTTON_WIDTH) * i,
			(height - SHOP_SELECT_BUTTON_HEIGHT) / 2 - 1,
			SHOP_SELECT_BUTTON_WIDTH,
			SHOP_SELECT_BUTTON_HEIGHT
		);
	}

	for (i = 0; i < MAX_HERO_NUM; i++) {
		UIElement *previousButton = &heroButton[(MAX_HERO_NUM + i - 1) % MAX_HERO_NUM];
		UIElement *nextButton = &heroButton[(i + 1) % MAX_HERO_NUM];
		heroButton[i].link(nextButton, UIElement::NEAR_RIGHT);
		heroButton[i].link(previousButton, UIElement::NEAR_LEFT);
	}
}

void Shop::refreshHero(int index)
{
	if (getPlayer().getHeroNum() > index) {

		heroButton[index].clear();
		heroButton[index].setWriteCursor(1, 2);
		heroButton[index].writeLine(getPlayer().getHero(index).getName());
		heroButton[index].writeLine("体力:   " + to_string(getPlayer().getHero(index).getMaxHealthPoint()));
		heroButton[index].writeLine("魔力:   " + to_string(getPlayer().getHero(index).getMaxManaPoint()));
		heroButton[index].writeLine("攻击:  " + to_string(getPlayer().getHero(index).getAttackPoint()));
		heroButton[index].writeLine("防御:  " + to_string(getPlayer().getHero(index).getDefencePoint()));
	}
	else {
		heroButton[index].clear();
		heroButton[index].setWriteCursor(SHOP_SELECT_BUTTON_WIDTH / 2 - 1, 4);
		heroButton[index].writeLine("该栏为空", 0, 2);
	}
}

bool Shop::onKeyDown(const int key)
{
	tips = "";
	int i;
	if (isOnKeyHandle() && key == UIElement::KEY_OK) {
		for (i = 0; i < MAX_SHOP_ITEM; i++)
			show(&itemButton[i]);

		jumpTo(&itemButton[0]);
		return true;
	}

	bool press = Scene::onKeyDown(key);
	for (i = 0; i < MAX_SHOP_ITEM; i++) {
		int key = itemButton[i].getPressedKey();
		if (key == UIElement::KEY_OK) {
			equipIndex = i;
			for (i = 0; i < MAX_HERO_NUM; i++) {
				itemButton[i].show(&heroButton[i]);
				refreshHero(i);
			}

			itemButton[i].jumpTo(&heroButton[0]);
			return true;
		}

		if (itemButton[i].isOnKeyHandle()) {
			inBuying = true;
			inSelecting = false;
		}
	}

	for (i = 0; i < MAX_HERO_NUM; i++) {
		int key = heroButton[i].getPressedKey();
		if (key == UIElement::KEY_OK) {
			Equipment * equipment = onBuyItem(i);
			if (equipment != NULL)
				getPlayer().getHero(i).equip(*equipment);
			return true;
		}

		if (heroButton[i].isOnKeyHandle()) {
			inBuying = false;
			inSelecting = true;
		}
	}

	if (isOnKeyHandle()) {
		for (i = 0; i < MAX_SHOP_ITEM; i++)
			hide(&itemButton[i]);
	}

	return press;
}

void Shop::refresh()
{
	printBoundary(isOnKeyFocus());

	if (!isOnKeyHandle()) {
		print(width / 2, 2, "持有金钱:" + to_string(getPlayer().getMoney()), UIElement::ALIGN_FRONT);
		print(width / 2, 3, tips, UIElement::ALIGN_FRONT);
		int startHeight = height / 3 * 2 + 1;
		if (inBuying) {
			print(width / 2, startHeight + 1, "'↑'、'↓'、'←'、'→'键选择不同的物品", UIElement::ALIGN_FRONT);
			print(width / 2, startHeight + 2, "'Z'键购买物品", UIElement::ALIGN_FRONT);
			print(width / 2, startHeight + 3, "'X'键离开商店", UIElement::ALIGN_FRONT);
		}
		else if (inSelecting) {
			print(width / 2, startHeight + 1, "'←'、'→'键选择不同的英雄", UIElement::ALIGN_FRONT);
			print(width / 2, startHeight + 2, "'Z'键为该英雄购买并穿上装备", UIElement::ALIGN_FRONT);
			print(width / 2, startHeight + 3, "'X'键取消此次购买", UIElement::ALIGN_FRONT);
		}
	}
	else {
		showPath();
		showDescription();
	}

	UIElement::refresh();
}

Equipment* Shop::onBuyItem(int index)
{
	if (getPlayer().getMoney() < itemPrice[index]) {
		tips = "金钱不足，无法购买！";
		return NULL;
	}

	Equipment* equipment = getPlayer().addEquipment(items[index]);

	if (equipment == NULL) {
		tips = "物品栏已满，无法购买！";
		return NULL;
	}
	else {
		randomNewItem(index);
		getPlayer().appendMoney(-itemPrice[index]);
	}

	return equipment;
}

void Shop::randomNewItem(int index)
{
	int type = rand() % 5;
	int special = rand() % 5;
	int price;

	string material = materialName[rand() % MAX_ITEM_MATERIAL];
	string prefix = "";
	string typeName = "";
	int atk = 0, def = 0, hp = 0, mp = 0;

	if (special <= 1) {
		prefix = prefixName[rand() % MAX_ITEM_PREFIX];
	}

	itemButton[index].clear();
	itemButton[index].setWriteCursor(3, 1);
	switch (type) {
	case 0:
		typeName = "盔";
		hp = 1 + rand() % 5;
		def = 1 + rand() % 5;
		itemButton[index].writeLine("体力 +" + to_string(hp));
		itemButton[index].writeLine("防御 +" + to_string(def));
		break;
	case 1:
		typeName = "杖";
		atk = 1 + rand() % 3;
		mp = 3 + rand() % 5;
		itemButton[index].writeLine("攻击 +" + to_string(atk));
		itemButton[index].writeLine("魔力 +" + to_string(mp));
		break;
	case 2:
		typeName = "剑";
		atk = 3 + rand() % 8;
		itemButton[index].writeLine("攻击 +" + to_string(atk));
		break;
	case 3:
		typeName = "盾";
		def = 1 + rand() % 4;
		itemButton[index].writeLine("防御 +" + to_string(def));
		break;
	case 4:
		typeName = "甲";
		hp = 5 + rand() % 15;
		itemButton[index].writeLine("体力 +" + to_string(hp));
		break;
	default:
		typeName = "以太";
		itemButton[index].writeLine("无加成");
		break;
	}

	items[index] = Equipment(prefix + material + typeName, atk, def, hp, mp);
	price = atk * 2 + mp * 3 + hp / 2 + def * 5 + rand() % 5;
	itemPrice[index] = price;

	itemButton[index].setWriteCursor(0, 0);
	itemButton[index].writeLine("[" + items[index].getName() + "]");
	itemButton[index].setWriteCursor(ITEM_BUTTON_WIDTH - 2, ITEM_BUTTON_HEIGHT - 2);
	itemButton[index].writeLine("价格 " + to_string(price), UIElement::ALIGN_RIGHT, 10);

}

string Shop::prefixName[MAX_ITEM_PREFIX] = {
	"全新的","二手的","发霉的","破旧的","豪华的","普通的"
};
string Shop::materialName[MAX_ITEM_MATERIAL] = {
	"木","铁","玻璃","饼干","黑曜石","金刚","云母","翡翠","真空"
};
#endif