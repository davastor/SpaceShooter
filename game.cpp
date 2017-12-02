#include "game.h"
#include <QCursor>
#include <CTime>
#include <QDebug>

Game::Game(QWidget*parent) : QGraphicsView(parent)
{

    scene = new QGraphicsScene(this);
    //view = new QGraphicsView(scene);
    player = new Player(this);
    enemy = new Enemy(this);

    setScene(scene);

    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    isShootingLaser = false;
    isShootingRocket = false;

    enemyCount = 0;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920,1080);
    setSceneRect(0,0,1920,1080);
    setCursor(QCursor(Qt::CrossCursor));
    setMouseTracking(true);

    srand(time(NULL));
    xRand = rand()%1000-500;
    yRand = rand()%1000-500;

    spawnTimer = new QTimer(this);
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawn()));
    spawnTimer->start(1000);

    enemyDestinationTimer = new QTimer(this);
    connect(enemyDestinationTimer, SIGNAL(timeout()), this, SLOT(setEnemyDestination()));
    enemyDestinationTimer->start(1500);

    enemyAngleTimer = new QTimer(this);
    connect(enemyAngleTimer, SIGNAL(timeout()), this, SLOT(setEnemyAngle()));
    enemyAngleTimer->start(10);

    //updateLaserTimer = new QTimer(this);
    //updateRocketTimer = new QTimer(this);
    playerFireTimer = new QTimer(this);

    connect(playerFireTimer, SIGNAL(timeout()), this, SLOT(playerFire()));
    playerFireTimer->start(1000);

    show();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{

    p1 = player->getOrigin();
    p2 = event->pos();
    line = QLineF(p1, p2);
    angle = -1*line.angle()+90;
    player->setRotation(angle);
    player->setPlayerAngle(player->rotation());
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isShootingLaser = true;

    }
    if(event->button() == Qt::RightButton)
    {
        isShootingRocket = true;

    }
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isShootingLaser = false;
        //qDebug() << "debug lef click release";

    }
    if(event->button() == Qt::RightButton)
    {
        isShootingRocket = false;
    }
}

void Game::mouseDoubleClickEvent(QMouseEvent *event)
{
    return;
}

void Game::playerFire()
{
    if(isShootingLaser == true)
    {
        PlayerLaser* laser = new PlayerLaser();
        scene->addItem(laser);
        laser->setPos(player->getOrigin().x(), player->getOrigin().y());
        laser->setRotation(player->getPlayerAngle()-90);
        qDebug()<< "debug";
    }
}


void Game::spawn()
{
    spawnArea = rand()%3;
    xSpawn = 0;
    ySpawn = 0;

    if(spawnArea == 0)  //spawn from top
    {
        xSpawn = rand()%200;
        ySpawn = rand()%200-1000;
    }
    else if(spawnArea == 1) // spawn from bottom
    {
        xSpawn = rand()%200;
        ySpawn = rand()%200+1000;
    }
    else if(spawnArea == 2) // spawn from left
    {
        xSpawn = rand()%200-1500;
        ySpawn = rand()%200;
    }
    else    //spawn from right
    {
        xSpawn = rand()%200+1500;
        ySpawn = rand()%200;
    }

    if(enemyCount != 3)
    {
        enemy = new Enemy(this);
        enemyCollection.push_back(enemy);
        scene->addItem(enemy);
        enemy->setPos(xSpawn, ySpawn);
        enemyCount++;
    }
}

void Game::setEnemyDestination()
{
    if(enemyCount != 0)
    {
        foreach(auto enemy, enemyCollection)
        {
            xRand = rand()%750-370;
            yRand = rand()%750-370;
            enemy->setDestination(player, xRand, yRand);
        }
    }
}

void Game::setEnemyAngle()
{

    if(enemyCount != 0)
    {
        foreach(auto enemy, enemyCollection)
            enemy->setAngle(player);
    }

}


Game::~Game()
{

}

