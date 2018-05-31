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
	//���캯��������һ��UI�����(posX,posY)������ӵ��width��Ⱥ�height�ĸ߶�
	UIElement(int posX = 0, int posY = 0, int width = 3, int height = 3);


	//�������������¼� �����ظð����Ƿ�������Ч����
	virtual bool onKeyDown(const int key);
	//ˢ�¸ò˵�UI��ʾ,���븸����ľ���ƫ�������Թ�����
	virtual void refresh();


	//���������ʾ��ʱ��ִ�еĶ���
	virtual void onShow();
	//�ڸ�����Ϸ���ʾĳ�����,���������Ѿ�����ʾ���򷵻�false
	virtual bool show(UIElement *element);
	//���ش��ڸ�����Ϸ���ʾ����������������ѱ����أ��򷵻�false
	virtual bool hide(UIElement *element);
	//�������д��ڸ�����Ϸ���ʾ����� 
	void hideAll();


	//���ø��������ת������UI���
	void link(UIElement *element, int position);
	//��ת����Ӧ��UI�����,Ŀ����������Ϊ������������ 
	void jumpTo(UIElement *element);
	//�ƶ�����Ӧ����ϣ�����ʱ���������������һ�������
	void moveTo(UIElement *element);
	//��������һ����������ҷ���һЩ����
	void back();


	//�޸�UI������ڵ�λ��
	void setPosition(int x, int y);
	//�޸�UI����Ŀ��
	void setSize(int width, int height);
	//����UI����Ƿ����Ĭ��ͨ�����ؼ����ظ������
	void setBackEnable(bool enable);


	//���ݻ�ȡ����
	UIElement& getPreviousElement();
	bool isOnKeyFocus();
	bool isOnKeyHandle();


	//Ӧ�ÿ���̨˫���壬����һ֡��Ⱦ�õĽ���ӳ�䵽����̨��
	static void putBufferScene();
	//��ʼ��UI�����þ�̬����
	static void bufferInit();


	//ת����������Ϊ��������
	static int keyTodirection(int key);
	static const int KEY_DIRECTIONS[KEY_NUM];

	//��ť�����뷽����������
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


	//������볣��
	static const int ALIGN_FRONT = 1;
	static const int ALIGN_RIGHT = 2;

protected:
	//�����ж������������Ƿ񴥷��������onKeyDown����
	void triggerKeyDown(const int key);
	//�������ƶ���Ŀ��UI���������Ϊ��������UI���
	void focusOn(UIElement *target, UIElement *backElement);


	//���Զ��ַ������ÿؼ�
	void fillWith(char fill);
	//��UI����Ĵ����ڵ���������´�ӡ�ַ� ,aligneΪ���뷽ʽ�����ALIGN_��ͷ�ľ�̬����
	void print(int relativeX, int relativeY, string str, int align = -1);
	//��UI����Ĵ����ڻ���һ����ֱ\ˮƽ��ֱ��
	//length�����ߵĳ��ȣ�isVertivleΪtrueʱΪ��ֱ���ߣ�falseʱΪˮƽ����
	void printLineVerticle(int relativeX, int relativeY, int length, bool solid);
	void printLineHorizontal(int relativeX, int relativeY, int length, bool solid);
	//����UI����ı߽磬isFocus���ھ������Ʊ߽������߻���ʵ�� 
	void printBoundary(bool isFocus);


	//UI������ڵ�λ��ƫ�Ƽ����
	int posX, posY, width, height;
	//�Ƿ�Ӧ����Ӧ�����ݰ����¼����Ƿ������¼�
	bool onKeyFocus, onKeyHandle;

private:
	//��UI�����4�������ٽ���UI���
	UIElement * previousElement;
	//��¼���ڵ����,0~3�ֱ�Ϊ�ϡ��¡����� 
	UIElement *nearElement[4];
	//��¼��UI����Ϸ���ʾ��UI
	UIElement *showElement[MAX_SHOWN_ELEMENT];
	int showElementNum;

	//�Ƿ����Ĭ��ͨ�����ؼ����ظ������
	bool backEnable;


	//����̨����ˢ���þ�̬����
	static HANDLE hout;
	static HANDLE houtBuffer;
	static CONSOLE_CURSOR_INFO cci;

};

#endif 
