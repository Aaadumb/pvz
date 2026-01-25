#pragma once
class Plant;
#include "Plant.h"
#include <vector>
#include <QString>
#include <QLabel>
#include <QMovie>
#include <utility>
#include <QObject>
#include "const.h"
#include <QWidget>
#include <QSound>
using namespace std;
class Zombie:public QObject
{
	Q_OBJECT;
public:
	int index;
	int  row, col, heart;
	int attackIntervals,attackDistance,sumAttackTime,attackPower;
	double walkSpeed,x,y;
	int curTargetRow, curTargetCol;
	int dieReason = 1;
	int gridCol[10] = { 0,250,330,410,490,573,650,735,810,900 };
	vector<QString> moviePic;
	QLabel* curPic = nullptr;
	QMovie* curMovie=nullptr;
	bool virtual zombieMoving(bool &isGameOver)=0;
	void virtual zombieReleaseSkill(Plant* (&v)[6][10],vector<pair<int,int>> &diePlant) = 0;
	~Zombie() {
		if (this->curMovie != nullptr) {
			this->curMovie->stop();
			this->curMovie->deleteLater();
			this->curMovie = nullptr;
		}
		if (this->curPic != nullptr) {
			this->curPic->deleteLater();
			this->curPic = nullptr;
		}
	}
};
	

