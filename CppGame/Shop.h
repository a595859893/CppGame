#ifndef SHOP_H
#define SHOP_H

#include "Scene.h"
#include "Equipment.h"
#include "Hero.h" 
#include "TextArea.h"


#define MAX_SHOP_ROW 2
#define MAX_SHOP_COL 3
#define MAX_SHOP_ITEM (MAX_SHOP_ROW*MAX_SHOP_COL)
#define ITEM_BUTTON_HEIGHT 5
#define ITEM_BUTTON_WIDTH 18

#define SHOP_SELECT_BUTTON_WIDTH 12
#define SHOP_SELECT_BUTTON_HEIGHT (GAME_WINDOW_HEIGHT / 2)

#define MAX_ITEM_PREFIX 6
#define MAX_ITEM_MATERIAL 9

class Shop :public Scene {
public:
	Shop(string name, string description);
	bool onKeyDown(const int key);
private:
	//��װ����������ʱ�Ķ���������ɹ�ʱ����װ��ָ�룬ʧ�ܷ���NULL
	Equipment * onBuyItem(int index, int heroIndex);
	//�������һ���ɹ���������Ӣ��
	void randomNewItem(int index);

	//��ʼ��UI����
	void initEquipementButton();
	void initHeroSelected();

	//ˢ�����Ӣ��״̬
	void refreshHero(int index);
	void refresh();


	//���Թ����װ�����۸�
	Equipment items[MAX_SHOP_ITEM];
	int itemPrice[MAX_SHOP_ITEM];

	//��¼��Ҫ�������Ʒ����
	int equipIndex;
	//�ж��Ƿ�����Ʒ����ѡ��Ӣ�۽׶�
	bool inBuying, inSelecting;

	//��Ʒ����ѡ��Ӣ���ý���
	TextArea itemButton[MAX_SHOP_ITEM],
		heroButton[MAX_HERO_NUM];
	//���ڱ�����Ϣ��ʾ
	string tips;


	//��Ʒ��������þ�̬����
	static string prefixName[MAX_ITEM_PREFIX];
	static string materialName[MAX_ITEM_MATERIAL];
};
#endif
