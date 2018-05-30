#ifndef HERO_BUTTON_H
#define HERO_BUTTON_H

#define MAX_MESSAGE_NUM 20

#include "UIElement.h"
#include "Hero.h"

class TextArea :public UIElement {
public:
	void init(int posX = 0, int posY = 0, int width = 3, int height = 3);

	bool onKeyDown(const int key);
	void refresh();

	//��λ��д���ֵ���ʼ����
	void setWriteCursor(int posX, int posY);
	//���������д����
	bool writeLine(string str, int align = -1);
	//��ת����һ��
	void nextLine();
	//��ո�����ϻ��Ƶ�����
	void clear();
	//��ȡ��һ�������µİ�������ȡ�󴢴�İ������ᱻ���
	int getPressedKey();
private:
	typedef struct {
		int posX, posY, align;
		string msg;
	}TextMessage;

	int cusorX, cusorY, storedKey, messageNum;
	TextMessage messages[MAX_MESSAGE_NUM];
};

#endif // !HERO_BUTTON_H
