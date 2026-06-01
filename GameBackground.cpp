#include "GameBackground.h"


GameBackground::GameBackground(QString pic,QWidget *parent)
	: QWidget(parent)
{
	this->pic = pic;
	this->setFixedSize(1103,600);
	this->setWindowIcon(QIcon(InitialIcon));
	
	this->cardVector.push_back(new PlantCard(SunPic, SunCd, SunCost, this));
	this->cardVector.push_back(new PlantCard(PeaShooterPic, PeaCd, PeaCost, this));
	this->cardVector.push_back(new PlantCard(NutPic, NutCd, NutCost, this));
	this->cardVector.push_back(new PlantCard(PotatoPic, PotatoCd, PotatoCost, this));
	this->cardVector.push_back(new PlantCard(CherryPic, CherryCd, CherryCost, this));
	this->cardVector.push_back(new PlantCard(RepeatShooterPic, RepeatShooterCd, RepeatShooterCost, this));
	for (int i = 0; i < this->cardVector.size(); i++) {
		this->cardVector[i]->show();
		this->cardVector[i]->move(300+i*50,8);
	}
	this->shovel = new Shovel(this);
	shovel->move(750, 0);
	shovel->show();

	this->mouseLabel = new QLabel(this);
	this->mouseLabel->hide();
	for (int i = 0; i < this->cardVector.size(); i++) {
		connect(this->cardVector[i], &QPushButton::pressed, [=]() {
			cardVector[i]->updateGameCondition(this->curGameCondition);
			if (this->curGameCondition != NORMAL)return;
			if (this->cardVector[i]->isOk()) {
				this->curCardIndex = i+1;
				this->costNeeded = this->cardVector[i]->getCost();
				QPixmap pix(QPixmap(this->cardVector[i]->getPlantPic()));
				this->mouseLabel->setPixmap(pix);
				this->mouseLabel->resize(pix.size());
				QPoint temp = this->mapFromGlobal(QCursor::pos());
				this->mouseLabel->move(temp.x()-pix.width()/2,temp.y()-pix.height()/2);
				this->mouseLabel->show();
			}
			});
	}
	connect(this->shovel, &QPushButton::pressed, [=]() {
		this->shovel->updateCurGameCondition(this->curGameCondition);
		if (this->curGameCondition != NORMAL)return;
		this->curCardIndex = 0;
		QPixmap pix(shovel->getPic());
		pix=pix.scaled(shovel->getSize());
		this->mouseLabel->setPixmap(pix);
		this->mouseLabel->resize(shovel->getSize());
		QPoint temp = this->mapFromGlobal(QCursor::pos());
		this->mouseLabel->move(temp.x() - pix.width() / 2, temp.y() - pix.height() / 2);
		this->mouseLabel->show();
		});



	//game's timer
	this->timer = new QTimer(this);
	this->timer->setInterval(gameTimeIntervals);
	//安装小推车
	this->installCar();
	//设置生成僵尸的时间
	for (int i = 1; i <= 5; i++) {
		this->generateZombieTime[i] = rand() % 20000 + 12001;
		this->generateZombieTimer[i] = 0;
	}
	this->curCoin = 50;
	//connect this game timer
	connect(this->timer, &QTimer::timeout, [=]() {//如果渲染物体数量和种类变多我这种架构就真成一坨了,必须考虑对象池以及world类,植物不能知道太多东西
		if (this->curGameCondition != NORMAL)return;
		//可以单独搞一个world类作为中间协调者,可以减少增加一个容器就要改一大堆虚函数并且可以内置更对函数,增加代码的复用性,符合开闭原则
		vector<pair<int, int>> generateCoin,diePlant;
		vector<pair<int, pair<int, int>>> generatebullet;
		vector<int> dieBullet;
		vector<pair<pair<int, int>, int>> dieZombie;
		bool isGameOver = false;
		this->sumTime += gameTimeIntervals;
		//this->sumTimeToZombie += gameTimeIntervals;
		//if (this->sumTime >= GenerateCoinTime) {
		//	createCoin(rand()%5+1,rand()%9+1);
		//	this->sumTime = 0;
		//}
		for (int i = 1; i <= 5; i++) {
			this->generateZombieTimer[i] += gameTimeIntervals;
			if (this->generateZombieTimer[i] >= generateZombieTime[i]) {
				int num = rand() % 2;
				for (int k = 1; k <= num; k++) {
					QTimer::singleShot(200,this, [=]() {createZombie(rand() % 5 + 1, i); });
				}
					this->generateZombieTimer[i] = 0;
				  this->generateZombieTime[i]=rand()%24000+12001;
				}
		}

		sys.updateCard(this->cardVector, this->curCoin);
		sys.plantReleaseSkillSystem(this->plantVector,generateCoin,generatebullet,this->zombieVecotr,diePlant,dieZombie);
		sys.zombieMovingSystem(this->zombieVecotr,isGameOver);
		//如果说游戏已经结束，剩下的就不执行了
		if (isGameOver) {
			this->gameOver();
			return;
		}
		sys.zombieReleaseSkillSystem(this->zombieVecotr, this->plantVector,diePlant);
		sys.bulletMovingSystem(this->bulletVector,dieBullet);
		sys.bulletReleaseSkillSystem(this->zombieVecotr, this->bulletVector,dieBullet,dieZombie);

		this->createCoin(generateCoin);
		this->createBullet(generatebullet);
		this->destroyBullet(dieBullet);
		this->destroyPlant(diePlant);
		this->destroyZombie(dieZombie);//可以考虑延时删除这样可以减少函数调用的次数
		});



	this->timer->start();

	coinNum = new QLabel(this);
	QFont font;
	font.setFamily("微软雅黑");
	font.setPointSize(12);
	coinNum->setFont(font);
	coinNum->setText(QString("%1").arg(this->curCoin));
	coinNum->setAlignment(Qt::AlignCenter);
	coinNum->resize(73, 33);
	coinNum->move(226,58);
	coinNum->show();
	//后续可以考虑将这些控件也做一个函数减少重复的代码数量
	this->gameSuspendButton = new QPushButton(this);
	QPixmap susBtnPix(SuspenButtonPic);
	this->gameSuspendButton->setIcon(susBtnPix);
	this->gameSuspendButton->setIconSize(susBtnPix.size());
	this->gameSuspendButton->resize(susBtnPix.width(), susBtnPix.height());
	this->gameSuspendButton->move(900, this->height()-this->gameSuspendButton->height());
	this->gameSuspendButton->show();
	QLabel* gameSuspendText = new QLabel(this);
	gameSuspendText->setText("暂停");
	gameSuspendText->setAlignment(Qt::AlignCenter);
	gameSuspendText->setFont(font);
	gameSuspendText->resize(113, 41);
	gameSuspendText->move(900, this->height() - 41);
	gameSuspendText->show();
	gameSuspendText->setAttribute(Qt::WA_TransparentForMouseEvents);
	connect(this->gameSuspendButton, &QPushButton::clicked, [=]() {
		static int condition=0;
		if (condition %2== 0) {
			this->curGameCondition = SUSPEND;
			gameSuspendText->setText("继续");
		}
		else {
			this->curGameCondition = NORMAL;
			gameSuspendText->setText("暂停");
		}
		condition++;
		});

	this->gameOverLabel = new QLabel(this);

	this->SunSound = new QSound(":/sound/sound_Sun.wav");
	this->placeSound = new QSound(":/sound/sound_Place.wav");
}
GameBackground::~GameBackground()
{
	this->SunSound->deleteLater();
	this->placeSound->deleteLater();

}
void GameBackground::resizeEvent(QResizeEvent* e) {

	return QWidget::resizeEvent(e);
}
void GameBackground::paintEvent(QPaintEvent* e) {
	QPainter painter(this);
	QPixmap pix;
	pix.load(this->pic);
	//pix = pix.scaled(900,600);
	painter.drawPixmap(0, 0, pix);
	pix.load(GeneralCardPic);
	pix = pix.scaled(466, 87);
	painter.drawPixmap(this->width()*GeneralCardX,this->height()*GeneralCardY, pix);
	if (this->curGameCondition == GAMEOVER) {
		painter.fillRect(rect(), QColor(0, 0, 0, 0.5 * 255));
	}
}
//create zombie logic
void GameBackground::createZombie(int index, int row) {
	Zombie* temp = nullptr;
	switch (index)
	{
	case 1:temp = new CommonZombie(row, this->gridRow[row],this);
		break;
	case 2:temp = new ConeZombie(row, this->gridRow[row], this);
		break;
	case 3:temp = new FootballZombie(row, this->gridRow[row], this);
		break;
	case 4:temp = new IronHubZombie(row, this->gridRow[row], this);
		break;
	case 5:temp = new IronDoorZombie(row, this->gridRow[row], this);
	default:
		break;
	}
	this->zombieVecotr[row][9].push_back(temp);
	if (temp != nullptr) {
		temp->curPic->show();
		temp->curPic->move(this->gridCol[9], this->gridRow[row] - temp->curPic->height());
	}
	
}

bool GameBackground::createPlant(int index, int row, int col) {
	if (row <= 0 || row > 5 || col <= 0 || col > 9)return false;
	if (this->plantVector[row][col] != nullptr)return false;
	Plant* temp = nullptr;
	switch (index)
	{
	case 1:temp = new Sun(row, col, this);
		break;
	case 2:temp = new PeaShooter(row, col, this);
		break;
	case 3:temp = new Nut(row, col, this);
		break;
	case 4:temp = new Potato(row, col, this);
		break;
	case 5:temp = new Cherry(row, col, this);
		break;
	case 6:temp = new RepeatShooter(row, col, this);
		break;
	default:
		break;
	}
	if (temp != nullptr) {
		plantVector[row][col] = temp;
		temp->curPic->show();
		temp->curPic->move(this->gridCol[col]+15, this->gridRow[row]-temp->curPic->height()-10);
		return true;
	}
	return false;
}
void GameBackground::createCoin(int row, int col) {
	Coin* temp = new Coin(this);
	temp->btn->show();
	temp->startAnimation(this->gridCol[col]+5, -66, this->gridCol[col] + 5, this->gridRow[row] - 66, row * 4000);
	connect(temp, &Coin::animationEnd, [=]() {
		if (temp->btn->y()== 0) {
			temp->btn->close();
			temp->deleteLater();
			return;
		}
		temp->timer->start();
		});
	connect(temp->btn, &QPushButton::clicked, [=]() {
		this->SunSound->play();
		curCoin += ValueOfEveryCoin;
		coinNum->setText(QString("%1").arg(this->curCoin));
		temp->timer->stop();
		temp->startAnimation(temp->btn->x(), temp->btn->y(), 220,0,300);
		});
	connect(temp, &Coin::die, [=]() {
		temp->btn->close();
		temp->deleteLater();
		});
}
void GameBackground::mouseMoveEvent(QMouseEvent* e) {
	if (this->curCardIndex != -1) {
		QPoint temp = this->mapFromGlobal(QCursor::pos());
		this->mouseLabel->move(temp.x()-this->mouseLabel->width()/2,temp.y()-this->mouseLabel->height()/2);
		this->mouseLabel->raise();
	}
	return QWidget::mouseMoveEvent(e);
}
void GameBackground::mouseReleaseEvent(QMouseEvent* e) {
	if (this->curCardIndex != -1) {
 		QPoint temp = this->mapFromGlobal(QCursor::pos());
		int x = temp.x();
		int y = temp.y();
		if (x >= 250&&x<=990&&y>=100&&y<=570) {
			int col = this->getCurCol(x);
			int row = this->getCurRow(y);
			if (this->curCardIndex == 0) {
				if (this->plantVector[row][col] != nullptr) {
					destroyPlant(row, col);
					this->placeSound->play();
				}
			}
			else if (this->createPlant(this->curCardIndex, row, col)) {
				this->curCoin -= this->costNeeded;
				coinNum->setText(QString("%1").arg(this->curCoin));
				this->cardVector[this->curCardIndex - 1]->updateCondition();
				this->placeSound->play();
			}
		}
		this->curCardIndex = -1;
		this->mouseLabel->hide();
		return;
	}
	return QWidget::mouseReleaseEvent(e);
}
int GameBackground::getCurCol(int x) {
	int res = -1;
	for (int i = 1; i <= 9; i++) {
		if (x >= this->gridCol[i]) {
			res = i;
		}
		else break;
	}
	return res;
}
int GameBackground::getCurRow(int y) {
	int res = -1;
	for (int i = 1; i <= 5; i++) {
		if (y <= this->gridRow[i]) {
			res = i;
			break;
		}
	}
	return res;
}
void GameBackground::createCoin(vector<pair<int, int>>& generateCoin) {
	for (auto it : generateCoin) {
		int row = it.first;
		int col = it.second;
		Coin* temp = new Coin(this);
		temp->btn->show();
		temp->startAnimation(this->gridCol[col], this->gridRow[row]-50, this->gridCol[col], this->gridRow[row] - 80, 350);
		QTimer::singleShot(410, temp, [=]() {temp->startAnimation(this->gridCol[col],this->gridRow[row]-80,this->gridCol[col],this->gridRow[row]-60,400); });
		connect(temp, &Coin::animationEnd, [=]() {
			if (temp->btn->y() == 0) {
				temp->btn->close();
				temp->deleteLater();
				return;
			}
			temp->timer->start();
			});
		connect(temp->btn, &QPushButton::clicked, [=]() {
			this->SunSound->play();
			curCoin += ValueOfEveryCoin;
			coinNum->setText(QString("%1").arg(this->curCoin));
			temp->timer->stop();
			temp->startAnimation(temp->btn->x(), temp->btn->y(), 220, 0, 300);
			});
		connect(temp, &Coin::die, [=]() {
			temp->btn->close();
			temp->deleteLater();
			});
	}
}//从代码单一职责来看,既然是UI文件,可以考虑只将这些东西show出来,创建的代码可以放在sys里面,然后就是可以考虑对象池只做拿取和归还,减少new的开销
void GameBackground::createBullet(int index, int row, int col) {
	Bullet* temp = nullptr;
	int x = this->gridCol[col] + 65;
	int y=this->gridRow[row]-80;
	switch (index)
	{
	case 1:temp = new Pea(row, col, x, y, this);
		break;
	default:
		break;
	}
	if (temp != nullptr) {
		this->bulletVector.push_back(temp);
		temp->curpic->show();
	}
}
void GameBackground::createBullet(vector<pair<int, pair<int, int>>>& generateBullet) {
	for (auto it : generateBullet) {
		int index = it.first;
		int row = it.second.first;
		int col = it.second.second;
		this->createBullet(index, row, col);
	}
}
void GameBackground::destroyBullet(vector<int>& dieBullet) {
	if (dieBullet.empty())return;
	for (int i = dieBullet.size() - 1; i >= 0; i--) {
		this->bulletVector[dieBullet[i]]->curpic->close();
		this->bulletVector[dieBullet[i]]->deleteLater();
		this->bulletVector.erase(this->bulletVector.begin() + dieBullet[i]);
	}
}
void GameBackground::destroyPlant(int row, int col) {
	if (this->plantVector[row][col] == nullptr)return;
	Plant* temp = this->plantVector[row][col];
	this->plantVector[row][col] = nullptr;
	temp->deleteLater();
}
void GameBackground::destroyPlant(vector<pair<int, int>>& diePlant) {
	if (diePlant.empty())return;
	for (auto it : diePlant) {
		int row = it.first;
		int col = it.second;
		this->destroyPlant(row, col);
	}
}
void GameBackground::destroyZombie(int row, int col, int pos) {
	auto& temp = this->zombieVecotr[row][col];
	if (temp.empty()||pos>=temp.size())return;
	if (temp[pos] == nullptr)return;
	Zombie* zombie = temp[pos];

	temp[pos] = nullptr;
	temp.erase(temp.begin() + pos);
	
	zombie->deleteLater();
}
void GameBackground::destroyZombie(vector<pair<pair<int, int>, int>>& dieZombie) {
	sort(dieZombie.begin(), dieZombie.end(), [](pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) {
		return a.second > b.second;
		});
	for (int i = 0; i < dieZombie.size(); i++) {
		int row = dieZombie[i].first.first;
		int col = dieZombie[i].first.second;
		int pos = dieZombie[i].second;
		int x = this->zombieVecotr[row][col][pos]->x;
		int y = this->zombieVecotr[row][col][pos]->y;
		int dieReason = this->zombieVecotr[row][col][pos]->dieReason;
		int zombieIndex = this->zombieVecotr[row][col][pos]->index;
		//销毁之前要播放一段动画
		if (dieReason == 1) {
			this->playAnimation(zombieIndex,dieReason, 1,x, y, 2500);
			this->playAnimation(zombieIndex, dieReason, 2, x, y, 2500);
		}
		else {
			this->playAnimation(zombieIndex, dieReason, 1, x, y, 3000);
		}
		this->destroyZombie(row, col, pos);
	}
}
void GameBackground::playAnimation(int zombieName,int dieReason, int index, int x, int y,int intervals) {
	QMovie *movie=nullptr;
	QLabel *movieLabel=nullptr;
	if (dieReason == 1) {
		if (index == 1) {
			switch (zombieName)
			{
			case 1:movie = new QMovie(ZombieBodyAnimation);
				break;
			case 2:movie = new QMovie(ZombieBodyAnimation);
				break;
			case 3:movie = new QMovie(FootballZombieDieAnimation);
				break;
			case 4:movie = new QMovie(ZombieBodyAnimation);
				break;
			case 5:movie = new QMovie(ZombieBodyAnimation);
				break;
			default:
				break;
			}
		}
		else {
			movie = new QMovie(ZombieHeadAnimation);
		}
	}
	else {
		movie = new QMovie(ZombieBurningAnimation);
	}
	if (movie != nullptr) {
		movieLabel = new QLabel(this);
		movieLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
		movieLabel->setMovie(movie);
		movie->start();
		movieLabel->move(x, y);
		movieLabel->show();
		QTimer::singleShot(intervals, [=]()mutable {
			movie->stop();
			movie->deleteLater();
			movieLabel->close();
			movieLabel->deleteLater();
			movie = nullptr;
			movieLabel = nullptr;
			});
	}
	
}
void GameBackground::gameOver() {
	this->curGameCondition = GAMEOVER;
	//放图片放特效
	update();
	QPixmap pix;
	pix.load(GameOverPic);
	pix = pix.scaled(this->width(), this->height());
	this->gameOverLabel->setPixmap(pix);
	this->gameOverLabel->resize(this->width(), this->height());
	this->gameOverLabel->move(0, 0);
	this->gameOverLabel->raise();
	this->gameOverLabel->show();
}
void GameBackground::installCar() {
	Bullet* car = nullptr;
	for (int i = 1; i <= 5; i++) {
		car = new Car(i, 1, this->gridCol[1]-70, this->gridRow[i]-57, this);
		car->curpic->show();
		this->bulletVector.push_back(car);
	}
}
////////////////////////////////////////////////////////////////////
//                          _ooOoo_                               //
//                         o8888888o                              //
//                         88" . "88                              //
//                         (| ^_^ |)                              //
//                         O\  =  /O                              //
//                      ____/`---'\____                           //
//                    .'  \\|     |//  `.                         //
//                   /  \\|||  :  |||//  \                        //
//                  /  _||||| -:- |||||-  \                       //
//                  |   | \\\  -  /// |   |                       //
//                  | \_|  ''\---/''  |   |                       //
//                  \  .-\__  `-`  ___/-. /                       //
//                ___`. .'  /--.--\  `. . ___                     //
//              ."" '<  `.___\_<|>_/___.'  >'"".                  //
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 //
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 //
//      ========`-.____`-.___\_____/___.-`____.-'========         //
//                           `=---='                              //
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //
//         佛祖保佑       永无BUG     永不修改                    //
////////////////////////////////////////////////////////////////////
