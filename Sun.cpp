#include "Sun.h"
void Sun::releaseSkill(vector<pair<int, int>>&generateCoin, 
	vector<pair<int,pair<int, int>>>&generaterbullet, vector<Zombie*>(&v)[6][10],
	vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie) {
	if (this->heart <= 0)return;
	this->curSumTime += gameTimeIntervals;
	if (curSumTime >= this->cd) {
		//释放技能放出一朵向日葵
		generateCoin.push_back(make_pair(this->row, this->col));
		//技能时间清零
		curSumTime = 0;
	}
}
Sun::Sun(int row, int col, QWidget* parent) {
	this->cd = 10000;
	this->pic.resize(1);
	this->pic[NORMAL] = SunNormalPic;

	this->curPic = new QLabel(parent);
	this->curMovie = new QMovie(this->pic[NORMAL]);
	this->curPic->setMovie(this->curMovie);
	this->curMovie->start();
	this->row = row;
	this->col = col;
	this->curSumTime = 0;
	this->heart = 50;
	//this->curPic->resize();
}