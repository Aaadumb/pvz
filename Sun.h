#pragma once
#include "Plant.h"
#include "const.h"
#include <QWidget>
#include "Coin.h"
#include <utility>
class Sun : public Plant
{
	Q_OBJECT;
public:
	Sun(int row,int col,QWidget* parent=nullptr);
	void virtual releaseSkill(vector<pair<int, int>>&generateCoin,
		vector<pair<int, pair<int, int>>>&generaterbullet, vector<Zombie*>(&v)[6][10],
		vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie);
private:
	int cd,curSumTime;
	enum Condition{NORMAL=0};
	Condition curCodition=NORMAL;
};

