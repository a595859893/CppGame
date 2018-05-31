#ifndef BATTLEFIELD_CPP
#define BATTLEFIELD_CPP

#include "Battlefield.h"

Battlefield::Battlefield(string name, string description) :Scene(name, description)
{
	initEnemyButton();
	initHeroSelected();
	initAction();

	randomEnemys();
}


void Battlefield::onDoingAction()
{

}

void Battlefield::randomNewEnemy(int index)
{
	string name = firstName[rand() % MAX_ENEMY_FIRST_NAME_NUM] + lastName[rand() % MAX_ENEMY_LAST_NAME_NUM];
	int maxHp = 15 + rand() % 25;
	int maxMp = 10 + rand() % 5;
	int attack = 5 + rand() % 3;
	int def = 2 + rand() % 2;

	enemy[index] = Hero(name, maxHp, maxMp, attack, def);
}

void Battlefield::randomEnemys()
{
	enemyNum = 1 + rand() % (MAX_ENEMY_NUM - 1);
	int i;
	for (i = 0; i < enemyNum; i++) {
		randomNewEnemy(i);
	}
}

bool Battlefield::onKeyDown(const int key)
{
	tips = "";

	if (isOnKeyHandle() && key == UIElement::KEY_OK) {
		if (getPlayer().getHeroNum() > 0)
			initScene();
		else
			tips = "û�п��Բ�ս��Ӣ�ۣ��޷�����ս����";

		return true;
	}


	bool press = Scene::onKeyDown(key);
	press |= handleHeroKey();
	press |= handleActionKey();
	press |= handleEnemyKey();
	return press;
}

void Battlefield::enemyTurn()
{
}

void Battlefield::finishTurn()
{
}

bool Battlefield::handleHeroKey()
{
	int i, j;
	for (i = 0; i < MAX_HERO_NUM; i++) {
		if (heroButton[i].isOnKeyHandle()) {
			for (j = 0; j < MAX_ACTION_NUM; j++)
				hide(&actionButton[j]);

			inAction = false;
			inSelecting = true;
		}

		int key = heroButton[i].getPressedKey();
		if (key == UIElement::KEY_OK) {

			if (getPlayer().getHeroNum() > i) {
				heroIndex = i;
				inAction = true;
				inSelecting = false;
				for (j = 0; j < MAX_ACTION_NUM; j++) {
					refreshAction(j);
					show(&actionButton[j]);
				}
				heroButton[i].jumpTo(&actionButton[0]);
			}
			else {
				tips = "����������Ӣ�ۣ�";
			}

			return true;
		}
	}

	return false;
}

bool Battlefield::handleActionKey()
{
	return false;
}

bool Battlefield::handleEnemyKey()
{
	return false;
}


void Battlefield::initScene()
{
	int i;
	for (i = 0; i < MAX_HERO_NUM; i++) {
		refreshHero(i);
		show(&heroButton[i]);
	}


	for (i = 0; i < MAX_ENEMY_NUM; i++) {
		refreshEnemy(i);
		show(&enemyButton[i]);
	}


	jumpTo(&heroButton[0]);
}

void Battlefield::initEnemyButton()
{
	int i;

	int interval = (width - BATTLEFIELD_ENEMY_BUTTON_WIDTH * MAX_ENEMY_NUM)
		/ (BATTLEFIELD_ENEMY_BUTTON_WIDTH + 2);
	int startWidth = (width - (interval + BATTLEFIELD_ENEMY_BUTTON_WIDTH) * MAX_ENEMY_NUM + 1) / 2;
	for (i = 0; i < MAX_ENEMY_NUM; i++) {
		enemyButton[i].init(
			startWidth + (interval + BATTLEFIELD_ENEMY_BUTTON_WIDTH) * i,
			2,
			BATTLEFIELD_ENEMY_BUTTON_WIDTH,
			BATTLEFIELD_ENEMY_BUTTON_HEIGHT
		);
	}

	for (i = 0; i < MAX_ENEMY_NUM; i++) {
		UIElement *previousButton = &enemyButton[(MAX_ENEMY_NUM + i - 1) % MAX_ENEMY_NUM];
		UIElement *nextButton = &enemyButton[(i + 1) % MAX_ENEMY_NUM];
		enemyButton[i].link(nextButton, UIElement::NEAR_RIGHT);
		enemyButton[i].link(previousButton, UIElement::NEAR_LEFT);

		randomNewEnemy(i);
	}
}

void Battlefield::initHeroSelected()
{
	int i;
	int buttonWidth = width / MAX_HERO_NUM;
	for (i = 0; i < MAX_HERO_NUM; i++) {
		heroButton[i].init(
			buttonWidth  * i,
			height - BATTLEFIELD_HERO_BUTTON_HEIGHT,
			buttonWidth,
			BATTLEFIELD_HERO_BUTTON_HEIGHT
		);
		heroButton[i].setBackEnable(false);
	}

	for (i = 0; i < MAX_HERO_NUM; i++) {
		UIElement *previousButton = &heroButton[(MAX_HERO_NUM + i - 1) % MAX_HERO_NUM];
		UIElement *nextButton = &heroButton[(i + 1) % MAX_HERO_NUM];
		heroButton[i].link(nextButton, UIElement::NEAR_RIGHT);
		heroButton[i].link(previousButton, UIElement::NEAR_LEFT);
	}
}

void Battlefield::initAction()
{
	int i;

	for (i = 0; i < MAX_ACTION_NUM; i++) {
		actionButton[i].init(0, 0, ACTION_BUTTON_WIDTH, ACTION_BUTTON_HEIGHT);
	}

	for (i = 0; i < MAX_ACTION_NUM; i++) {
		UIElement *previousButton = &actionButton[(MAX_ACTION_NUM + i - 1) % MAX_ACTION_NUM];
		UIElement *nextButton = &actionButton[(i + 1) % MAX_ACTION_NUM];
		actionButton[i].link(nextButton, UIElement::NEAR_UP);
		actionButton[i].link(previousButton, UIElement::NEAR_DOWN);
	}
}

void Battlefield::refreshHero(int index)
{
	if (getPlayer().getHeroNum() > index) {
		Hero hero = getPlayer().getHero(index);
		string hpStr = to_string(hero.getHealthPoint()) + "/" + to_string(hero.getMaxHealthPoint());
		string mpStr = to_string(hero.getManaPoint()) + "/" + to_string(hero.getMaxManaPoint());

		heroButton[index].clear();
		heroButton[index].setWriteCursor(0, 0);
		heroButton[index].writeLine("[" + hero.getName() + "]");
		heroButton[index].setWriteCursor(1, 2);
		heroButton[index].writeLine("����: " + hpStr);
		heroButton[index].writeLine("ħ��: " + mpStr);
		heroButton[index].nextLine();
		switch (heroTurn[index]) {
		case(TURN_TYPE_END):
			heroButton[index].writeLine("* ���ж� * " + mpStr);
		case(TURN_TYPE_STUNNED):
			heroButton[index].writeLine("* �޷��ж� * " + mpStr);
		}
	}
	else {
		heroButton[index].clear();
		heroButton[index].setWriteCursor(0, 0);
		heroButton[index].writeLine("[��Ӣ��]");
	}
}

void Battlefield::refreshEnemy(int index)
{
	if (enemyNum > index) {
		enemyButton[index].clear();
		enemyButton[index].setWriteCursor(BATTLEFIELD_ENEMY_BUTTON_WIDTH / 2, 0);
		enemyButton[index].writeLine("[" + enemy[index].getName() + "]", UIElement::ALIGN_FRONT, BATTLEFIELD_ENEMY_BUTTON_WIDTH);
		enemyButton[index].setWriteCursor(2, 2);
		enemyButton[index].writeLine("����:" + to_string(enemy[index].getHealthPoint()));
	}
	else {
		enemyButton[index].clear();
		enemyButton[index].setWriteCursor(BATTLEFIELD_ENEMY_BUTTON_WIDTH / 2, 0);
		enemyButton[index].writeLine("[ - ]", UIElement::ALIGN_FRONT);
	}
}

void Battlefield::refreshAction(int index)
{
	int posX = (width / MAX_HERO_NUM) * (heroIndex + 1) - ACTION_BUTTON_WIDTH;
	int posY = height - BATTLEFIELD_HERO_BUTTON_HEIGHT - 1 -
		(ACTION_BUTTON_HEIGHT - 1) * (index + 1);

	actionButton[index].setPosition(posX, posY);

	actionButton[index].clear();
	actionButton[index].setWriteCursor(ACTION_BUTTON_WIDTH / 2, 1);
	switch (index) {
	case 0:
		actionButton[index].writeLine("����", UIElement::ALIGN_FRONT, ACTION_BUTTON_WIDTH);
		break;
	case 1:
		actionButton[index].writeLine("ħ��", UIElement::ALIGN_FRONT, ACTION_BUTTON_WIDTH);
		break;
	case 2:
		actionButton[index].writeLine("�ȴ�", UIElement::ALIGN_FRONT, ACTION_BUTTON_WIDTH);
		break;
	}
}

void Battlefield::refresh()
{
	printBoundary(isOnKeyFocus());

	if (!isOnKeyHandle()) {
		int startHeight = height / 3;
		int startWidth;
		if (inSelecting) {
			startWidth = width / 2;
			print(startWidth, startHeight + 1, "��'��'��'��ѡ��Ҫ�ж���Ӣ��", UIElement::ALIGN_FRONT);
			print(startWidth, startHeight + 2, "'Z'��ѡ���Ӣ�۽��ж���", UIElement::ALIGN_FRONT);
			print(startWidth, startHeight + 3, "ÿ�غ�ÿ��Ӣ�۸����ж� 1 ��", UIElement::ALIGN_FRONT);
			print(startWidth, startHeight + 5, tips, UIElement::ALIGN_FRONT);
		}
		else if (inAction) {
			startWidth = (heroIndex >= MAX_HERO_NUM / 2) ? 5 : width / 2 + 2;
			print(startWidth, startHeight + 1, "��'��'��'��ѡ���ж�");
			print(startWidth, startHeight + 2, "'Z'��ȷ�϶�����ѡ��");
			print(startWidth, startHeight + 4, tips);
		}

	}
	else {
		print(width / 2, 3, tips, UIElement::ALIGN_FRONT);
		showPath();
		showDescription();
	}

	UIElement::refresh();
}

string Battlefield::firstName[MAX_ENEMY_FIRST_NAME_NUM] = {
	"����",
	"����",
	"�ڻ�",
	"��å",
	"����"
};

string Battlefield::lastName[MAX_ENEMY_LAST_NAME_NUM] = {
	"I","II","III","IV","V","VI","VII","VIII","IX","X"
};
#endif