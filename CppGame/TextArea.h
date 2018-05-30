#ifndef HERO_BUTTON_H
#define HERO_BUTTON_H

#define MAX_MESSAGE_NUM 20

#include "UIElement.h"
#include "Hero.h"

class TextArea :public UIElement {
public:
	//��������г�ʼ��
	void init(int posX = 0, int posY = 0, int width = 3, int height = 3);

	//��ȡ��һ�������µİ�������ȡ�󴢴�İ������ᱻ���
	int getPressedKey();
	//ˢ�³�����UI����
	void refresh();
	//��������Ϣ
	bool onKeyDown(const int key);


	//��λ��д���ֵ���ʼ����
	void setWriteCursor(int posX, int posY);
	//���������д����,align����������뷽ʽ��strWidth������ٿ���Զ�����(Ĭ�ϳ��������Ȼ���)
	bool writeLine(string str, int align = -1, int strWidth = -1);
	//��ת����һ��
	void nextLine();
	//��ո�����ϻ��Ƶ�����
	void clear();

private:
	//���ڼ�¼�ı���Ϣ�Ľṹ��
	typedef struct {
		int posX, posY, align;
		string msg;
	}TextMessage;

	int messageNum;
	TextMessage messages[MAX_MESSAGE_NUM];


	//��ǰ�α�λ��
	int cusorX, cusorY;
	//�洢�İ���
	int storedKey;
};

#endif // !HERO_BUTTON_H
