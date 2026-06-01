#include "GameSelectBackground.h"

#include <QPixmap>
#include <QSound>
GameSelectBackground::GameSelectBackground(QWidget *parent)
	: QWidget(parent)
{

	this->setWindowIcon(QIcon(InitialIcon));
	this->daygame = new QPushButton(this);
	daygame->show();
	this->nightgame = new QPushButton(this);
	nightgame->show();

	//设置绑定事件
	sound = new QSound(":/sound/Grazy.wav");
	sound->setLoops(-1);
	
	connect(this->daygame, &QPushButton::clicked, [=]() {
		this->game = new GameBackground(DayGamePic);
		game->resize(1103,600);
		game->move(this->x(), this->y());
		game->show();
		sound->play();
		this->hide();
		});
	connect(this->nightgame, &QPushButton::clicked, [=]() {
		this->game = new GameBackground(NightGamePic);
		game->setFixedSize(1103, 600);
		game->move(this->x(), this->y());
		game->show();
		sound->play();
		this->hide();
		});
}

GameSelectBackground::~GameSelectBackground()
{
	this->sound->deleteLater();
}
void GameSelectBackground::paintEvent(QPaintEvent* e) {
	QPainter painter(this);
	QPixmap pix;
	pix.load(GameSelectBackgroundPic);
	pix = pix.scaled(this->width(), this->height());
	painter.drawPixmap(0,0,pix);
}
void GameSelectBackground::resizeEvent(QResizeEvent* e) {
	daygame->resize(this->width() * DayGameButtonWidth, this->height() * DayGameButtonHeight);
	daygame->move(this->width() * DayGameButtonX, this->height() * DayGameButtonY);
	daygame->setIcon(QPixmap(DayGamePic).scaled(daygame->width(), daygame->height()));
	daygame->setIconSize(QSize(daygame->width(), daygame->height()));
	nightgame->resize(this->width() * NightGameButtonWidth, this->height() * NightGameButtonHeight);
	nightgame->move(this->width() * NightGameButtonX, this->height() * NightGameButtonY);
	nightgame->setIcon(QPixmap(NightGamePic).scaled(nightgame->width(), nightgame->height()));
	nightgame->setIconSize(QSize(this->width(), this->height()));
	return QWidget::resizeEvent(e);
}

