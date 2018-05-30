#include <iostream>
#include <conio.h>
#include<time.h>

#include "Player.h"
#include "Altar.h"
#include "Shop.h"


#define TOTAL_SCENE_NUM 2

void printWelcome();
void startGame(Scene &firstScene, Player *firstPlayer);

int main(int argc, char** argv) {
	SMALL_RECT rc;
	rc.Top = 0;
	rc.Left = 0;
	rc.Bottom = GAME_WINDOW_HEIGHT - 1;
	rc.Right = GAME_WINDOW_WIDTH - 1;

	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rc);

	Player player;
	Altar altar("祭坛", "可雇佣英雄加入队伍");
	Shop scene("商店", "可购买装备强化英雄");
	Scene *scenes[TOTAL_SCENE_NUM];
	scenes[0] = &scene;
	scenes[0] = &altar;

	altar.link(UIElement::NEAR_LEFT, &scene);
	scene.link(UIElement::NEAR_RIGHT, &altar);

	UIElement::bufferInit();
	printWelcome();
	startGame(scene, &player);


	/*
	//生命值，魔法值，攻击力，防御力
	Hero hero1("拉普拉斯", 300, 300, 10, 5);
	Hero hero2;
	hero2.setName("学渣");

	//攻击力，防御力，生命值，魔法值
	Equipment item[] = {
		Equipment("拉普拉斯妖",8,0,0,15),
		Equipment("拉普拉斯展开",5,0,20,0),
		Equipment("拉普拉斯变换",0,7,0,5),
		Equipment("拉普拉斯算子",0,0,0,0),
		Equipment("拉普拉斯算子",0,0,0,0),
		Equipment("拉普拉斯算子",0,0,0,0),
		Equipment("泰勒展开",10,10,0,0)
	};

	int itemPosition[10];
	for (int i = 0; i < 7; i++) {
		itemPosition[i] = hero1.equip(item[i]);
	}

	hero1.unequip(itemPosition[5]);
	hero1.unequip(itemPosition[4]);
	hero1.unequip(itemPosition[3]);
	hero1.unequip(itemPosition[0]);

	hero2.equip(item[6]);
	hero1.print();

	hero1.attackTo(hero2);
	hero1.defenceFrom(hero2);
	hero1.useMagicTo(hero2, 90, 50);
	hero2.useMagicTo(hero1, 120, 120);
	hero1.attackTo(hero2);

	*/
	return 0;
}

void printWelcome() {
	int i;

	cout << "|==========================================================|" << endl;
	for (i = 0; i < (GAME_WINDOW_HEIGHT - 4) / 2; i++)
		cout << "|                                                          |" << endl;

	cout << "|                   Welcome to CPP_GAME!                   |" << endl;
	cout << "|                Press any key to continue                 |" << endl;


	for (i = 0; i < (GAME_WINDOW_HEIGHT - 4) / 2; i++)
		cout << "|                                                          |" << endl;
	cout << "|==========================================================|" << endl;
	UIElement::putBufferScene();
}

void startGame(Scene &firstScene, Player *firstPlayer) {
	int key;
	bool firstKey = true;

	//随机种子初始化
	srand((int)time(0));

	while (true)
	{
		key = getch();
		if (key == UIElement::KEY_SPECIAL)//是功能键前置
			key += getch();

		if (key == 0)
			continue;

		if (firstKey) {//按任意键继续
			firstKey = false;
			firstScene.arrive(firstPlayer);
			firstScene.refresh();
			UIElement::putBufferScene();
			continue;
		}

		if (Scene::getPresentScene().onKeyDown(key)) {
			Scene::getPresentScene().refresh();
			UIElement::putBufferScene();
		}

	}
}