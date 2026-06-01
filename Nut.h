#pragma once

#include "Plant.h"
#include "const.h"
class Nut :public Plant
{
public:
	Nut(int row,int col,QWidget*parent=nullptr);
	void virtual releaseSkill(vector<pair<int, int>>& generateCoin,
		vector<pair <int, pair <int, int>>>& generaterbullet, vector<Zombie*>(&v)[6][10],
		vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie);
private:
	enum Condition{NORMAL=0,HALFHEART,LITTERLHEART};
	Condition curContion=NORMAL;
	int sumHeart=0;
};

