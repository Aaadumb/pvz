#pragma once

#include <QWidget>
#include <QPainter>
#include "const.h"
#include "QPushButton"
#include "GameBackground.h"
#include <QSound>
class GameSelectBackground  : public QWidget
{
	Q_OBJECT

public:
	GameSelectBackground(QWidget *parent=nullptr);
	~GameSelectBackground();

private:
	void paintEvent(QPaintEvent* e);
	QPushButton* daygame, *nightgame;
	void resizeEvent(QResizeEvent* e);
	GameBackground* game=nullptr;
	QSound* sound = nullptr;
};

