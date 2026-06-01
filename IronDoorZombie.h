#pragma once

#include "Zombie.h"
class IronDoorZombie : public Zombie
{
public:
	IronDoorZombie(int row, int y, QWidget* parent = nullptr);
	bool virtual zombieMoving(bool& isGameOver);
	void virtual zombieReleaseSkill(Plant* (&v)[6][10], vector<pair<int, int>>& diePlant);
private:
	enum Condition { NORMAL, ATTACKING };
	Condition curCondition = NORMAL;
};

