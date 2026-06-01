#pragma once //存储基本的一些数据

//初始窗口的基本数据
#define InitialWidgetX 400
#define InitialWidgetY 200
#define InitialWidgetWidth 900
#define InitialWidgetHeight 600
//基本的pic
#define InitialIcon ":/pic/InitialGamePic/mainlogo.png"
#define InitialBackGroundPic ":/pic/InitialGamePic/Surface.png"
//按钮基本信息
#define StartGameButtonWidth 0.3
#define StartGameButtonHeight 0.22
#define StartGameButtonPrePic ":/pic/InitialGamePic/mx.png"
#define StartGameButtonRelPic ":/pic/InitialGamePic/mx1.png"
#define StartGameButtonX 0.56
#define StartGameButtonY 0.1

#define EnterGameButtonPrePic ":/pic/InitialGamePic/mini.png"
#define EnterGameButtonRelPic ":/pic/InitialGamePic/mini1.png"
#define EnterGameButtonWidth 0.25
#define EnterGameButtonHeight 0.16
#define EnterGameButtonX 0.58
#define EnterGameButtonY 0.32
#define EnterGameButtonAnimationIntervals 100
#define EnterGameButtonAnimationSum 8


//select game widget information
#define GameSelectBackgroundPic ":/pic/InitialGamePic/Title.jpg"
#define DayGamePic ":/pic/GameIngPic/Background(1).jpg"
#define NightGamePic ":/pic/InitialGamePic/Background2(1).jpg"
#define DayGameButtonWidth 0.42
#define DayGameButtonHeight 0.35
#define DayGameButtonX 0.05
#define DayGameButtonY 0.32
#define NightGameButtonWidth 0.42
#define NightGameButtonHeight 0.35
#define NightGameButtonX 0.52
#define NightGameButtonY 0.32


//gaming information
#define CardPic ":/pic/GameIngPic/Card.png"

#define GeneralCardPic ":/pic/GameIngPic/Shop.png"
#define GeneralCardWidth 0.63
#define GeneralCardHeight 0.16
#define GeneralCardX 0.2
#define GeneralCardY 0
#define ShovelBankPic ":/pic/GameIngPic/ShovelBank.png"
#define CardPic ":/pic/GameIngPic/Card.png"

//zombie 
//common zombie
#define CommonZombieWalkPic ":/pic/Zombie/CommonZombie/ZombieWalk1.gif"
#define CommonZombieWalkPic2 ":/pic/Zombie/CommonZombie/ZombieWalk2.gif"
#define CommonZombieAttackPic ":/pic/Zombie/CommonZombie/ZombieAttack.gif"
//cone zombie
#define ConeZombieWalkPic ":/pic/Zombie/ConeZombie/ConeZombieWalk.gif"
#define ConeZombieAttackingPic ":/pic/Zombie/ConeZombie/ConeZombieAttack.gif"
//football zombie
#define FootballZombieWalkPic ":/pic/Zombie/FootballZombie/FootballZombieWalk.gif"
#define FootballZombieAttackingPic ":/pic/Zombie/FootballZombie/FootballZombieAttack.gif"
//iron hub zombie
#define IronHubZombieWalkPic ":/pic/Zombie/IronHubZombie/BucketZombieWalk.gif"
#define IronHubZombieAttackingPic ":/pic/Zombie/IronHubZombie/BucketZombieAttack.gif"
//iron door zombie
#define IronDoorZombieWalkPic ":/pic/Zombie/IronDoorZombie/ScreenZombieWalk.gif"
#define IronDoorZombieAttackingPic ":/pic/Zombie/IronDoorZombie/ScreenZombieAttack.gif"

//Plant
//Sun
#define SunNormalPic ":/pic/Plant/Sun/SunFlower.gif"
#define SunPic ":/pic/Plant/Sun/SunFlower.png"
#define SunCd 6500 //6500
#define SunCost 50
//peashooter
#define PeaShooterNormalPic ":/pic/Plant/PeaShooter/Peashooter.gif"
#define PeaShooterPic ":/pic/Plant/PeaShooter/Peashooter.png"
#define PeaCd 12000
#define PeaCost 100
//Nut
#define NutPic ":/pic/Plant/Nut/WallNut.png"
#define NutNormalPic ":/pic/Plant/Nut/WallNut.gif"
#define NutHalfHeartPic ":/pic/Plant/Nut/WallNut1.gif"
#define NutLitterHeartPic ":/pic/Plant/Nut/WallNut2.gif"
#define NutCost 50
#define NutCd 25000
//Potato
#define PotatoPic ":/pic/Plant/Potato/PotatoMine(1).png"
#define PotatoNormalPic ":/pic/Plant/Potato/PotatoMine1.gif"
#define PotatoIsActivePic ":/pic/Plant/Potato/PotatoMine.gif"
#define PotatoBoomPic ":/pic/Plant/Potato/PotatoMineBomb.gif"
#define PotatoCd 25000
#define PotatoCost 25
//Cherry
#define CherryPic ":/pic/Plant/Cherry/CherryBomb.png"
#define CherryNormalPic ":/pic/Plant/Cherry/CherryBomb.gif"
#define CherryBoomPic ":/pic/Plant/Cherry/Boom.gif"
#define CherryCd 1000//35000
#define CherryCost 10//250
//RepeatShooter
#define RepeatShooterPic ":/pic/Plant/RepeatShoot/Repeater.png"
#define RepeatShooterNormalPic ":/pic/Plant/RepeatShoot/Repeater.gif"
#define RepeatShooterCd 25000
#define RepeatShooterCost 200

//Tool
//coin
#define gameCoinPic ":/pic/Tool/Sun.gif"
#define CoinExistTime 8000
#define ValueOfEveryCoin 50
#define GenerateCoinTime 10000
//shovel
#define ShovelBankPic ":/pic/Tool/ShovelBank.png"
#define ShovelPic ":/pic/Tool/Shovel.png"
//car
#define CarPic ":/pic/Tool/LawnMower.png"

//gameCondition
#define SuspenButtonPic ":/pic/GameIngPic/Button.png"
#define GameOverPic ":/pic/GameIngPic/ZombiesWon.png"


//Bullet
//pea
#define PeaPic ":/pic/Bullet/Pea.png"

//Animation
//Zombie's head
#define ZombieHeadAnimation ":/pic/Animation/ZombieHead.gif"
//Zombie's body
#define ZombieBodyAnimation ":/pic/Animation/ZombieDie.gif"
//burning Zombie
#define ZombieBurningAnimation ":/pic/Zombie/Burn.gif"
//football zombie die
#define FootballZombieDieAnimation ":/pic/Zombie/FootballZombie/FootballZombieDie.gif"
//grid size
#define GridSize 90

//define game time_intervals
#define gameTimeIntervals 20

//将每一列的坐标存储一下 250 330 410 490 573 650 735 810 900
//int EveryGridColX[10] = { 0,250,330,410,490,573,650,735,810,900 };
//0,165 ,260, 366, 450, 545 
