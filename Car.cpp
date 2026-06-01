#include "Car.h"

Car::Car(int row,int col,int x,int y, QWidget* parent) {
	this->row = row;
	this->col = 1;
	this->speed = 15;//
	

	QPixmap pix;
	pix.load(CarPic);
	this->curpic = new QLabel(parent);
	this->curpic->resize(pix.width(), pix.height());
	this->curpic->setPixmap(pix);
	this->x = x;
	this->y = y;
	this->curpic->move(x, y);
	this->attackPower = 999;
}
bool Car::bulletMove() {
	if (curCondition == NORMAL)return false;
	x += this->speed;
	int curCol = this->col;
	for (int i = this->col + 1; i <= 9; i++) {
		if (this->x >=this->gridCol[i]) {
			curCol = i;
		}
		else break;
	}
	this->col = curCol;
	this->curpic->move(this->x, this->y);
	this->curpic->raise();
	if (this->x >= 1103)return true;
	return false;
}
bool Car::releaseSkill(vector<Zombie*>(&v)[6][10], vector<pair<pair<int, int>, int>>& dieZombie) {
	if (this->curCondition == NORMAL) {
		if (!v[this->row][1].empty()) {
			auto& temp = v[this->row][1];
			for (int i = 0; i < temp.size(); i++) {
				if (this->x + this->curpic->width()-80 >= temp[i]->x) {
					this->curCondition = MOVING;
					break;
				}
			}
		}
	}
	if (this->curCondition == MOVING) {
		if (!v[this->row][this->col].empty()) {
			auto& temp = v[this->row][this->col];
			for (int i = 0; i < temp.size(); i++) {
				if (this->x + this->curpic->width()-80 >= temp[i]->x && this->x <= temp[i]->x + temp[i]->curPic->width()) {
					dieZombie.push_back(make_pair(make_pair(this->row, this->col), i));
				}
			}
		}
	}
	return false;
}
