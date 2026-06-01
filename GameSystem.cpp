#include "GameSystem.h"

void GameSystem::zombieMovingSystem(vector<Zombie*>(&v)[6][10],bool& isGameOver) {
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 9; j++) {
			if (!v[i][j].empty()) {
				vector<int> index;
				for (int k = 0; k < v[i][j].size(); k++) {
					if (v[i][j][k] == nullptr)continue;
					bool flag=v[i][j][k]->zombieMoving(isGameOver);
					if (flag)index.push_back(k);
				}
				if (!index.empty()) {
					for (int k = index.size() - 1; k >= 0; k--) {
						Zombie* temp = v[i][j][index[k]];
						v[i][j - 1].push_back(temp);
						v[i][j].erase(v[i][j].begin()+index[k]);
					}
				}
			}
		}
	}
}
void GameSystem::updateCard(vector<PlantCard*>& v, int curCoin) {
	for (auto it : v) {
		it->updateCd();
		it->updateCoin(curCoin);
		it->update();
		it->updateCanPlant();
	}
}
void GameSystem::plantReleaseSkillSystem(Plant* (&v)[6][10], vector<pair<int, int>>& generateCoin,
	vector<pair<int, pair<int, int>>>& generaterbullet, vector<Zombie*>(&vz)[6][10], 
	vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie) {
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 9; j++) {
			if (v[i][j] != nullptr) {
				v[i][j]->releaseSkill(generateCoin,generaterbullet,vz,diePlant,dieZombie);
			}
		}
	}
}
void GameSystem::bulletMovingSystem(vector<Bullet*>& v,vector<int>&dieBullet) {
	for (int i = 0; i < v.size(); i++) {
		bool flag=v[i]->bulletMove();
		if (flag) {
			dieBullet.push_back(i);
		}
	}
}
void GameSystem::bulletReleaseSkillSystem(vector<Zombie*>(&vz)[6][10],vector<Bullet*>& v, vector<int>& dieBullet, vector<pair<pair<int, int>, int>>& dieZombie) {
	for (int i = 0; i < v.size(); i++) {
		bool flag=v[i]->releaseSkill(vz,dieZombie);
		if (flag) {
			dieBullet.push_back(i);
		}
	}
}
void GameSystem::zombieReleaseSkillSystem(vector<Zombie*>(&vz)[6][10], Plant* (&v)[6][10],vector<pair<int,int>>&diePlant) {
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 9; j++) {
			if (!vz[i][j].empty()) {
				for (int k = 0; k < vz[i][j].size(); k++) {
					vz[i][j][k]->zombieReleaseSkill(v,diePlant);
				}
			}
		}
	}
}
