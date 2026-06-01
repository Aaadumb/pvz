#include "PlantCard.h"


PlantCard::PlantCard(QString plant,int cd,int coinNeeded,QWidget *parent)
	: QPushButton(parent)
{
	this->plantPic = plant;
	this->Card = CardPic;
	QPixmap temp;
	temp.load(this->Card);
	this->resize(temp.size()*0.5);
	this->cd = cd;
	this->curSumTime = 0;
	this->coinNeeded = coinNeeded;
}

PlantCard::~PlantCard()
{}
void PlantCard::paintEvent(QPaintEvent* e) {
	QPainter painter(this);
	QPixmap pix;
	pix.load(CardPic);
	pix = pix.scaled(this->width() , this->height() );
	painter.drawPixmap(0, 0, pix);
	pix.load(this->plantPic);
	//pix = pix.scaled(this->width() * 0.5, this->height() * 0.5);
	pix = pix.scaled(pix.width() * 0.45, this->height() * 0.45);
	painter.drawPixmap(10, 15, pix);
	painter.setPen(QColor(0,0,0));
	QFont font("Arial");
	font.setPointSize(12);
	painter.setFont(QFont("Arial", 8));
	painter.drawText(this->width()*0.35,this->height()-4,QString("%1").arg(this->coinNeeded)); // 阳光数值
	if (this->isPress&& cdIsOk && this->curCoin >= coinNeeded) {
			if (this->curGameCondition != 0)return;
			painter.fillRect(rect(), QColor(0, 0, 0, 0.8 * 255));
	}
	else{
		if (this->cdIsOk && this->curCoin < coinNeeded) {
			painter.fillRect(rect(), QColor(0, 0, 0, 0.5 * 255));
		}
		else if (!this->cdIsOk) {
			double rate =1.0- (double)this->curSumTime / this->cd;
			painter.fillRect(rect(), QColor(0, 0, 0, 0.5 * 255));
			painter.fillRect(QRect(0,0,this->width(),this->height()*rate), QColor(0, 0, 0, 0.5 * 255));
		}
	}
}
void PlantCard::updateCanPlant() {
	if (this->curCoin >= coinNeeded && this->cdIsOk) {
		this->everythingOk = true;
	}
}
void PlantCard::updateCd() {
	if (this->cdIsOk)return;
	this->curSumTime += gameTimeIntervals;
	if (curSumTime >= cd) {
		this->cdIsOk = true;
		curSumTime = 0;
	}
}
void PlantCard::updateCoin(int coin) {
	this->curCoin = coin;
}
void PlantCard::mousePressEvent(QMouseEvent* e) {
	this->isPress = true;
	return QPushButton::mousePressEvent(e);
}
void PlantCard::mouseReleaseEvent(QMouseEvent* e) {
	this->isPress = false;
	return QPushButton::mouseReleaseEvent(e);
}
bool PlantCard::isOk() {
	return everythingOk;
}
void PlantCard::updateCondition() {
	this->cdIsOk = false;
	this->everythingOk = false;
}
QString PlantCard::getPlantPic() {
	return this->plantPic;
}
int PlantCard::getCost() {
	return this->coinNeeded;
}
void PlantCard::updateGameCondition(int gameCondition) {
	this->curGameCondition = gameCondition;
}
