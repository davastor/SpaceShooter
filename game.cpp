#include "game.h"
#include <QCursor>
#include <CTime>

Game::Game(QWidget*parent) : QGraphicsView(parent)
{

    scene = new QGraphicsScene(this);
    //view = new QGraphicsView(scene);
    player = new Player();
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


    show();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{

    QPointF p1 = player->getOrigin();
    QPointF p2 = event->pos();
    QLineF line(p1, p2);
    double angle = -1*line.angle()+90;
    player->setRotation(angle);
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
        return;
    }
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{
    return;
}

void Game::mouseDoubleClickEvent(QMouseEvent *event)
{
    return;
}

void Game::spawn()
{
    spawnArea = rand()%3;
    int xSpawn = 0;
    int ySpawn = 0;

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


    if(enemyCount != 10)
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

