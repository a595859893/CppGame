#ifndef SCENE_H
#define SCENE_H

#include <string>

#include "UIElement.h"
#include "Player.h"

#define MAX_NEAR_SCENE 4 

class Scene :public UIElement {

public:
	Scene(string name = "δ��������", string description = "��δ���˵��");

	//��ȡ��ǰ���ڵĳ���
	static Scene& getPresentScene();

	string getName() const;
	string getDescription()const;
	Player& getPlayer();

	//��Ŀ�곡���뱾�������ӣ�ʹ���Ϊ�ٽ����� 
	virtual void link(int direction, Scene * nearScene);
	//�������ת����ǰ����
	virtual void arrive(Player * const player);

	//ˢ�³�����UI����
	virtual void refresh();
	//��������Ϣ
	virtual bool onKeyDown(const int key);
protected:
	//���ڴ�ӡ������Ϣ
	void showDescription();
	//���ڴ�ӡ������ͨ��·��
	void showPath();
private:
	//��ǰ������ڵĳ���
	static Scene *presentScene;
	//��¼����ó�������ң����û��ٿص���� 
	Player * player;

	//��ǰ��������
	string name;
	string description;

	//��¼�ٽ��ĳ���,����ͨ���������ֱ����ת���Է����� 
	Scene *nearScene[MAX_NEAR_SCENE];
};
#endif
