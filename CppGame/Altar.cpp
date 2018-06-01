#ifndef ALTAR_CPP
#define ALTAR_CPP

#include "Altar.h"

Altar::Altar(string name, string description) :Scene(name, description) {
	initHeroSelected();
}

bool Altar::onKeyDown(const int key)
{
	tips = "";

	if (isOnKeyHandle() && key == UIElement::KEY_OK) {
		initScene();
		return true;
	}

	bool press = Scene::onKeyDown(key);
	press |= handleHeroKey();

	if (isOnKeyHandle()) {
		hideAll();
	}

	return press;
}

void Altar::refresh()
{
	printBoundary(isOnKeyFocus());

	if (!isOnKeyHandle()) {
		print(width / 2, 2, "持有金钱:" + to_string(getPlayer().getMoney()), UIElement::ALIGN_FRONT);
		print(width / 2, 3, tips, UIElement::ALIGN_FRONT);

		int startHeight = height / 3 * 2 + 1;
		print(width / 2, startHeight + 1, "←'、'→'键选择不同的英雄", UIElement::ALIGN_FRONT);
		print(width / 2, startHeight + 2, "'Z'键花费金钱将选中其加入队伍", UIElement::ALIGN_FRONT);
		print(width / 2, startHeight + 3, "'X'键离开祭坛", UIElement::ALIGN_FRONT);
	}
	else {
		showPath();
		showDescription();
	}

	UIElement::refresh();
}

void Altar::initScene()
{
	int i;
	for (i = 0; i < MAX_MANAGE_HEROS; i++)
		show(&heroButton[i]);

	jumpTo(&heroButton[0]);
}

void Altar::initHeroSelected()
{
	int interval = (width - HERO_BUTTON_WIDTH * MAX_MANAGE_HEROS) / (MAX_MANAGE_HEROS + 2);
	int startWidth = (width - (interval + HERO_BUTTON_WIDTH) * MAX_MANAGE_HEROS + 1) / 2;
	int i;
	for (i = 0; i < MAX_MANAGE_HEROS; i++) {
		heroButton[i].init(
			startWidth + (interval + HERO_BUTTON_WIDTH) * i,
			(height - HERO_BUTTON_HEIGHT) / 2 - 1,
			HERO_BUTTON_WIDTH,
			HERO_BUTTON_HEIGHT
		);
	}

	for (i = 0; i < MAX_MANAGE_HEROS; i++) {
		UIElement *previousButton = &heroButton[(MAX_MANAGE_HEROS + i - 1) % MAX_MANAGE_HEROS];
		UIElement *nextButton = &heroButton[(i + 1) % MAX_MANAGE_HEROS];
		heroButton[i].link(nextButton, UIElement::NEAR_RIGHT);
		heroButton[i].link(previousButton, UIElement::NEAR_LEFT);

		randomNewHero(i);

	}
}

bool Altar::handleHeroKey()
{
	int i;
	for (i = 0; i < MAX_MANAGE_HEROS; i++) {
		int key = heroButton[i].getPressedKey();
		if (key == UIElement::KEY_OK) {
			onBuyHero(i);
			return true;
		}
	}

	return false;
}

void Altar::onBuyHero(int index)
{
	if (getPlayer().getHeroNum() == MAX_HERO_NUM) {
		tips = "拥有英雄数量已满！";
		return;
	}

	if (getPlayer().getMoney() < heroPrice[index]) {
		tips = "金钱不足，无法雇佣此英雄！";
		return;
	}
	getPlayer().addHero(heros[index]);
	getPlayer().appendMoney(-heroPrice[index]);
	randomNewHero(index);
}

void Altar::randomNewHero(int index)
{
	string name = firstName[rand() % MAX_FIRST_NAME_NUM] + lastName[rand() % MAX_LAST_NAME_NUM];
	int maxHp = 15 + rand() % 30;
	int maxMp = 5 + rand() % 15;
	int attack = 5 + rand() % 3;
	int def = 2 + rand() % 2;

	int price = maxHp / 6 + maxMp * 3 + attack + def * 6 + rand() % 10;

	heros[index] = Hero(name, maxHp, maxMp, attack, def);
	heroPrice[index] = price;

	heroButton[index].clear();
	heroButton[index].setWriteCursor(1, 2);
	heroButton[index].writeLine(heros[index].getName());
	heroButton[index].writeLine("体力:  " + to_string(heros[index].getMaxHealthPoint()));
	heroButton[index].writeLine("魔力:  " + to_string(heros[index].getMaxManaPoint()));
	heroButton[index].writeLine("攻击:  " + to_string(heros[index].getAttackPoint()));
	heroButton[index].writeLine("防御:  " + to_string(heros[index].getDefencePoint()));
	heroButton[index].nextLine();
	heroButton[index].writeLine("价格:  " + to_string(heroPrice[index]));
}

string Altar::firstName[MAX_FIRST_NAME_NUM] = {
	"路人",
	"勇者",
	"战士",
	"步兵",
	"脚男"
};

string Altar::lastName[MAX_LAST_NAME_NUM] = {
	"甲","乙","丙","丁","戊","己","庚","辛"
};

#endif


