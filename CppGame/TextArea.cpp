#ifndef HERO_BUTTON_CPP
#define HERO_BUTTON_CPP

#include "TextArea.h"
#include <string>

void TextArea::init(int posX, int posY, int width, int height)
{
	this->messageNum = 0;
	this->storedKey = -1;
	this->changePosition(posX, posY);
	this->changeSize(width, height);
}

bool TextArea::onKeyDown(const int key)
{
	if (isOnKeyHandle())
		storedKey = key;

	return UIElement::onKeyDown(key);
}

void TextArea::refresh()
{
	fillWith(' ');
	printBoundary(isOnKeyFocus());

	TextMessage nowText;
	int i;
	for (i = 0; i < messageNum; i++) {
		print(messages[i].posX, messages[i].posY, messages[i].msg, messages[i].align);
	}

	UIElement::refresh();
}

void TextArea::clear()
{
	messageNum = 0;
}


void TextArea::setWriteCursor(int posX, int posY)
{
	this->cusorX = posX;
	this->cusorY = posY;
}

bool TextArea::writeLine(string str, int align, int strWidth)
{
	int length = str.length();
	int space = strWidth > 0 ? strWidth : width - cusorX;
	int remain = 0;


	while (remain < length) {
		messages[messageNum] = TextMessage{ cusorX, cusorY,align, str.substr(remain,space) };
		messageNum++;

		if (messageNum >= MAX_MESSAGE_NUM)
			return false;

		remain += space;
		cusorY++;
	}

	return true;
}

void TextArea::nextLine()
{
	cusorY++;
}

int TextArea::getPressedKey()
{
	int temp = storedKey;
	storedKey = -1;
	return temp;
}

#endif // !HERO_BUTTON_CPP



