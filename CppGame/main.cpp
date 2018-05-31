#include <iostream>
#include <conio.h>
#include<time.h>

#include "Player.h"
#include "Altar.h"
#include "Shop.h"
#include "Battlefield.h"


#define TOTAL_SCENE_NUM 2

void printWelcome();
void startGame(Scene &firstScene, Player *firstPlayer);

int main(int argc, char** argv) {
	//控制台参数初始化
	SMALL_RECT rc{ 0,0,GAME_WINDOW_WIDTH - 1 , GAME_WINDOW_HEIGHT - 1 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rc);
	UIElement::bufferInit();


	//场景和玩家数据初始化
	Player player;
	Altar altar("祭坛", "可雇佣英雄加入队伍");
	Shop shop("商店", "可购买装备强化英雄");
	Battlefield battlefield("战场", "可与敌人作战赚取金钱");


	//连接场景路径
	altar.link(UIElement::NEAR_LEFT, &shop);
	shop.link(UIElement::NEAR_RIGHT, &altar);

	altar.link(UIElement::NEAR_DOWN, &battlefield);
	battlefield.link(UIElement::NEAR_UP, &altar);


	//启动游戏
	printWelcome();
	startGame(altar, &player);

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