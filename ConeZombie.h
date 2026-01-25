#pragma once
#include "Zombie.h"
class ConeZombie :  public Zombie
{
public:
	ConeZombie(int row, int y, QWidget* parent = nullptr);
	bool virtual zombieMoving(bool& isGameOver);
	void virtual zombieReleaseSkill(Plant* (&v)[6][10], vector<pair<int, int>>& diePlant);
private:
	enum Condition{NORMAL=0,ATTACKING};
	Condition curCondition = NORMAL;
};

