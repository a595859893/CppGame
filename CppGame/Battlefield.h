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
	//����������غϵ���Ϊ
	void enemyTurn();
	//�������ֻغϣ���ʼ��һ�ֻغ�
	void finishTurn();
	//��Ӣ��ִ�ж�����ʱ�򽫻ᱻִ��
	void onDoingAction();

	//�������һ������
	void randomNewEnemy(int index);
	//�������һ������
	void randomEnemys();

	//��ʼ��UI����
	void initScene();
	void initHeroSelected();
	void initAction();
	void initEnemyButton();


	//�������¼�
	bool handleHeroKey();
	bool handleActionKey();
	bool handleEnemyKey();

	//ˢ�����Ӣ�ۡ�����״̬
	void refreshHero(int index);
	void refreshEnemy(int index);
	void refreshAction(int index);
	void refresh();

	//Ӣ�۵Ļغ��ж�״̬
	int heroTurn[MAX_HERO_NUM];
	//��������
	Hero enemy[MAX_ENEMY_NUM];
	int enemyNum;

	//��¼ѡ���Ӣ�ۡ���Ϊ��Ŀ������
	int heroIndex,actionIndex, targetIndex;
	//�ж��Ƿ���ѡ��Ӣ�ۡ���Ϊ��Ŀ�꣬�з��ж��׶�
	bool inSelecting, inAction, inTarget, inEnemy;


	TextArea heroButton[MAX_HERO_NUM],
		actionButton[MAX_ACTION_NUM],
		enemyButton[MAX_ENEMY_NUM];

	//���ڱ�����Ϣ��ʾ
	string tips;


	static const int TURN_TYPE_ACTIVE = 0;
	static const int TURN_TYPE_END = 1;
	static const int TURN_TYPE_STUNNED = 2;

	static string firstName[MAX_ENEMY_FIRST_NAME_NUM];
	static string lastName[MAX_ENEMY_LAST_NAME_NUM];
};
#endif
