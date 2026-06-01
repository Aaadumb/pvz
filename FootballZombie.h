#pragma once

#include "Zombie.h"
class FootballZombie :public Zombie
{
public:
	FootballZombie(int row, int y, QWidget* parent = nullptr);
	bool virtual zombieMoving(bool& isGameOver);
	void virtual zombieReleaseSkill(Plant* (&v)[6][10], vector<pair<int, int>>& diePlant);
private:
	enum Condition { NORMAL = 0, ATTACKING };
	Condition curCondition = NORMAL;

};

