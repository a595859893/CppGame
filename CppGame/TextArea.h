#ifndef HERO_BUTTON_H
#define HERO_BUTTON_H

#define MAX_MESSAGE_NUM 20

#include "UIElement.h"
#include "Hero.h"

class TextArea :public UIElement {
public:
	//对组件进行初始化
	void init(int posX = 0, int posY = 0, int width = 3, int height = 3);

	//获取上一个被按下的按键，获取后储存的按键将会被清除
	int getPressedKey();
	//刷新场景的UI界面
	void refresh();
	//处理按键信息
	bool onKeyDown(const int key);


	//定位书写文字的起始坐标
	void setWriteCursor(int posX, int posY);
	//在组件上书写文字,align代表字体对齐方式，strWidth代表多少宽度自动换行(默认超过组件宽度换行)
	bool writeLine(string str, int align = -1, int strWidth = -1);
	//跳转到下一行
	void nextLine();
	//清空该组件上绘制的文字
	void clear();

private:
	//用于记录文本信息的结构体
	typedef struct {
		int posX, posY, align;
		string msg;
	}TextMessage;

	int messageNum;
	TextMessage messages[MAX_MESSAGE_NUM];


	//当前游标位置
	int cusorX, cusorY;
	//存储的按键
	int storedKey;
};

#endif // !HERO_BUTTON_H
