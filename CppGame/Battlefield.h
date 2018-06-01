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
	//开始敌人这回合的行为
	void enemyTurn();
	//决定敌人的行为
	void enemyAction(int index);
	//结束本轮回合，开始新一轮回合
	void finishTurn();
	//检查战场情况，判断回合和胜负，回合或者胜负变动时返回true
	bool stateCheck();

	//决定动作时触发，如果动作需要目标，将跳转到目标指定界面
	void onDoingAction();
	//让当前选择英雄对索引为target的敌人进行动作
	void onDoingActionToTarget(int target);
	//当动作完成时触发
	void onActionDone();

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

	//展示延时消息,延时单位为毫秒
	void lateMessage(string msg);

	//英雄的回合行动状态
	int heroTurn[MAX_HERO_NUM];
	//敌人数据
	Hero enemy[MAX_ENEMY_NUM];
	int enemyNum;
	//确定当前轮到哪个敌人
	int enemyTurnIndex;

	//记录选择的英雄、行为、目标索引
	int heroIndex, actionIndex, targetIndex;
	//判断是否处于选择英雄、行为、目标，敌方行动阶段
	bool inSelecting, inAction, inTarget, inEnemy;

	//英雄按钮，行为按钮，敌人按钮，消息提示框
	TextArea heroButton[MAX_HERO_NUM],
		actionButton[MAX_ACTION_NUM],
		enemyButton[MAX_ENEMY_NUM],
		textButton;

	//用于保存消息提示
	string tips;


	static const int TURN_TYPE_ACTIVE = 0;
	static const int TURN_TYPE_END = 1;
	static const int TURN_TYPE_STUNNED = 2;

	static const int ACTION_ATTACK = 0;
	static const int ACTION_MAGIC = 1;
	static const int ACTION_WAIT = 2;


	static string firstName[MAX_ENEMY_FIRST_NAME_NUM];
	static string lastName[MAX_ENEMY_LAST_NAME_NUM];
};
#endif
