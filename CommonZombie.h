#pragma once

#include "Zombie.h"
#include <QWidget>
#include "const.h"
#include <QLabel>
#include <cmath>
class CommonZombie:public Zombie
{
public:
	CommonZombie(int row,int y,QWidget *parent=nullptr);
	bool virtual zombieMoving(bool &isGameOver);
	void virtual zombieReleaseSkill(Plant* (&v)[6][10], vector<pair<int, int>>& diePlant);
private:
	enum Codition { NORMAL = 0, ATTACKING,DINGY };
	Codition curCondition = NORMAL;
};

