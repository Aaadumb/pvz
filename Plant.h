#pragma once

class Zombie;
#include <QLabel>
#include <vector>
#include <QString>
#include <QMovie>
#include <QWidget>
#include <QObject>
#include <utility>
#include "const.h"
#include "Zombie.h"
using namespace std;
class Plant:public QObject
{
	Q_OBJECT;
public:
	int row, col, heart;
	vector<QString> pic;
	QLabel* curPic=nullptr;
	QMovie* curMovie=nullptr;
	void virtual releaseSkill(vector<pair<int,int>> &generateCoin,
		vector<pair<int,pair<int,int>>>&generaterbullet,vector<Zombie*>(&v)[6][10],vector<pair<int,int>> &diePlant,vector<pair<pair<int,int>,int>>&dieZombie)=0;
	~Plant(){
		if (this->curMovie != nullptr) {
			this->curMovie->stop();
			delete this->curMovie;
			this->curMovie = nullptr;
		}
		if (curPic != nullptr) {
			this->curPic->close();
			this->curPic->setParent(nullptr);
			delete this->curPic;
			this->curPic = nullptr;
		}
	};
};

