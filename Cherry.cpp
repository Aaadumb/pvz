#include "Cherry.h"
Cherry::Cherry(int row, int col, QWidget* parent) {
	this->row = row;
	this->col = col;
	this->pic.resize(2);
	this->pic[NORMAL] = CherryNormalPic;
	this->pic[ISBOOM] = CherryBoomPic;
	QPixmap pix(CherryNormalPic);
	int w = pix.width(), h = pix.height();
	this->curPic = new QLabel(parent);
	this->curMovie = new QMovie(this->pic[NORMAL]);
	this->curPic->resize(w, h);
	this->curPic->setMovie(this->curMovie);
	this->curMovie->start();
	this->curPic->setAttribute(Qt::WA_TransparentForMouseEvents);

	this->heart = 1e9;
	this->attackPower = 250;
	this->cd = 460;
	this->dieTime = 500;
}
void Cherry::releaseSkill(vector<pair<int, int>>& generateCoin,
	vector<pair<int, pair<int, int>>>& generaterbullet, vector<Zombie*>(&v)[6][10],
	vector<pair<int, int>>& diePlant, vector<pair<pair<int, int>, int>>& dieZombie) {
	if (this->curCondition == NORMAL) {
		this->sumTime += gameTimeIntervals;
		if (this->sumTime >= this->cd) {
			//造成伤害，状态转变
			this->curCondition = ISBOOM;
			this->curMovie->stop();
			this->curMovie->setFileName(this->pic[ISBOOM]);
			QPixmap pix(this->pic[ISBOOM]);
			int w = pix.width(), h = pix.height();
			int x = this->curPic->x() + this->curPic->width() / 2 - w / 2, y = this->curPic->y() + this->curPic->height() / 2 - h / 2;
			this->curPic->resize(w, h);
			this->curPic->move(x, y);
			this->curPic->setMovie(this->curMovie);
			this->curMovie->start();
			this->sumTime = 0;
			this->heart = 0;

			int startRow = (this->row > 1) ? this->row - 1 : this->row;
			int endRow = (this->row < 5) ? this->row + 1 : this->row;
			int startCol = (this->col > 1) ? this->col - 1 : this->col;
			int endCol = (this->col < 9) ? this->col + 1 : this->col;
			for (int i = startRow; i <= endRow; i++) {
				for (int j = startCol; j <= endCol; j++) {
					if (v[i][j].empty())continue;
					auto& temp = v[i][j];
					for (int k = 0; k < temp.size(); k++) {
						if (temp[k] == nullptr || temp[k]->heart <= 0)continue;
						temp[k]->heart -= this->attackPower;
						if (temp[k]->heart <= 0) {
							dieZombie.push_back(make_pair(make_pair(i, j), k));
							temp[k]->dieReason = 2;
						}
					}
				}
			}
		}
	}
	else if (this->curCondition == ISBOOM) {
		sumTime += gameTimeIntervals;
		if (sumTime >= this->dieTime) {
			//执行消除逻辑
			diePlant.push_back(make_pair(this->row, this->col));
		}
	}
}
