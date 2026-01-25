#include "Pea.h"
Pea::Pea(int row, int col, int x, int y, QWidget* parent) {
	this->row = row;
	this->col = col;
	this->x = x;
	this->y = y;

	this->curpic = new QLabel(parent);
	this->curpic->setPixmap(QPixmap(PeaPic));
	this->curpic->move(x, y);

	this->attackPower = 10.0;
	this->speed = 10;
	
}
bool Pea::bulletMove() {
	this->x += this->speed;
	this->curpic->move(this->x, this->y);
	int curCol = this->col;
	for (int i = this->col + 1; i <= 9; i++) {
		if (this->x >= this->gridCol[i]) {
			curCol = i;
		}
		else break;
	}
	if (this->x>=1103) {
		//消除逻辑
		return true;
	}
	else this->col = curCol;
	this->curpic->raise();
	return false;
}
bool Pea::releaseSkill(vector<Zombie*>(&v)[6][10], vector<pair<pair<int, int>, int>>& dieZombie) {
	if (v[this->row][this->col].empty())return false;
	Zombie* target = nullptr;
	int pos = -1,curDistance=1e9;
	auto& temp = v[this->row][this->col];
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] != nullptr && temp[i]->heart > 0 && temp[i]->x +80<= this->x + this->curpic->width() && temp[i]->x + temp[i]->curPic->width() >= this->x) {
			if (abs(temp[i]->x-this->x)<curDistance) {
				target = temp[i];
				pos = i;
				curDistance = abs(temp[i]->x - this->x);
			}
		}
	}
	if (target == nullptr) {
		return false;
	}
	target->heart -= this->attackPower;
	if (target->heart <= 0) {
		//执行消除逻辑
		dieZombie.push_back(make_pair(make_pair(target->row, target->col), pos));
	}
	return true;
}
Pea::~Pea() {
	delete this->curpic;
	this->curpic = nullptr;
}
