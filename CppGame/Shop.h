#ifndef SHOP_H
#define SHOP_H

#include "Scene.h"
#include "Equipment.h"
#include "Hero.h" 
#include "TextArea.h"


#define MAX_SHOP_ROW 2
#define MAX_SHOP_COL 3
#define MAX_SHOP_ITEM (MAX_SHOP_ROW*MAX_SHOP_COL)
#define ITEM_BUTTON_HEIGHT 4
#define ITEM_BUTTON_WIDTH 12

#define MAX_ITEM_TYPE 6
#define MAX_ITEM_PREFIX 6

class Shop :public Scene {
public:
	Shop(string name, string description);
	bool onKeyDown(const int key);
private:
	//���ڱ�����Ϣ��ʾ
	string tips;
	//���Թ����װ�����۸�Ͷ�ӦUI�����ť
	Equipment items[MAX_SHOP_ITEM];
	int itemPrice[MAX_SHOP_ITEM];
	TextArea itemButton[MAX_SHOP_ITEM];

	void refresh();

	//��Ӣ�۱���������ʱ�����Ķ���
	void onBuyItem(int index);
	//�������һ���ɹ���������Ӣ��
	void randomNewItem(int index);

	static string typeName[MAX_ITEM_TYPE];
	static string prefixName[MAX_ITEM_PREFIX];
};
#endif
