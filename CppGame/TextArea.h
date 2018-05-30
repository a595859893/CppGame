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

	//定位书写文字的起始坐标
	void setWriteCursor(int posX, int posY);
	//在组件上书写文字
	bool writeLine(string str, int align = -1);
	//跳转到下一行
	void nextLine();
	//清空该组件上绘制的文字
	void clear();
	//获取上一个被按下的按键，获取后储存的按键将会被清除
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
