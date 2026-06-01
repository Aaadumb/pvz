#pragma once


#include <QWidget>
#include <QPainter>
#include "const.h"
#include "Zombie.h"
#include "CommonZombie.h"
#include <vector>
#include <QTimer>
#include "GameSystem.h"
#include "Plant.h"
#include "Sun.h"
#include "Coin.h"
#include "PlantCard.h"
#include <ctime>
#include <cstdlib>
#include "PeaShooter.h"
#include "Bullet.h"
#include "Pea.h"
#include <QMovie>
#include "Shovel.h"
#include <QPushButton>
#include "Car.h"
#include "Nut.h"
#include "Potato.h"
#include "Cherry.h"
#include "ConeZombie.h"
#include "FootballZombie.h"
#include "RepeatShooter.h"
#include "IronHubZombie.h"
#include "IronDoorZombie.h"
#include <QSound>
using namespace std;
class GameBackground : public QWidget
{
	Q_OBJECT

public:
	GameBackground(QString pic, QWidget* parent = nullptr);
	~GameBackground();
private:
	QString pic;							//Widget
	void resizeEvent(QResizeEvent* e);
	void paintEvent(QPaintEvent* e);


	
	vector<Zombie*> zombieVecotr[6][10];	//vector
	Plant* plantVector[6][10] = {nullptr};
	vector<PlantCard*> cardVector;
	vector<Bullet*> bulletVector;
	int curCoin = 0;
	QLabel* coinNum = nullptr;
	Shovel* shovel = nullptr;

	void createZombie(int index, int row);
	bool createPlant(int index, int row, int col);
	void createCoin(int row,int col);
	void createCoin(vector<pair<int, int>>& generateCoin);
	void createBullet(int index, int row, int col);
	void createBullet(vector<pair<int,pair<int,int>>>& generateBullet);

	void destroyPlant(int row, int col);
	void destroyPlant(vector<pair<int, int>>& diePlant);
	void destroyBullet(vector<int>& dieBullet);
	void destroyZombie(int row, int col, int pos);
	void destroyZombie(vector<pair<pair<int, int>, int>> & dieZombie);

	void installCar();

	
	QTimer* timer;					//game timer
	int sumTime=0;		
	int sumTimeToZombie=0;
	int generateZombieTime[6] = { 0 };
	int generateZombieTimer[6] = { 0 };

	GameSystem sys;					//gamesystem
	
	QLabel* mouseLabel = nullptr;	//mouseEvent
	int curCardIndex = -1;
	int costNeeded = 0;
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);


	
	int getCurCol(int colx);		//grid
	int getCurRow(int rowy);
	int gridCol[10] = { 0,250,330,410,490,573,650,735,810,900 };
	int gridRow[6] = { 0,165 ,260, 366, 450, 545 };



	void playAnimation(int zombieName,int dieReason,int index,int x,int y,int intervals);		//animation

	enum CurGameCondition{NORMAL=0,SUSPEND,GAMEOVER};						//gameCondition
	CurGameCondition curGameCondition = NORMAL;
	QPushButton* gameSuspendButton = nullptr;
	void gameOver();
	QLabel* gameOverLabel = nullptr;

	QSound* SunSound = nullptr,*placeSound=nullptr;			//sound
};

