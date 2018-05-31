#ifndef UI_ELEMENT_H 
#define UI_ELEMENT_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

#define KEY_NUM 4
#define MAX_SHOWN_ELEMENT 20
#define GAME_WINDOW_WIDTH 60
#define GAME_WINDOW_HEIGHT 24
#define GAME_WINDOW_SIZE (GAME_WINDOW_WIDTH * GAME_WINDOW_HEIGHT)

using namespace std;

class UIElement {

public:
	//构造函数，创建一个UI组件在(posX,posY)处，并拥有width宽度和height的高度
	UIElement(int posX = 0, int posY = 0, int width = 3, int height = 3);


	//处理按键被按下事件 ，返回该按键是否属于有效输入
	virtual bool onKeyDown(const int key);
	//刷新该菜单UI显示,传入父组件的绝对偏移坐标以供计算
	virtual void refresh();


	//当组件被显示的时候执行的动作
	virtual void onShow();
	//在该组件上方显示某个组件,如果该组件已经被显示，则返回false
	virtual bool show(UIElement *element);
	//隐藏处于该组件上方显示的组件，如果该组件已被隐藏，则返回false
	virtual bool hide(UIElement *element);
	//隐藏所有处于该组件上方显示的组件 
	void hideAll();


	//设置该组件可跳转的相邻UI组件
	void link(UIElement *element, int position);
	//跳转到对应的UI组件上,目标组件将会成为该组件的子组件 
	void jumpTo(UIElement *element);
	//移动到对应组件上，回退时将会退至本组件上一级的组件
	void moveTo(UIElement *element);
	//回退至上一层组件，并且返回一些参数
	void back();


	//修改UI组件所在的位置
	void setPosition(int x, int y);
	//修改UI组件的宽高
	void setSize(int width, int height);
	//设置UI组件是否可以默认通过返回键返回父级组件
	void setBackEnable(bool enable);


	//数据获取函数
	UIElement& getPreviousElement();
	bool isOnKeyFocus();
	bool isOnKeyHandle();


	//应用控制台双缓冲，将下一帧渲染好的界面映射到控制台上
	static void putBufferScene();
	//初始化UI界面用静态变量
	static void bufferInit();


	//转换按键索引为方向索引
	static int keyTodirection(int key);
	static const int KEY_DIRECTIONS[KEY_NUM];

	//按钮索引与方向索引常量
	static const int NEAR_UP = 0;
	static const int NEAR_DOWN = 1;
	static const int NEAR_LEFT = 2;
	static const int NEAR_RIGHT = 3;

	static const int KEY_SPECIAL = 224;
	static const int KEY_UP = 0x48 + KEY_SPECIAL;
	static const int KEY_DOWN = 0x50 + KEY_SPECIAL;
	static const int KEY_LEFT = 0x4b + KEY_SPECIAL;
	static const int KEY_RIGHT = 0x4d + KEY_SPECIAL;
	static const int KEY_OK = 'z';
	static const int KEY_CANCEL = 'x';


	//字体对齐常量
	static const int ALIGN_FRONT = 1;
	static const int ALIGN_RIGHT = 2;

protected:
	//用于判断条件并决定是否触发本组件的onKeyDown函数
	void triggerKeyDown(const int key);
	//将焦点移动至目标UI组件，并且为其设置子UI组件
	void focusOn(UIElement *target, UIElement *backElement);


	//用自定字符填满该控件
	void fillWith(char fill);
	//在UI组件的窗口内的相对坐标下打印字符 ,aligne为对齐方式，详见ALIGN_开头的静态常量
	void print(int relativeX, int relativeY, string str, int align = -1);
	//在UI组件的窗口内画出一条垂直\水平的直线
	//length代表线的长度，isVertivle为true时为竖直的线，false时为水平的线
	void printLineVerticle(int relativeX, int relativeY, int length, bool solid);
	void printLineHorizontal(int relativeX, int relativeY, int length, bool solid);
	//绘制UI组件的边界，isFocus用于决定绘制边界是虚线还是实线 
	void printBoundary(bool isFocus);


	//UI组件窗口的位置偏移及宽高
	int posX, posY, width, height;
	//是否应该响应并传递按键事件、是否处理按键事件
	bool onKeyFocus, onKeyHandle;

private:
	//父UI组件和4方向上临近的UI组件
	UIElement * previousElement;
	//记录相邻的组件,0~3分别为上、下、左、右 
	UIElement *nearElement[4];
	//记录该UI组件上方显示的UI
	UIElement *showElement[MAX_SHOWN_ELEMENT];
	int showElementNum;

	//是否可以默认通过返回键返回父级组件
	bool backEnable;


	//控制台界面刷新用静态变量
	static HANDLE hout;
	static HANDLE houtBuffer;
	static CONSOLE_CURSOR_INFO cci;

};

#endif 
