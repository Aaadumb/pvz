#pragma once

#include <QPushButton>
#include <QtWidgets/QMainWindow>
class mypushbutton  : public QPushButton
{
	Q_OBJECT

public:
	mypushbutton(QString prePic, QString relPic,QMainWindow *parent=nullptr);
	~mypushbutton();
	void updateIconSize(int x, int y);
private:
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);

	QPixmap pressPic,releasePic;
};

