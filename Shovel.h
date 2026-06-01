#pragma once


#include <QPushButton>
#include <QPainter>
#include "const.h"
class Shovel  : public QPushButton
{
	Q_OBJECT

public:
	Shovel(QWidget *parent);
	~Shovel();
	//需要准备的事务：重写绘图时间，按压和释放事件
	void paintEvent(QPaintEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	QString getPic();
	QSize getSize();
	void updateCurGameCondition(int gameCondition);
private:
	bool isPress;
	int curGameCondition=0;
};

