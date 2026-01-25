#include "ConeZombie.h"
ConeZombie::ConeZombie(int row, int y, QWidget* parent) {
	this->curPic = new QLabel(parent);
	this->curPic->setAttribute(Qt::WA_TransparentForMouseEvents);
	this->moviePic.resize(2);
	this->moviePic[NORMAL] = ConeZombieWalkPic;
	this->moviePic[ATTACKING] = ConeZombieAttackingPic;
	this->curMovie = new QMovie(this->moviePic[NORMAL]);
	this->curPic->setMovie(this->curMovie);
	QPixmap pix(this->moviePic[NORMAL]);
	int w = pix.width(), h = pix.height();
	this->curPic->resize(w, h);
	this->curMovie->start();

	this->index = 2;
	this->heart = 150;
	this->row = row;
	this->col = 9;
	this->x = this->gridCol[9];
	this->y = y - this->curPic->height();
	this->walkSpeed = 0.30;
	this->attackDistance = 5;
	this->sumAttackTime = 0;
	this->attackIntervals = 1000;
	this->attackPower = 20;

}
bool ConeZombie::zombieMoving(bool& isGameOver) {
	if (this->heart <= 0)return false;
	if (this->curCondition == ATTACKING)return false;
	this->x -= this->walkSpeed;
	this->curPic->move(this->x, this->y);
	if (this->x <= this->gridCol[1] - this->curPic->width()) {
		isGameOver = true;
		return false;
	}
	int curCol = this->col;
	for (int i = this->col - 1; i >= 1; i--) {
		if (this->x <= this->gridCol[i]) {
			curCol = i;
			break;
		}
	}
	if (this->col != curCol) {
		this->col = curCol;
		return true;
	}
	return false;
}
void ConeZombie::zombieReleaseSkill(Plant* (&v)[6][10], vector<pair<int, int>>& diePlant) {
	if (this->heart <= 0)return;
	this->curPic->raise();
	//状态比较少，直接在这里更新状态
	if (this->curCondition == NORMAL) {
		if (v[this->row][this->col] != nullptr && v[this->row][this->col]->heart > 0) {
			this->curCondition = ATTACKING;
			this->sumAttackTime = 0;
			this->curTargetRow = this->row;
			this->curTargetCol = this->col;
		}
		else if (this->col != 1 && this->x - this->attackDistance <= this->gridCol[this->col - 1] && v[this->row][this->col - 1] != nullptr && v[this->row][this->col - 1]->heart > 0) {
			this->curCondition = ATTACKING;
			this->sumAttackTime = 0;
			this->curTargetRow = this->row;
			this->curTargetCol = this->col - 1;
		}
		if (this->curCondition == ATTACKING) {
			this->curMovie->stop();
			this->curMovie->setFileName(this->moviePic[ATTACKING]);
			this->curPic->setMovie(this->curMovie);
			this->curMovie->start();
		}
		return;
	}
	this->sumAttackTime += gameTimeIntervals;
	if (v[this->curTargetRow][this->curTargetCol] != nullptr && v[this->curTargetRow][this->curTargetCol]->heart > 0) {
		if (this->sumAttackTime >= this->attackIntervals) {
			//造成伤害
			v[this->curTargetRow][this->curTargetCol]->heart -= this->attackPower;
			if (v[this->curTargetRow][this->curTargetCol]->heart <= 0) {
				//执行消除逻辑
				diePlant.push_back(make_pair(this->curTargetRow, this->curTargetCol));
				//将当前的状态重置为NORMAL
				this->curCondition = NORMAL;
			}
			this->sumAttackTime = 0;
		}
	}
	else this->curCondition = NORMAL;
	if (this->curCondition == NORMAL) {
		this->curMovie->stop();
		this->curMovie->setFileName(this->moviePic[NORMAL]);
		this->curPic->setMovie(this->curMovie);
		this->curMovie->start();
		this->sumAttackTime = 0;
	}

}