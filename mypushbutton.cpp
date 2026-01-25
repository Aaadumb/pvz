#include "mypushbutton.h"

mypushbutton::mypushbutton(QString prePic, QString relPic,QMainWindow*parent)
	: QPushButton(parent)
{

	QPixmap scalePix;
	scalePix.load(prePic);
	this->pressPic = scalePix;
	scalePix.load(relPic);
	this->releasePic = scalePix;
	this->setStyleSheet("QPushButton{border:0px;background:transparent;}");
	this->setIcon(this->releasePic);
	this->setIconSize(this->releasePic.size());
	this->resize(scalePix.size());


}

mypushbutton::~mypushbutton()
{}

//重写鼠标按压和释放的事件
void mypushbutton::mousePressEvent(QMouseEvent* e) {
	this->setIcon(this->pressPic);
	return QPushButton::mousePressEvent(e);
}
void mypushbutton::mouseReleaseEvent(QMouseEvent* e) {
	this->setIcon(this->releasePic);
	return QPushButton::mouseReleaseEvent(e);
}
//
void mypushbutton::updateIconSize(int width, int height) {
	this->pressPic=this->pressPic.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	this->releasePic=this->releasePic.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	this->setIcon(this->releasePic);
	this->setIconSize(this->releasePic.size());
}


