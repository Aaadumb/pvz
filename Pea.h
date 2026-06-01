#pragma once

#include "Bullet.h"
#include "const.h"
#include <algorithm>
#include <cmath>
#include <QSound>
class Pea : public Bullet
{
public:
	Pea(int row, int col, int x, int y, QWidget* parent);
	bool virtual bulletMove();
	bool virtual releaseSkill(vector<Zombie*>(&v)[6][10], vector<pair<pair<int, int>, int>>& dieZombie);
	~Pea();
private:
	
};

