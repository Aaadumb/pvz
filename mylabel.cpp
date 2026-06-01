#include "mylabel.h"


mylabel::mylabel(int width, int height, QString prePic, QString relPic, QMainWindow*parent)
	: QLabel(parent)
{
	QPixmap scalePix;
	scalePix.load(prePic);
	this->pressPic = scalePix.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	scalePix.load(relPic);
	this->releasePic = scalePix.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	this->setStyleSheet("QLabel{border:0px;background:transparent;}");
	this->setPixmap(this->releasePic);
	this->resize(width, height);
}

mylabel::~mylabel()
{}
void mylabel::startAnimation(int intervals,int sum) {
	int *cnt = new int(0);
	QTimer* timer = new QTimer(this);
	timer->setInterval(intervals);
	timer->start();
	connect(timer, &QTimer::timeout, [=]() {
		if ((*cnt) == sum) {
			timer->stop();
			delete cnt;
			emit animationEnd();
			return;
		}
		if ((*cnt) % 2 == 0) {
			this->setPixmap(this->pressPic);
		}
		else {
			this->setPixmap(this->releasePic);
		}
		(*cnt)++;
		});
}
void mylabel::updatePicSize(int Wwidth,int Wheight,double width,double height) {
	this->pressPic = this->pressPic.scaled(Wwidth*width,Wheight*height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	this->releasePic = this->releasePic.scaled(Wwidth * width, Wheight * height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	this->setPixmap(this->releasePic);
}

