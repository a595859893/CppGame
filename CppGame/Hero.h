#ifndef HERO_H
#define HERO_H

#define MAX_EQUIP_NUM 6

#include <iostream>

#include "Equipment.h"


using namespace std;

class Hero {
public:
	//����һ��Ӣ�ۣ�����name������maxHp���������ޣ�maxMp��ħ������,atk�Ĺ�������def�ķ����� 
	explicit Hero(string name = "������", int maxHp = 100, int maxMp = 100, int atk = 0, int def = 0);


	//����ħ��ֵ����targetӢ���ͷ�һ��ħ������ɷ������˺�(���ᱻdefence����)������ħ���Ƿ�ɹ��ͷ� 
	bool useMagicTo(Hero &target, int damage, int manaCost);
	//����targetӢ�ۣ�����targetӢ�۵�����ֵ��ֵȡ�����Լ��Ĺ������ͶԷ��ķ����� 
	void attackTo(Hero &target);
	//�ܵ�����attackerӢ�۵Ĺ����������Լ�������ֵ��ֵȡ����targetӢ�۵Ĺ��������Լ��ķ����� 
	void defenceFrom(Hero &attacker);


	//װ��equipment��������ṩ�����Լӳɣ����ر�װ����λ�ã�װ��ʧ�ܷ���-1�� 
	int equip(Equipment &equipment);
	//ж�¶�Ӧ��Ʒ��λ�õ�װ����Ӣ�۽��������������Ʒ�ṩ�����Լӳ� 
	void unequip(int index);
	//����Ӣ��������Ʒ��λ�ã��������λ���ϵ�װ�� 
	Equipment& getEquip(int index);


	//���ݻ�ȡ����
	int getMaxHealthPoint() const;
	int getMaxManaPoint() const;
	int getHealthPoint() const;
	int getManaPoint() const;
	int getAttackPoint() const;
	int getDefencePoint() const;
	string getName() const;

	//�������ú���
	void setHealthPoint(int value);
	void setManaPoint(int value);
	void setName(string const value);

	//��ֵ������������ͨ�����븺ֵ�Լ��٣�
	void appendHealthPoint(int value);
	void appendManaPoint(int value);
	void appendAttackPoint(int value);
	void appendDefencePoint(int value);
	//������ħ�����޽��������仯ʱ����ǰ������ħ��ֵ���ᰴ��������仯 
	void appendMaxHealthPoint(int value);
	void appendMaxManaPoint(int value);

private:
	//���Ӣ���Ƿ����� 
	bool deathCheck(Hero &lastAttacker);

	//��targetӢ������˺��������target������ֵ����damage��
	//���isPhysicsΪtrue,���˺������Է�defence���⣬��ʱʵ���˺�ֵΪmax(0,damage-defence)�� 
	int damageTo(Hero &target, int damage, bool isPhysics);


	//Ӣ������ 
	string name;
	//�������� 
	int maxHealthPoint;
	//ħ������ 
	int maxManaPoint;
	//��ǰ����ֵ 
	int healthPoint;
	//��ǰħ��ֵ 
	int manaPoint;
	//������ 
	int attackPoint;
	//������ 
	int defencePoint;
	//�Ƿ����� 
	bool deathFlag;
	//��Ʒ�� 
	Equipment *equipped[MAX_EQUIP_NUM];

};
#endif 
