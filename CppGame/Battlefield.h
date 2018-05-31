#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Scene.h"
#include "Hero.h" 
#include "TextArea.h"

#define MAX_ENEMY_NUM 4
#define MAX_ACTION_NUM 3

#define ACTION_BUTTON_HEIGHT 3
#define ACTION_BUTTON_WIDTH 10

#define BATTLEFIELD_HERO_BUTTON_HEIGHT 8

#define BATTLEFIELD_ENEMY_BUTTON_WIDTH 13
#define BATTLEFIELD_ENEMY_BUTTON_HEIGHT 5

#define MAX_ENEMY_FIRST_NAME_NUM 5
#define MAX_ENEMY_LAST_NAME_NUM 10


class Battlefield :public Scene {

public:
	Battlefield(string name, string description);
	bool onKeyDown(const int key);

private:
	//决定敌人这回合的行为
	void enemyTurn();
	//结束本轮回合，开始新一轮回合
	void finishTurn();
	//当英雄执行动作的时候将会被执行
	void onDoingAction();

	//随机生成一个敌人
	void randomNewEnemy(int index);
	//随机生成一批敌人
	void randomEnemys();

	//初始化UI界面
	void initScene();
	void initHeroSelected();
	void initAction();
	void initEnemyButton();


	//处理按键事件
	bool handleHeroKey();
	bool handleActionKey();
	bool handleEnemyKey();

	//刷新玩家英雄、敌人状态
	void refreshHero(int index);
	void refreshEnemy(int index);
	void refreshAction(int index);
	void refresh();

	//英雄的回合行动状态
	int heroTurn[MAX_HERO_NUM];
	//敌人数据
	Hero enemy[MAX_ENEMY_NUM];
	int enemyNum;

	//记录选择的英雄、行为、目标索引
	int heroIndex,actionIndex, targetIndex;
	//判断是否处于选择英雄、行为、目标，敌方行动阶段
	bool inSelecting, inAction, inTarget, inEnemy;


	TextArea heroButton[MAX_HERO_NUM],
		actionButton[MAX_ACTION_NUM],
		enemyButton[MAX_ENEMY_NUM];

	//用于保存消息提示
	string tips;


	static const int TURN_TYPE_ACTIVE = 0;
	static const int TURN_TYPE_END = 1;
	static const int TURN_TYPE_STUNNED = 2;

	static string firstName[MAX_ENEMY_FIRST_NAME_NUM];
	static string lastName[MAX_ENEMY_LAST_NAME_NUM];
};
#endif
