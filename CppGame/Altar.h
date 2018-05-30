#ifndef ALTAR_H
#define ALTAR_H

#include "Scene.h"
#include "Hero.h" 
#include "TextArea.h"

#define MAX_MANAGE_HEROS 4
#define HERO_BUTTON_HEIGHT (GAME_WINDOW_HEIGHT / 2)
#define HERO_BUTTON_WIDTH 12

#define MAX_FIRST_NAME_NUM 5
#define MAX_LAST_NAME_NUM 8

class Altar :public Scene {
public:
	Altar(string name, string description);
	bool onKeyDown(const int key);
private:
	//用于保存消息提示
	string tips;

	//可以雇佣的英雄、价格和对应UI组件按钮
	Hero heros[MAX_MANAGE_HEROS];
	int heroPrice[MAX_MANAGE_HEROS];
	TextArea heroButton[MAX_MANAGE_HEROS];

	void refresh();

	//当英雄将被雇佣的时候做的动作
	void onBuyHero(int index);
	//随机生成一个可雇佣的英雄
	void randomNewHero(int index);

	static string firstName[MAX_FIRST_NAME_NUM];
	static string lastName[MAX_LAST_NAME_NUM];
};
#endif
