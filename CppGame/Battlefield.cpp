#ifndef BATTLEFIELD_CPP
#define BATTLEFIELD_CPP

#include "Battlefield.h"

Battlefield::Battlefield(string name, string description)
{
}

bool Battlefield::onKeyDown(const int key)
{
	return false;
}

void Battlefield::initEnemyButton()
{
}

void Battlefield::initHeroSelected()
{
}

void Battlefield::initAction()
{
}

void Battlefield::refreshHero(int index)
{
}

void Battlefield::refreshEnemy(int index)
{
}

void Battlefield::refresh()
{
}

Equipment * Battlefield::onDoingAction(int index, int heroIndex)
{
	return nullptr;
}

void Battlefield::randomNewEnemy(int index)
{
}

#endif