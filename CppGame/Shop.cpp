#ifndef SHOP_CPP
#define SHOP_CPP
#include "Shop.h"

Shop::Shop(string name, string description) :Scene(name, description)
{
	int interval = (width - ITEM_BUTTON_WIDTH * MAX_SHOP_COL) / (MAX_SHOP_COL + 2);
	int intervalRaw = 2;
	int startWidth = (width - (interval + ITEM_BUTTON_WIDTH) * MAX_SHOP_COL + 1) / 2;
	int startHeight = height / 4;

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
			onBuyItem(i);
			return true;
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
		print(width / 2, startHeight + 1, "'←'、'→'键选择不同的物品", UIElement::ALIGN_FRONT);
		print(width / 2, startHeight + 2, "'Z'键购买物品", UIElement::ALIGN_FRONT);
		print(width / 2, startHeight + 3, "'X'键离开商店", UIElement::ALIGN_FRONT);
	}
	else {
		showPath();
		showDescription();
	}

	UIElement::refresh();
}

void Shop::onBuyItem(int index)
{
	if (getPlayer().getMoney() < itemPrice[index]) {
		tips = "金钱不足，无法购买！";
		return;
	}
	getPlayer().addEquipment(items[index]);
	getPlayer().appendMoney(-itemPrice[index]);
	randomNewItem(index);
}

void Shop::randomNewItem(int index)
{
}

#endif