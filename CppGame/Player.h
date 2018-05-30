#ifndef PLAYER_H
#define PLAYER_H

#define MAX_HERO_NUM 4
#define MAX_EQUIPMENT_NUM 20

#include "Hero.h"
#include "Equipment.h"

class Player {
public:
	//���캯�� 
	Player();

	//Ϊ������һ�����Բٿص�Ӣ�ۣ��ɲٿ�Ӣ��������ʱ������Ӳ�����false 
	bool addHero(const Hero &hero);
	//ʹ��������ɾ�������Ӣ�ۣ�����Ӣ�۲�������ҿɲٿ�Ӣ���򷵻�false
	bool removeHeroByIndex(const int index);

	//����ҳ���װ�����ɹ�����װ��ָ�룬����װ�����������޷����ʱ����NULL
	Equipment* addEquipment(Equipment &equipment);
	//ʹ��������������Ʒ��ɾ�� 
	bool removeEquipmentByIndex(const int index);


	//��ֵ������������ͨ�����븺ֵ�Լ��٣�
	void appendMoney(const int delta);

	//���ݻ�ȡ����
	int getMoney() const;
	int getHeroNum()const;
	int getEquipmentNum()const;
	//ͨ�������±�����ȡ����
	Hero& getHero(const int index);
	Equipment& getEquipment(const int index);

private:
	//��ҳ��еĽ�Ǯ 
	int money;

	//��ҹ����Ӣ�ۣ����Ե������ǵ�װ����������ǲ�ս 
	int heroNum;
	Hero heros[MAX_HERO_NUM];

	//��ҳ��е�װ�������汸�û�����ҹ����Ӣ��װ�������������  
	int equipmentNum;
	Equipment equipments[MAX_EQUIPMENT_NUM];
};
#endif
