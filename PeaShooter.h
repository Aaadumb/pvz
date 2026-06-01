#pragma once

#include "Plant.h"
#include "const.h"
#include <utility>
class PeaShooter : public Plant
{
public:
	PeaShooter(int row, int col,QWidget*parent);
	void virtual releaseSkill(vector<pair<int, int>>& generateCoin,
		vector<pair<int,pair<int, int>>>& generaterbullet, vector<Zombie*>(&v)[6][10],
		vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie);
private:
	int cd,curSumTime;
	enum Codition{NORMAL=0,ATTACKING};
	Codition curCondition = NORMAL;
};

