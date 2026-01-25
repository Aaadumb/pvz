#include "RepeatShooter.h"
RepeatShooter::RepeatShooter(int row, int col, QWidget* parent) {
	this->row = row;
	this->col = col;
	this->pic.resize(1);
	pic[NORMAL] = RepeatShooterNormalPic;
	QPixmap pix(this->pic[NORMAL]);
	int w = pix.width(), h = pix.height();
	this->curPic = new QLabel(parent);
	this->curPic->resize(w, h);
	this->curMovie = new QMovie(this->pic[NORMAL]);
	this->curPic->setMovie(this->curMovie);
	this->curMovie->start();

	this->heart = 200;
	this->attackIntervals = 2000;
	this->shootIntervals = 100;

}
void RepeatShooter::releaseSkill(vector<pair<int, int>>& generateCoin,
	vector<pair<int, pair<int, int>>>& generaterbullet, vector<Zombie*>(&v)[6][10],
	vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie) {
	bool flag = true;
	for (int i = this->col; i <= 9; i++) {
		if (!v[this->row][i].empty()) {
			flag = false;
			break;
		}
	}
	if (this->curCondition == NORMAL&&flag==false) {
		this->curCondition = ATTACKINGFIRST;
		this->sumTime = 0;
	}
	else if (this->curCondition == ATTACKINGFIRST) {
		if (flag) {
			this->curCondition = NORMAL;
			this->sumTime = 0;
		}
		else {
			sumTime += gameTimeIntervals;
			if (sumTime >= this->attackIntervals) {
				generaterbullet.push_back(make_pair(1, make_pair(this->row, this->col)));
				this->sumTime = 0;
				this->curCondition = ATTACKINGSECOND;
			}
		}
	}
	else if (this->curCondition == ATTACKINGSECOND) {
		sumTime += gameTimeIntervals;
		if (sumTime >= this->shootIntervals) {
			generaterbullet.push_back(make_pair(1, make_pair(this->row, this->col)));
			if (flag) this->curCondition = NORMAL;
			else this->curCondition = ATTACKINGFIRST;
			this->sumTime = 0;
		}
	}
}