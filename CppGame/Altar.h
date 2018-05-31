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
	//��Ӣ�۽�����Ӷ��ʱ�����Ķ���
	void onBuyHero(int index);
	//�������һ���ɹ�Ӷ��Ӣ��
	void randomNewHero(int index);

	//��ʼ��UI����
	void initScene();
	void initHeroSelected();
	//�������¼�
	bool handleHeroKey();
	//����ˢ�º���
	void refresh();


	//���Թ�Ӷ��Ӣ�ۡ��۸�Ͷ�ӦUI�����ť
	Hero heros[MAX_MANAGE_HEROS];
	int heroPrice[MAX_MANAGE_HEROS];
	TextArea heroButton[MAX_MANAGE_HEROS];

	//���ڱ�����Ϣ��ʾ
	string tips;


	//Ӣ����������þ�̬����
	static string firstName[MAX_FIRST_NAME_NUM];
	static string lastName[MAX_LAST_NAME_NUM];
};
#endif
