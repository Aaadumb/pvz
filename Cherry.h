#pragma once
#include "Plant.h"
class Cherry : public Plant
{
public:
	Cherry(int row, int col, QWidget* parent = nullptr);
	void virtual releaseSkill(vector<pair<int, int>>& generateCoin,
		vector<pair<int, pair<int, int>>>& generaterbullet, vector<Zombie*>(&v)[6][10], 
		vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie);
private:
	enum Condition{NORMAL=0,ISBOOM};
	Condition curCondition = NORMAL;
	int cd, sumTime = 0,dieTime,attackPower;
	int gridCol[10] = { 0,250,330,410,490,573,650,735,810,900 };
};

