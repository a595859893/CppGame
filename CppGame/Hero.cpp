#include "Hero.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int Hero::getMaxHealthPoint() const{return maxHealthPoint;}
int Hero::getMaxManaPoint() const{return maxManaPoint;}
int Hero::getHealthPoint() const{return healthPoint;}
int Hero::getManaPoint() const{return manaPoint;}
int Hero::getAttackPoint() const{return attackPoint;}
int Hero::getDefencePoint() const{return defencePoint;}
string Hero::getName() const{return name;}

void Hero::setHealthPoint(int value){healthPoint = value;}
void Hero::appendHealthPoint(int value){healthPoint += value;}
void Hero::setManaPoint(int value){manaPoint = value; } 
void Hero::appendManaPoint(int value){manaPoint += value;}
void Hero::appendAttackPoint(int value){attackPoint += value;}
void Hero::appendDefencePoint(int value){defencePoint += value;}
void Hero::setName(string const value){name = value;}

void Hero::appendMaxHealthPoint(int value){
	float hpPercentage = healthPoint/(float)maxHealthPoint;
	maxHealthPoint += value;
	healthPoint = (int)max((maxHealthPoint*hpPercentage),1.0f);
}

void Hero::appendMaxManaPoint(int value){
	float mpPercentage = manaPoint/(float)maxManaPoint;
	maxManaPoint += value;
	manaPoint = (int)max((maxManaPoint*mpPercentage),1.0f);
}

bool Hero::deathCheck(Hero &lastAttacker){
	if(Hero::healthPoint<=0 && !deathFlag){
		Hero::deathFlag = true;
		cout<<getName()<<" 已经死亡,凶手是 "<<lastAttacker.getName()<<endl;
		return true;
	}

	return false;
}

int Hero::damageTo(Hero &target,int damage,bool isPhysics){
	if(isPhysics){
		damage-=target.getDefencePoint();
		if(damage < 0)
			damage = 0;
	}
		
	target.appendHealthPoint(-damage);
	cout<<getName()<<" 对 "<<target.getName()<<",造成了 "<<damage<<" 点 ";
	cout<<(isPhysics?"物理":"魔法")<<"伤害"<<endl;
	target.deathCheck(*this);
	
	return damage;
}


Hero::Hero(string name,int maxHp,int maxMp,int atk,int def):
	name(name),
	maxHealthPoint(maxHp),
	maxManaPoint(maxMp),
	healthPoint(maxHp),
	manaPoint(maxMp),
	attackPoint(atk),
	defencePoint(def)
{
	for(int i = 0;i<MAX_EQUIP_NUM;i++){
		equipped[i] = NULL;
	} 
}

bool Hero::useMagicTo(Hero &target,int damage,int manaCost){
	if(manaPoint>=manaCost){
		cout<<getName()<<" 消耗 "<<manaCost<<" 魔法值，对 "<<target.getName()<<" 释放魔法"<<endl;
		appendManaPoint(-manaCost);
		damageTo(target,damage,false);
		return true;	
	} else{
		cout<<getName()<<" 想对 "<<target.getName()<<" 释放魔法，但是魔法值不足失败了"<<endl;
		return false;
	}

}

void Hero::attackTo(Hero &target){
	cout<<getName()<<" 对 "<<target.getName()<<" 进行攻击"<<endl;
	damageTo(target,getAttackPoint(),true);
}

void Hero::defenceFrom(Hero &attacker){
	cout<<getName()<<" 抵挡来自 "<<attacker.getName()<<" 的攻击"<<endl;
	attacker.damageTo(*this,getAttackPoint(),true);
}



int Hero::equip(Equipment &equipment){
	for(int i = 0;i<MAX_EQUIP_NUM;i++){
		if(equipped[i]==NULL){
			equipped[i] = &equipment;
			appendAttackPoint(equipment.getAttackAppend());
			appendDefencePoint(equipment.getDefenceAppend());
			appendMaxManaPoint(equipment.getMaxManaPointAppend());
			appendMaxHealthPoint(equipment.getMaxHealthPointAppend()); 
			
			return i;
		}
	}
 
	return -1;
}

void Hero::unequip(int index){
	cout<<equipped[index]->getName()<<" 被 "<<name<<" 卸下 "<<endl;
	appendAttackPoint(-equipped[index]->getAttackAppend());
	appendDefencePoint(-equipped[index]->getDefenceAppend());
	appendMaxManaPoint(-equipped[index]->getMaxManaPointAppend());
	appendMaxHealthPoint(-equipped[index]->getMaxHealthPointAppend()); 
	equipped[index]=NULL;
	
} 

Equipment& Hero::getEquip(int index){
	return *equipped[index];
}
