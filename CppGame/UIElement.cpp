#ifndef UI_ELEMENT_CPP
#define UI_ELEMENT_CPP

#include "UIElement.h"

using namespace std;

UIElement::UIElement(int posX, int posY, int width, int height) :
	posX(posX), posY(posY), width(width), height(height),
	previousElement(NULL), showElementNum(0), onKeyFocus(false), onKeyHandle(false) {
	int i;
	for (i = 0; i < KEY_NUM; i++) {
		nearElement[i] = NULL;
	}
	for (i = 0; i < MAX_SHOWN_ELEMENT; i++) {
		showElement[i] = NULL;
	}
}

bool UIElement::show(UIElement *element) {
	if (showElementNum >= MAX_SHOWN_ELEMENT)
		return false;

	int i;
	for (i = 0; i < showElementNum; i++) {
		if (showElement[i] == element) {
			return false;
		}
	}

	showElement[showElementNum] = element;
	showElementNum++;

	element->refresh();
	element->onShow();
	return true;
}

bool UIElement::hide(UIElement *element) {
	int i;
	for (i = 0; i < showElementNum; i++) {
		if (showElement[i] == element) {
			element->hideAll();
			showElementNum--;
			showElement[i] = showElement[showElementNum];
			showElement[showElementNum] = NULL;
			return true;
		}
	}

	return false;
}

void UIElement::refresh() {
	int i;
	for (i = 0; i < showElementNum; i++)
		showElement[i]->refresh();
}

void UIElement::onShow() {}

void UIElement::hideAll()
{
	int i;
	for (i = 0; i < showElementNum; i++) {
		showElement[i]->hideAll();
		showElement[i] = NULL;
	}
	showElementNum = 0;
}

bool UIElement::onKeyDown(const int key) {
	int i;

	if (isOnKeyHandle()) {
		if (key == UIElement::KEY_CANCEL && previousElement != NULL) {
			back();
			return true;
		}

		for (i = 0; i < KEY_NUM; i++) {
			if (key == KEY_DIRECTIONS[i] && nearElement[i] != NULL) {
				moveTo(nearElement[i]);
				return true;
			}
		}
	}

	if (isOnKeyFocus()) {
		for (i = 0; i < showElementNum; i++) {
			if (showElement[i]->onKeyDown(key))
				return true;
		}
	}

	return false;
}

void UIElement::link(UIElement * element, int position)
{
	nearElement[position] = element;
}

void UIElement::jumpTo(UIElement *element) {
	focusOn(element, this);
	show(element);
}
void UIElement::moveTo(UIElement * element) {
	focusOn(element, previousElement);
}
void UIElement::back() {
	focusOn(previousElement, NULL);
	hideAll();
}

UIElement & UIElement::getPreviousElement() { return *previousElement; }
bool UIElement::isOnKeyFocus() { return onKeyFocus; }
bool UIElement::isOnKeyHandle() { return onKeyHandle; }

void UIElement::focusOn(UIElement * target, UIElement * backElement)
{
	previousElement = NULL;
	onKeyFocus = (backElement == this);
	onKeyHandle = false;
	target->onKeyFocus = true;
	target->onKeyHandle = true;

	if (backElement != NULL)
		target->previousElement = backElement;
}

void UIElement::changePosition(int x, int y)
{
	posX = x;
	posY = y;
}

void UIElement::changeSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void UIElement::print(int relativeX, int relativeY, string str, int align) {
	COORD coord;
	coord.X = posX + relativeX;
	coord.Y = posY + relativeY;
	switch (align)
	{
	case(ALIGN_FRONT):
		coord.X -= (short)str.length() / 2;
		break;
	case(ALIGN_RIGHT):
		coord.X -= (short)str.length();
		break;
	default:
		break;
	}

	SetConsoleCursorPosition(hout, coord);
	cout << str;
}

void UIElement::triggerKeyDown(const int key)
{
	if (isOnKeyFocus()) {
		onKeyDown(key);
	}
	else {
		int i = 0;
		for (i = 0; i < showElementNum; i++) {
			triggerKeyDown(key);
		}
	}
}

int UIElement::keyTodirection(int key)
{
	int i;
	for (i = 0; i < KEY_NUM; i++) {
		if (key == KEY_DIRECTIONS[i])
			return i;
	}
	return -1;
}

void UIElement::printLineVerticle(int relativeX, int relativeY, int length, bool solid) {
	int i;
	for (i = 0; i < length; i++) {
		if (solid || i % 2 == 0) {
			print(relativeX, relativeY + i, "|");
		}
	}
}

void UIElement::printLineHorizontal(int relativeX, int relativeY, int length, bool solid) {
	int i;
	for (i = 0; i < length; i++) {
		if (solid || i % 2 == 0) {
			print(relativeX + i, relativeY, "=");
		}
	}
}

void UIElement::fillWith(char fill)
{
	COORD coord = { posX,posY };
	DWORD written = 0;

	int i;
	for (i = 0; i < height; i++) {
		FillConsoleOutputCharacter(hout, (TCHAR)fill, width, coord, &written);
		coord.Y++;
	}

}

void UIElement::printBoundary(bool isFocus) {
	printLineHorizontal(1, 0, width - 2, isFocus);
	printLineHorizontal(1, height - 1, width - 2, isFocus);
	printLineVerticle(0, 0, height, isFocus);
	printLineVerticle(width - 1, 0, height, isFocus);
}

void UIElement::putBufferScene()
{
	DWORD written = 0;
	COORD coord = { 0,0 };
	COORD size = { GAME_WINDOW_WIDTH,GAME_WINDOW_HEIGHT };
	CHAR_INFO data[GAME_WINDOW_SIZE];
	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Right = GAME_WINDOW_WIDTH;
	rect.Bottom = GAME_WINDOW_HEIGHT;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hout, &csbi);
	ReadConsoleOutput(hout, data, size, coord, &rect);
	WriteConsoleOutput(houtBuffer, data, size, coord, &rect);
	FillConsoleOutputCharacter(hout, (TCHAR) ' ', csbi.dwSize.X * GAME_WINDOW_HEIGHT, coord, &written);
}

void UIElement::bufferInit()
{
	//获取控制台缓冲区，并创建双重缓冲区
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	houtBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	//隐藏缓冲区光标
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hout, &cci);
	SetConsoleCursorInfo(houtBuffer, &cci);

	//设置新的缓冲区为活动显示缓冲
	SetConsoleActiveScreenBuffer(houtBuffer);
}


const int UIElement::KEY_DIRECTIONS[KEY_NUM] = {
	UIElement::KEY_UP,
	UIElement::KEY_DOWN,
	UIElement::KEY_LEFT,
	UIElement::KEY_RIGHT
};
HANDLE UIElement::hout;
HANDLE UIElement::houtBuffer;
CONSOLE_CURSOR_INFO UIElement::cci;
#endif 
