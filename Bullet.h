#pragma once
#include <QLabel>
#include <vector>
#include <QString>
#include <QWidget>
#include <QObject>
#include "Zombie.h"
#include <QSound>
using namespace std;
class Bullet:public QObject
{
	Q_OBJECT
public:
	int row, col;
	double x, y;
	double attackPower,speed;
	QLabel* curpic=nullptr;
	bool virtual bulletMove() = 0;
	bool virtual releaseSkill(vector<Zombie*>(&v)[6][10],vector<pair<pair<int,int>,int>>&dieZombie)=0;
	int gridCol[10] = { 0,250,330,410,490,573,650,735,810,900 };
	~Bullet() {
		if (this->curpic != nullptr) {
			this->curpic->deleteLater();
			this->curpic = nullptr;
		}
	}
};

