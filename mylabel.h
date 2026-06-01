#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
class mylabel  : public QLabel
{
	Q_OBJECT

public:
	mylabel(int width, int height, QString prePic, QString relPic, QMainWindow *parent=nullptr);
	~mylabel();
	void startAnimation(int intervals,int sum);
	void updatePicSize(int Wwidth, int Wheight, double width, double height);
private:
	QPixmap pressPic, releasePic;
	
signals:
	void animationEnd();
};

