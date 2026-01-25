#pragma once
#include "Bullet.h"
#include "const.h"
class Car :public Bullet
{
public:
	Car(int row, int col,int x,int y,QWidget* parent = nullptr);
	bool virtual bulletMove();
	bool virtual releaseSkill(vector<Zombie*>(&v)[6][10], vector<pair<pair<int, int>, int>>& dieZombie);
private:
	enum Condition{NORMAL,MOVING};
	Condition curCondition = NORMAL;
};

