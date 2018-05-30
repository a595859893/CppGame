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
	//��ʼ��UI����
	void initEnemyButton();
	void initHeroSelected();
	void initAction();

	//ˢ�����Ӣ�ۡ�����״̬
	void refreshHero(int index);
	void refreshEnemy(int index);
	void refresh();


	//��Ӣ��ִ�ж�����ʱ�򽫻ᱻִ��
	Equipment* onDoingAction(int index, int heroIndex);
	//�������һ���ɹ���������Ӣ��
	void randomNewEnemy(int index);

	//��¼ѡ���Ӣ�ۡ���Ϊ��Ŀ������
	int heroIndex��actionIndex, targetIndex;
	//�ж��Ƿ���ѡ��Ӣ�ۡ���Ϊ��Ŀ�꣬�з��ж��׶�
	bool inSelecting, inAction, inTarget, inEnemy;

	//ѡ��Ӣ�ۡ���Ϊ��Ŀ�����
	TextArea heroButton[MAX_HERO_NUM],
		actionButton[MAX_ACTION_NUM],
		enemyButton[MAX_ENEMY_NUM];
	//���ڱ�����Ϣ��ʾ
	string tips;

};
#endif
