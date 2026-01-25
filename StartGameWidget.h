#pragma once

#include <QtWidgets/QMainWindow>
#include "const.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QVBoxLayout>
#include "mylabel.h"
#include <QPushButton>
#include "GameSelectBackground.h"
class StartGameWidget : public QMainWindow
{
    Q_OBJECT

public:
    StartGameWidget(QWidget *parent = nullptr);
    ~StartGameWidget();

private:
    //基本按钮，label成员
    mylabel* startGameLabel = nullptr;
    mypushbutton* enterGameButton=nullptr;
    //select game widget
    GameSelectBackground* gameSelectBackground = nullptr;
    void resizeEvent(QResizeEvent* e);
    void paintEvent(QPaintEvent* e);
    void updateButtonSize(double width, double height, double x, double y,mypushbutton* btn);
    void updateLabelSize(double width, double height, double x, double y, mylabel* label);
};

