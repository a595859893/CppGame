#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Scene.h"
#include "Hero.h" 
#include "TextArea.h"

#define MAX_ENEMY_NUM 6
#define MAX_ACTION_NUM 2

#define ACTION_BUTTON_HEIGHT 5
#define ACTION_BUTTON_WIDTH 2

#define BATTLEFIELD_HERO_BUTTON_WIDTH 12
#define BATTLEFIELD_HERO_BUTTON_HEIGHT 8


class Battlefield :public Scene {

public:
	Battlefield(string name, string description);
	bool onKeyDown(const int key);

private:
	//初始化UI界面
	void initEnemyButton();
	void initHeroSelected();
	void initAction();

	//刷新玩家英雄、敌人状态
	void refreshHero(int index);
	void refreshEnemy(int index);
	void refresh();


	//当英雄执行动作的时候将会被执行
	Equipment* onDoingAction(int index, int heroIndex);
	//随机生成一个可供加入管理的英雄
	void randomNewEnemy(int index);

	//记录选择的英雄、行为、目标索引
	int heroIndex，actionIndex, targetIndex;
	//判断是否处于选择英雄、行为、目标，敌方行动阶段
	bool inSelecting, inAction, inTarget, inEnemy;

	//选择英雄、行为、目标界面
	TextArea heroButton[MAX_HERO_NUM],
		actionButton[MAX_ACTION_NUM],
		enemyButton[MAX_ENEMY_NUM];
	//用于保存消息提示
	string tips;

};
#endif
