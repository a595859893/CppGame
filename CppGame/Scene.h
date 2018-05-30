#ifndef SCENE_H
#define SCENE_H

#include <string>

#include "UIElement.h"
#include "Player.h"

#define MAX_NEAR_SCENE 4 

class Scene :public UIElement {

public:
	Scene(string name = "未命名场景", string description = "尚未添加说明");

	//获取当前所在的场景
	static Scene& getPresentScene();

	string getName() const;
	string getDescription()const;
	Player& getPlayer();

	//将目标场景与本场景连接，使其成为临近场景 
	virtual void link(int direction, Scene * nearScene);
	//让玩家跳转到当前场景
	virtual void arrive(Player * const player);

	//刷新场景的UI界面
	virtual void refresh();
	//处理按键信息
	virtual bool onKeyDown(const int key);
protected:
	//用于打印场景信息
	void showDescription();
	//用于打印场景可通行路径
	void showPath();
private:
	//当前玩家所在的场景
	static Scene *presentScene;
	//记录进入该场景的玩家，即用户操控的玩家 
	Player * player;

	//当前场景名字
	string name;
	string description;

	//记录临近的场景,可以通过这个场景直接跳转到对方场景 
	Scene *nearScene[MAX_NEAR_SCENE];
};
#endif
