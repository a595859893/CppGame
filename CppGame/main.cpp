#include <iostream>
#include <conio.h>
#include<time.h>

#include "Player.h"
#include "Altar.h"
#include "Shop.h"
#include "Battlefield.h"


#define TOTAL_SCENE_NUM 2

void printWelcome();
void startGame(Scene &firstScene, Player *firstPlayer);

int main(int argc, char** argv) {
	//����̨������ʼ��
	SMALL_RECT rc{ 0,0,GAME_WINDOW_WIDTH - 1 , GAME_WINDOW_HEIGHT - 1 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rc);
	UIElement::bufferInit();


	//������������ݳ�ʼ��
	Player player;
	Altar altar("��̳", "�ɹ�ӶӢ�ۼ������");
	Shop shop("�̵�", "�ɹ���װ��ǿ��Ӣ��");
	Battlefield battlefield("ս��", "���������ս׬ȡ��Ǯ");


	//���ӳ���·��
	altar.link(UIElement::NEAR_LEFT, &shop);
	shop.link(UIElement::NEAR_RIGHT, &altar);

	altar.link(UIElement::NEAR_DOWN, &battlefield);
	battlefield.link(UIElement::NEAR_UP, &altar);


	//������Ϸ
	printWelcome();
	startGame(altar, &player);

	return 0;
}


void printWelcome() {
	int i;

	cout << "|==========================================================|" << endl;
	for (i = 0; i < (GAME_WINDOW_HEIGHT - 4) / 2; i++)
		cout << "|                                                          |" << endl;

	cout << "|                   Welcome to CPP_GAME!                   |" << endl;
	cout << "|                Press any key to continue                 |" << endl;


	for (i = 0; i < (GAME_WINDOW_HEIGHT - 4) / 2; i++)
		cout << "|                                                          |" << endl;
	cout << "|==========================================================|" << endl;
	UIElement::putBufferScene();
}

void startGame(Scene &firstScene, Player *firstPlayer) {
	int key;
	bool firstKey = true;

	//������ӳ�ʼ��
	srand((int)time(0));

	while (true)
	{
		key = getch();
		if (key == UIElement::KEY_SPECIAL)//�ǹ��ܼ�ǰ��
			key += getch();

		if (key == 0)
			continue;

		if (firstKey) {//�����������
			firstKey = false;
			firstScene.arrive(firstPlayer);
			firstScene.refresh();
			UIElement::putBufferScene();
			continue;
		}

		if (Scene::getPresentScene().onKeyDown(key)) {
			Scene::getPresentScene().refresh();
			UIElement::putBufferScene();
		}

	}
}