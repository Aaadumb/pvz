#include "Potato.h"
Potato::Potato(int row, int col, QWidget* parent) {
	this->row = row;
	this->col = col;
	this->curPic = new QLabel(parent);
	this->pic.resize(3);
	pic[NORMAL] = PotatoNormalPic;
	pic[ISACTIVE] = PotatoIsActivePic;
	pic[ISBOOM] = PotatoBoomPic;
	QPixmap pix(pic[NORMAL]);
	this->curPic->resize(pix.width(), pix.height());
	this->curMovie = new QMovie(this->pic[NORMAL]);
	this->curPic->setMovie(this->curMovie);
	this->curMovie->start();
	this->heart = 180;
	this->attackPower = 250;
	this->cd = 12000;
	this->dieTime = 500;
}
void Potato::releaseSkill(vector<pair<int,int>>& generateCoin,
	vector<pair <int,pair<int,int>>>& generaterbullet, vector<Zombie*>(&v)[6][10],
	vector<pair<int,int>>& diePlant, vector<pair<pair<int,int>,int>>& dieZombie) {
	if (this->heart <= 0&&this->isCanEat)return;
	if (this->curCondition == NORMAL) {
		this->sumTime += gameTimeIntervals;
		if (this->sumTime >= this->cd) {
			this->curCondition = ISACTIVE;
			this->curMovie->stop();
			this->curMovie->setFileName(this->pic[ISACTIVE]);
			this->curPic->setMovie(this->curMovie);
			this->curMovie->start();
			this->sumTime = 0;
		}
	}
	else if (this->curCondition == ISACTIVE) {
		if (!v[this->row][this->col].empty()) {
			this->curCondition = ISBOOM;
		}
		else if (this->col != 9 && !v[this->row][this->col + 1].empty()) {
			auto& temp = v[this->row][this->col + 1];
			for (int i = 0; i < temp.size(); i++) {
				int len = temp[i]->x - temp[i]->attackDistance;
				if (len<=this->gridCol[this->col]) {
					this->curCondition = ISBOOM;
					break;
				}
			}
		}
		if (this->curCondition == ISBOOM) {
			QPixmap pix(this->pic[ISBOOM]);
			int w = pix.width(), h = pix.height();
			int x = this->curPic->x() + this->curPic->width() / 2 - w / 2,y=this->curPic->y()+this->curPic->height()/2-h/2;
			this->curMovie->stop();
			this->curMovie->setFileName(this->pic[ISBOOM]);
			this->curPic->setMovie(this->curMovie);
			this->curPic->resize(w, h);
			this->curPic->move(x, y);
			this->curMovie->start();
			this->isCanEat = false;
			this->heart = 0;
			//造成伤害
			int startCol = (this->col>1)?this->col-1:this->col;
			int endCol = (this->col < 9) ? this->col + 1 : this->col;
			for (int i = startCol; i <= endCol; i++) {
				if (v[this->row][i].empty())continue;
				auto& temp = v[this->row][i];
				for (int k = 0; k < temp.size(); k++) {
					if (temp[k] == nullptr || temp[k]->heart <= 0)continue;
					temp[k]->heart -= this->attackPower;
					if (temp[k]->heart <= 0) {
						dieZombie.push_back(make_pair(make_pair(this->row, i), k));
					}
				}
			}
		}
	}
	else if (this->curCondition == ISBOOM) {
		sumTime += gameTimeIntervals;
		if (sumTime >= this->dieTime) {
			//将土豆地雷删掉
			diePlant.push_back(make_pair(this->row, this->col));
		}
	}
}