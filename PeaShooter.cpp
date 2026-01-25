#include "PeaShooter.h"
PeaShooter::PeaShooter(int row, int col, QWidget* parent) {
	this->row = row;
	this->col = col;
	this->cd = 2000;
	this->curPic = new QLabel(parent);
	this->pic.resize(1);
	this->curMovie = new QMovie(PeaShooterNormalPic);
	this->curPic->setMovie(this->curMovie);
	this->curMovie->start();
	this->curSumTime = 0;
	this->heart = 180;
}
void PeaShooter::releaseSkill(vector<pair<int, int>>& generateCoin,
	vector<pair<int, pair<int, int>>> &generaterbullet, vector<Zombie*>(&v)[6][10], 
	vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie) {
	bool flag = true;
	for (int i = this->col; i <= 9; i++) {
		if (!v[this->row][i].empty()) {
			this->curCondition = ATTACKING;
			flag = false;
			break;
		}
	}
	if (flag) {
		this->curCondition = NORMAL;
		this->curSumTime = 0;
	}
	if (this->curCondition == NORMAL)return;
	this->curSumTime += gameTimeIntervals;
	if (curSumTime >= this->cd) {
		//发射子弹
		generaterbullet.push_back(make_pair(1, make_pair(this->row, this->col)));
		//清空弹夹
		this->curSumTime = 0;
	}
}
