#ifndef SCENE_CPP
#define SCENE_CPP

#include "Scene.h"


Player & Scene::getPlayer()
{
	return *player;
}

Scene::Scene(string name, string description) :
	UIElement(0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT),
	name(name), description(description), player(NULL) {
	int i;
	for (i = 0; i < MAX_NEAR_SCENE; i++) {
		nearScene[i] = NULL;
	}
}

bool Scene::onKeyDown(const int key) {
	if (isOnKeyHandle()) {
		int direction = keyTodirection(key);

		if (direction != -1 && nearScene[direction] != NULL) {
			nearScene[direction]->arrive(player);
			return true;
		}

	}

	return UIElement::onKeyDown(key);
}

void Scene::link(int direction, Scene * nearScene) {
	this->nearScene[direction] = nearScene;
}

void Scene::arrive(Player * const player) {
	if (presentScene != NULL) {
		presentScene->hideAll();
		presentScene->focusOn(this, NULL);
	}
	else {
		focusOn(this, NULL);
	}

	this->player = player;
	presentScene = this;
}

void Scene::refresh() {
	printBoundary(isOnKeyFocus());
	showPath();
	showDescription();

	UIElement::refresh();
}

void Scene::showPath() {
	if (nearScene[NEAR_UP] != NULL) {
		print(width / 2, 0, "↑", UIElement::ALIGN_FRONT);
		print(width / 2, 1, nearScene[NEAR_UP]->getName(), UIElement::ALIGN_FRONT);
	}

	if (nearScene[NEAR_DOWN] != NULL) {
		print(width / 2, height - 1, "↓", UIElement::ALIGN_FRONT);
		print(width / 2, height - 2, nearScene[NEAR_DOWN]->getName(), UIElement::ALIGN_FRONT);
	}

	if (nearScene[NEAR_LEFT] != NULL) {
		print(0, height / 2, "←");
		print(2, height / 2, nearScene[NEAR_LEFT]->getName());
	}

	if (nearScene[NEAR_RIGHT] != NULL) {
		print(width - 2, height / 2, "→");
		print(width - 3, height / 2, nearScene[NEAR_RIGHT]->getName(), UIElement::ALIGN_RIGHT);
	}
}

void Scene::showDescription()
{
	int grid = 10;
	int startHeight = height / 2 - 3;
	print(width / 2, startHeight + 1, "===== 当前场景 =====", UIElement::ALIGN_FRONT);
	print(width / 2, startHeight + 2, "[" + getName() + "]", UIElement::ALIGN_FRONT);
	print(width / 2, startHeight + 3, "\"" + getDescription() + "\"", UIElement::ALIGN_FRONT);
	print(width / 2, startHeight + 4, "===按 'Z' 进入场景==", UIElement::ALIGN_FRONT);
}

string Scene::getName() const { return name; }
string Scene::getDescription() const { return description; }

Scene & Scene::getPresentScene() { return *presentScene; }
Scene *Scene::presentScene = NULL;
#endif
