#ifndef PLAYER_H
#define PLAYER_H

#define MAX_HERO_NUM 4
#define MAX_EQUIPMENT_NUM 12

#include "Hero.h"
#include "Equipment.h"

class Player {
public:
	//���캯�� 
	Player();


	//��ȡ���ӵ�еĽ�Ǯ 
	int getMoney() const;
	//Ϊ��Ǯ���һ������(����Ϊ����)  
	void appendMoney(const int delta);


	//��ȡ��ҵ�ǰӵ�е�Ӣ������ 
	int getHeroNum()const;
	//��ȡ��ҹ����Ӣ�ۣ��������±�Ϊ���� 
	Hero& getHero(const int index);
	//Ϊ������һ��Ӣ�ۣ������Ӣ�ۿ��Ա���ҹ����ɹ���Ӣ�����������޷����ʱ����false 
	bool addHero(const Hero &hero);
	//ʹ��������ɾ�������Ӣ�۵�
	bool removeHeroByIndex(const int index);


	//��ȡ��ҵ�ǰ���е�װ������ 
	int getEquipmentNum()const;
	//��ȡ��ҳ��е�װ�����������±�Ϊ���� 
	Equipment& getEquipment(const int index);
	//����ҳ���װ�����ɹ�����װ��ָ�룬����װ�����������޷����ʱ����NULL
	Equipment* addEquipment(Equipment &equipment);
	//ʹ�����������й���Ӣ�۵�ɾ�� 
	bool removeEquipmentByIndex(const int index);
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
