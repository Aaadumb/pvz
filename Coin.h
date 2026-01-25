#pragma once
#include "const.h"
#include <QLabel>
#include <QMovie>
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QTimer>
#include <QPropertyAnimation>

class Coin:public QObject
{
	Q_OBJECT;
public:
	Coin(QWidget* parent = nullptr);
	~Coin();
	void startAnimation(int startx,int starty,int endx,int endy,int intervals);
	bool updateCondition();
	QPushButton* btn=nullptr;
	QMovie* movie = nullptr;
	QPropertyAnimation* animation = nullptr;
	QTimer *timer = nullptr;
	
signals:
	void animationEnd();
	void die();
};
/*

*/

