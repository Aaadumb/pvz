#pragma once
#include "Zombie.h"
#include <vector>
#include "PlantCard.h"
#include "Plant.h"
#include "Bullet.h"
using namespace std;
class GameSystem
{
public:
	void zombieMovingSystem(vector<Zombie*>(&v)[6][10],bool &isGameOver);
	void plantReleaseSkillSystem(Plant* (&v)[6][10], vector<pair<int, int>>& generateCoin, vector<pair<int, pair<int, int>>>& generaterbullet, vector<Zombie*>(&vz)[6][10], 
		vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie);
	void updateCard(vector<PlantCard*>& v,int curCoin);
	void bulletMovingSystem(vector<Bullet*>& v,vector<int> &dieBullet);
	void bulletReleaseSkillSystem(vector<Zombie*>(&vz)[6][10],vector<Bullet*>& v, vector<int>& dieBullet, vector<pair<pair<int, int>, int>>& dieZombie);
	void zombieReleaseSkillSystem(vector<Zombie*>(&vz)[6][10], Plant* (&v)[6][10],vector<pair<int,int>>&diePlant);
};

