#pragma once

#include <QPushButton>
#include <QPainter>
#include <QString>
#include "const.h"
class PlantCard  : public QPushButton
{
	Q_OBJECT
public:
	PlantCard(QString plantPic,int cd,int coinNeeded,QWidget *parent=nullptr);
	~PlantCard();
	void updateCanPlant();
	void updateCd();
	void updateCoin(int coin);
	void updateGameCondition(int gameCondition);
	bool isOk();
	void updateCondition();
	QString getPlantPic();
	int getCost();
private:
	QString plantPic,Card;
	void paintEvent(QPaintEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	bool isPress = false;
	bool cdIsOk = false;
	bool everythingOk = false;
	int cd,curSumTime,coinNeeded,curCoin=0;
	int curGameCondition=0;
};

