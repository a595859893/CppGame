#ifndef _EQUIPMENT
#define _EQUIPMENT

#include <iostream>
using namespace std;

class Equipment {
public:
	//���캯��������һ����Ʒ������name���֣�atc�������ӳɣ�def�������ӳɣ�maxHp�������޼ӳɣ�maxMpħ�����޼ӳ� 
	explicit Equipment(string name = "��̫", int atk = 0, int def = 0, int maxHp = 0, int maxMp = 0);

	//��ȡ��Ʒ�������ӳ� 
	int getAttackAppend();
	//��ȡ��Ʒ�������ӳ� 
	int getDefenceAppend();
	//��ȡ��Ʒ�������޼ӳ� 
	int getMaxHealthPointAppend();
	//��ȡ��Ʒħ�����޼ӳ� 
	int getMaxManaPointAppend();
	//��ȡ��Ʒ���� 
	string getName();

	//�����Ʒ�����ı� 
	void print();

private:
	//��Ʒ���� 
	string name;
	//�������ӳ� 
	int attackAppend;
	//�������ӳ� 
	int defenceAppend;
	//�������޼ӳ� 
	int maxHealthPointAppend;
	//ħ�����޼ӳ� 
	int maxManaPointAppend;
};

#endif
