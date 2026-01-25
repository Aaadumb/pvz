#include "Shovel.h"

Shovel::Shovel(QWidget *parent)
	: QPushButton(parent)
{

	this->setFixedSize(70, 72);
	this->isPress = false;
}

Shovel::~Shovel()
{}

void Shovel::paintEvent(QPaintEvent* e) {
	QPainter painter(this);
	QPixmap pix(ShovelBankPic);
	painter.drawPixmap(0, 0, pix);
	if (!this->isPress||this->curGameCondition!=0) {
		pix.load(ShovelPic);
		pix = pix.scaled(this->width(), this->height());
		painter.drawPixmap(0, 0, pix);
	}
}
void Shovel::mousePressEvent(QMouseEvent* e) {
	this->isPress = true;
	return QPushButton::mousePressEvent(e);
}
void Shovel::mouseReleaseEvent(QMouseEvent* e) {
	this->isPress = false;
	return QPushButton::mouseReleaseEvent(e);
}
QString Shovel::getPic() {
	return ShovelPic;
}
QSize Shovel::getSize() {
	return QSize(70, 72);
}
void Shovel::updateCurGameCondition(int gameCondition) {
	this->curGameCondition = gameCondition;
}