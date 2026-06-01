#include "StartGameWidget.h"


StartGameWidget::StartGameWidget(QWidget *parent)
    : QMainWindow(parent)
{
    //初始化窗口基本信息
    this->move(InitialWidgetX, InitialWidgetY);
    this->resize(InitialWidgetWidth, InitialWidgetHeight);
    this->setWindowIcon(QIcon(InitialIcon));

    //基本按钮的设置
    this->startGameLabel = new mylabel(StartGameButtonWidth*this->width(), StartGameButtonHeight*this->height(), StartGameButtonPrePic, StartGameButtonRelPic, this);
    this->startGameLabel->move(this->width()*StartGameButtonX,this->height()*StartGameButtonY);
    this->startGameLabel->show();
    this->enterGameButton = new mypushbutton(EnterGameButtonPrePic, EnterGameButtonRelPic, this);
    this->enterGameButton->move(this->width() * EnterGameButtonX, this->height() * EnterGameButtonY);
    this->enterGameButton->show();

    //绑定事件
    connect(this->enterGameButton,&QPushButton::clicked, [=]() {
        this->startGameLabel->startAnimation(EnterGameButtonAnimationIntervals,EnterGameButtonAnimationSum);
        });
    this->gameSelectBackground = new GameSelectBackground();
    connect(this->startGameLabel, &mylabel::animationEnd, [=]() {
        this->gameSelectBackground->resize(this->width(), this->height());
        this->gameSelectBackground->move(this->x(), this->y());
        this->gameSelectBackground->show();
        this->hide();
        });
}

StartGameWidget::~StartGameWidget()
{
    delete this->gameSelectBackground;

}

//重写绘图事件
void StartGameWidget::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(InitialBackGroundPic);
    painter.drawPixmap(0,0,this->width(), this->height(), pix);
}
//重写伸缩事件
void StartGameWidget::resizeEvent(QResizeEvent* e) {
    
    this->updateLabelSize(StartGameButtonWidth, StartGameButtonHeight, StartGameButtonX, StartGameButtonY,this->startGameLabel);
    this->updateButtonSize(EnterGameButtonWidth, EnterGameButtonHeight, EnterGameButtonX, EnterGameButtonY, this->enterGameButton);
    return QMainWindow::resizeEvent(e);
}
void StartGameWidget::updateButtonSize(double width, double height, double x, double y,mypushbutton* btn) {
    btn->resize(this->width() * width, this->height() * height);
    btn->move(QPoint(this->width() * x, this->height() * y));
    btn->updateIconSize(this->width() * width, this->height() * height);
}
void StartGameWidget::updateLabelSize(double width, double height, double x, double y, mylabel* label) {
    label->resize(this->width() * width, this->height() * height);
    label->move(QPoint(this->width() * x, this->height() * y));
    label->updatePicSize(this->width(), this->height(), width, height);
    //label->updateIconSize(this->width() * width, this->height() * height);
}

