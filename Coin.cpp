#include "Coin.h"
Coin::Coin(QWidget*parent) {
	
	this->movie = new QMovie(gameCoinPic);
	this->movie->start();
	this->btn = new QPushButton(parent);
	this->btn->setFixedSize(66, 66);
	this->btn->setIconSize(QSize(66, 66));
	this->btn->setStyleSheet("QPushButton{border:0px;background:transparent;}");
	this->btn->raise();
	connect(this->movie, &QMovie::frameChanged, [=]() {
		QPixmap pix = this->movie->currentPixmap();
		this->btn->setIcon(pix);
		this->btn->raise();
		});

	this->timer = new QTimer(this);
	timer->setInterval(CoinExistTime);
	connect(this->timer, &QTimer::timeout, [=]() {
		emit die();
		timer->stop();
		});
}
void Coin::startAnimation(int startx, int starty, int endx, int endy,int intervals) {
	if (this->animation) {
		this->animation->stop(); // 先停止动画
		delete this->animation;
		this->animation = nullptr;
	}
	animation=new QPropertyAnimation(this->btn,"geometry");
	animation->setDuration(intervals);
	animation->setStartValue(QRect(startx,starty,this->btn->width(),this->btn->height()));
	animation->setEndValue(QRect(endx, endy,this->btn->width(), this->btn->height()));
	//animation->setEasingCurve(QEasingCurve::OutBounce);
	animation->start();
	connect(animation, &QPropertyAnimation::finished, [=]() {
		emit this->animationEnd();
		});
}
Coin::~Coin() {
	delete this->btn;
	this->btn = nullptr;
	delete this->movie;
	this->movie = nullptr;
	delete this->timer;
	timer = nullptr;
}

