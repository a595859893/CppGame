#ifndef BATTLEFIELD_CPP
#define BATTLEFIELD_CPP

#include "Battlefield.h"

Battlefield::Battlefield(string name, string description) :Scene(name, description)
{
	actionIndex = 0;
	heroIndex = 0;
	targetIndex = 0;
	enemyTurnIndex = -1;

	initEnemyButton();
	initHeroSelected();
	initAction();

	randomEnemys();
}


void Battlefield::onDoingAction()
{
	Hero *hero = getPlayer().getHero(heroIndex);
	int manaCost = 5 + hero->getManaPoint() / 3;
	bool needTarget = true;

	switch (actionIndex) {
	case ACTION_WAIT:
		needTarget = false;
		lateMessage(hero->getName() + " 伺机而动");
		onActionDone();
		break;
	case ACTION_MAGIC:
		if (hero->getManaPoint() < manaCost) {
			tips = "没有足够的魔力释放魔法！";
			needTarget = false;
		}
		break;
	}

	if (needTarget) {
		actionButton[actionIndex].jumpTo(&enemyButton[0]);
	}
}

void Battlefield::onDoingActionToTarget(int target)
{
	Hero *hero = getPlayer().getHero(heroIndex);
	int magicDamage = hero->getMaxManaPoint();
	int manaCost = 5 + hero->getManaPoint() / 3;

	switch (actionIndex) {
	case ACTION_ATTACK:
		lateMessage(hero->getName() + " 对 " + enemy[target].getName() + " 发起攻击");
		hero->attackTo(enemy[targetIndex]);
		break;
	case ACTION_MAGIC:
		lateMessage(hero->getName() + " 对 " + enemy[target].getName() + " 施展魔法");
		hero->useMagicTo(enemy[targetIndex], magicDamage, manaCost);
		break;
	}

	refreshEnemy(targetIndex);
	onActionDone();
}

void Battlefield::onActionDone()
{
	if (enemyButton[targetIndex].isOnKeyHandle())
		enemyButton[targetIndex].back();
	if (actionButton[actionIndex].isOnKeyHandle())
		actionButton[actionIndex].back();

	heroTurn[heroIndex] = TURN_TYPE_END;
	refreshHero(heroIndex);
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
			tips = "没有可以参战的英雄，无法进入战场！";

		return true;
	}

	bool press = Scene::onKeyDown(key);

	if (isOnKeyFocus()) {
		hide(&textButton);

		if (!stateCheck()) {
			press |= handleEnemyKey();
			press |= handleActionKey();
			press |= handleHeroKey();
		}
		else {
			if (isOnKeyHandle())
				hideAll();

			return true;
		}

	}

	return press;
}

void Battlefield::enemyTurn()
{
	enemyTurnIndex = enemyNum;
	lateMessage("敌人的回合");
}

void Battlefield::enemyAction(int index)
{
	if (enemy[index].isDead()) {
		lateMessage(enemy[index].getName() + " 无法再战");
		return;
	}

	int i;
	int heroNum = getPlayer().getHeroNum();
	int target = rand() % heroNum;
	for (i = 0; i < heroNum; i++) {
		Hero *hero = getPlayer().getHero(target + i % heroNum);
		if (!hero->isDead()) {
			enemy[index].attackTo(*hero);
			refreshEnemy(index);
			refreshHero(target + i % heroNum);

			lateMessage(enemy[index].getName() + " 对 " + hero->getName() + " 发起攻击");
			return;
		}
	}

	lateMessage(enemy[index].getName() + " 伺机而动");
}

void Battlefield::finishTurn()
{
	int i;
	for (i = 0; i < getPlayer().getHeroNum(); i++) {
		if (!getPlayer().getHero(i)->isDead())
			heroTurn[i] = TURN_TYPE_ACTIVE;
		else
			heroTurn[i] = TURN_TYPE_STUNNED;

		refreshHero(i);
		refreshEnemy(i);
	}
}

bool Battlefield::stateCheck()
{
	int i, heroNum = getPlayer().getHeroNum();

	if (enemyTurnIndex > 0) {
		enemyTurnIndex--;
		enemyAction(enemyTurnIndex);
		if (enemyTurnIndex == 0) {
			finishTurn();
		}
		return true;
	}


	bool nextTurn = true;
	bool lose = true;
	bool win = true;
	for (i = 0; i < heroNum; i++) {
		if (heroTurn[i] == TURN_TYPE_ACTIVE) {
			nextTurn = false;
		}

		if (!getPlayer().getHero(i)->isDead()) {
			lose = false;
		}
	}

	for (i = 0; i < enemyNum; i++) {
		if (!enemy[i].isDead())
			win = false;
	}

	if (win || lose) {
		if (win) {
			int money = 30 + rand() % 50;
			getPlayer().appendMoney(money);
			print(5, height - 5, "战斗胜利，你获得了 " + to_string(money) + " 的金钱奖励！");
			for (i = 0; i < heroNum; i++) {
				Hero *hero = getPlayer().getHero(i);
				hero->setHealthPoint(hero->getMaxHealthPoint());
				hero->setManaPoint(hero->getMaxManaPoint());
				randomEnemys();
			}
		}

		if (lose) {
			int randLeave = rand() % heroNum;
			for (i = 0; i < heroNum; i++) {
				Hero *hero = getPlayer().getHero(i);
				hero->setHealthPoint(hero->getMaxHealthPoint());
				hero->setManaPoint(hero->getMaxManaPoint());
			}
			print(5, height - 5, "战斗失败，你仓促逃离了！");
			print(5, height - 4, getPlayer().getHero(randLeave)->getName() + " 心灰意冷地退出了队伍。");
			getPlayer().removeHeroByIndex(randLeave);
		}

		for (i = 0; i < MAX_ENEMY_NUM; i++)
			enemyButton[i].back();
		for (i = 0; i < MAX_ACTION_NUM; i++)
			actionButton[i].back();
		for (i = 0; i < MAX_HERO_NUM; i++)
			heroButton[i].back();


		/*
		if (enemyButton[targetIndex].isOnKeyHandle())
			enemyButton[targetIndex].back();
		if (actionButton[actionIndex].isOnKeyHandle())
			actionButton[actionIndex].back();
		if (heroButton[heroIndex].isOnKeyHandle())
			heroButton[heroIndex].back();
		*/


		return true;
	}
	else if (nextTurn) {
		enemyTurn();
		return true;
	}


	return false;
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
			if (getPlayer().getHeroNum() <= i) {
				tips = "该栏不存在英雄！";
				return true;
			}

			if (heroTurn[i] != TURN_TYPE_ACTIVE) {
				tips = "该英雄本回合无法继续行动！";
				return true;
			}

			heroIndex = i;
			inAction = true;
			inSelecting = false;
			for (j = 0; j < MAX_ACTION_NUM; j++) {
				refreshAction(j);
				show(&actionButton[j]);
			}
			heroButton[i].jumpTo(&actionButton[0]);


			return true;
		}
	}

	return false;
}

bool Battlefield::handleActionKey()
{
	int i;
	for (i = 0; i < MAX_ACTION_NUM; i++) {
		if (actionButton[i].isOnKeyHandle()) {
			inAction = true;
			inTarget = false;
		}

		int key = actionButton[i].getPressedKey();
		if (key == UIElement::KEY_OK) {
			inAction = false;
			inTarget = true;
			actionIndex = i;
			onDoingAction();
			return true;
		}
	}

	return false;
}

bool Battlefield::handleEnemyKey()
{
	int i;
	for (i = 0; i < MAX_ENEMY_NUM; i++) {
		int key = enemyButton[i].getPressedKey();
		if (key == UIElement::KEY_OK) {
			if (enemyNum <= i) {
				tips = "该栏不存在敌人！";
				return true;
			}
			if (enemy[i].isDead()) {
				tips = "敌人已死亡！";
				return true;
			}
			targetIndex = i;
			onDoingActionToTarget(targetIndex);
			return true;
		}
	}

	return false;
}


void Battlefield::initScene()
{
	finishTurn();

	int i;

	for (i = 0; i <  MAX_ACTION_NUM; i++) {
		actionButton[i].getPressedKey();
	}

	for (i = 0; i < MAX_ENEMY_NUM; i++) {
		enemyButton[i].getPressedKey();
		refreshEnemy(i);
		show(&enemyButton[i]);
	}

	for (i = 0; i < MAX_HERO_NUM; i++) {
		heroButton[i].getPressedKey();
		refreshHero(i);
		show(&heroButton[i]);
	}

	actionIndex = 0;
	heroIndex = 0;
	targetIndex = 0;
	enemyTurnIndex = -1;

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
		Hero *hero = getPlayer().getHero(index);
		heroButton[index].clear();
		heroButton[index].setWriteCursor(0, 0);
		heroButton[index].writeLine("[" + hero->getName() + "]");

		if (!hero->isDead()) {
			string hpStr = to_string(hero->getHealthPoint()) + "/" + to_string(hero->getMaxHealthPoint());
			string mpStr = to_string(hero->getManaPoint()) + "/" + to_string(hero->getMaxManaPoint());

			heroButton[index].setWriteCursor(1, 2);
			heroButton[index].writeLine("体力: " + hpStr);
			heroButton[index].writeLine("魔力: " + mpStr);
		}
		else {
			heroButton[index].setWriteCursor(3, 2);
			heroButton[index].writeLine("失去战力");
		}

		heroButton[index].setWriteCursor(1, 5);
		switch (heroTurn[index]) {
		case(TURN_TYPE_END):
			heroButton[index].writeLine(" * 已行动 * ");
			break;
		case(TURN_TYPE_STUNNED):
			heroButton[index].writeLine("* 无法行动 * ");
			break;
		}
	}
	else {
		heroButton[index].clear();
		heroButton[index].setWriteCursor(0, 0);
		heroButton[index].writeLine("[无英雄]");
	}
}

void Battlefield::refreshEnemy(int index)
{
	if (enemyNum > index) {
		enemyButton[index].clear();
		enemyButton[index].setWriteCursor(BATTLEFIELD_ENEMY_BUTTON_WIDTH / 2, 0);
		enemyButton[index].writeLine("[" + enemy[index].getName() + "]", UIElement::ALIGN_FRONT, BATTLEFIELD_ENEMY_BUTTON_WIDTH);
		enemyButton[index].setWriteCursor(2, 2);
		if (!enemy[index].isDead()) {
			enemyButton[index].writeLine("体力:" + to_string(enemy[index].getHealthPoint()));
		}
		else {
			enemyButton[index].writeLine("失去战力");
		}

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
		actionButton[index].writeLine("攻击", UIElement::ALIGN_FRONT, ACTION_BUTTON_WIDTH);
		break;
	case 1:
		actionButton[index].writeLine("魔法", UIElement::ALIGN_FRONT, ACTION_BUTTON_WIDTH);
		break;
	case 2:
		actionButton[index].writeLine("等待", UIElement::ALIGN_FRONT, ACTION_BUTTON_WIDTH);
		break;
	}
}

void Battlefield::refresh()
{
	printBoundary(isOnKeyFocus());

	if (!isOnKeyHandle()) {
		int startHeight = height / 3;
		int startWidth = width / 2;
		if (inSelecting) {
			print(startWidth, startHeight + 1, "←'、'→'键选择要行动的英雄", UIElement::ALIGN_FRONT);
			print(startWidth, startHeight + 2, "'Z'键选择该英雄进行动作", UIElement::ALIGN_FRONT);
			print(startWidth, startHeight + 3, "每回合每个英雄各可行动 1 次", UIElement::ALIGN_FRONT);
			print(startWidth, startHeight + 5, tips, UIElement::ALIGN_FRONT);
		}
		else if (inAction) {
			startWidth = (heroIndex >= MAX_HERO_NUM / 2) ? 5 : width / 2 + 2;
			print(startWidth, startHeight + 1, "↑'、'↓'键选择行动");
			print(startWidth, startHeight + 2, "'Z'键确认动作的选择");
			print(startWidth, startHeight + 4, tips);
		}
		else if (inTarget) {
			print(startWidth, startHeight, tips, UIElement::ALIGN_FRONT);
		}

	}
	else {
		showPath();
		showDescription();
		print(width / 2, 5, tips, UIElement::ALIGN_FRONT);
	}

	UIElement::refresh();
}

void Battlefield::lateMessage(string msg)
{
	textButton.init(width / 2 - msg.length() / 2 - 2, height / 2 - 3, msg.length() + 4, 5);
	textButton.clear();
	textButton.setWriteCursor(2, 2);
	textButton.writeLine(msg);
	show(&textButton);
}

string Battlefield::firstName[MAX_ENEMY_FIRST_NAME_NUM] = {
	"杂鱼",
	"反派",
	"炮灰",
	"流氓",
	"无赖"
};

string Battlefield::lastName[MAX_ENEMY_LAST_NAME_NUM] = {
	"I","II","III","IV","V","VI","VII","VIII","IX","X"
};
#endif