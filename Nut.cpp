#include "Nut.h"

Nut::Nut(int row, int col, QWidget* parent) {
	this->row = row;
	this->col = col;
	this->pic.resize(3);
	pic[NORMAL] = NutNormalPic;
	pic[HALFHEART] = NutHalfHeartPic;
	pic[LITTERLHEART] = NutLitterHeartPic;
	this->curMovie = new QMovie(this->pic[this->curContion]);
	this->curPic = new QLabel(parent);
	this->curPic->setMovie(this->curMovie);
	this->curMovie->start();
	this->heart = 300;
	this->sumHeart = 300;
}
void Nut::releaseSkill(vector<pair<int, int>>& generateCoin, 
	vector<pair <int, pair <int, int>>>& generaterbullet, vector<Zombie*>(&v)[6][10], 
	vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie) {
	if (this->heart <= 0)return;
	Condition curC = NORMAL;
	if (this->heart >= this->sumHeart * 0.5 && this->heart <= this->sumHeart)curC = NORMAL;
	else if (this->heart >= this->sumHeart * 0.33 && this->heart < this->sumHeart * 0.5)curC = HALFHEART;
	else if (this->heart > 0 && this->heart < this->sumHeart * 0.33)curC = LITTERLHEART;
	if (this->curContion != curC) {
		this->curMovie->stop();
		this->curMovie->setFileName(this->pic[curC]);
		this->curPic->setMovie(this->curMovie);
		this->curMovie->start();
		this->curContion = curC;
	}
}
