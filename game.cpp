#include "game.h"
#include <QCursor>


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

    spawnTimer = new QTimer(this);
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawn()));
    spawnTimer->start(1000);

    enemyDestinationTimer = new QTimer(this);
    connect(enemyDestinationTimer, SIGNAL(timeout()), this, SLOT(setEnemyDestination()));
    enemyDestinationTimer->start(10);

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
    if(enemyCount != 10)
    {
        int xPos = rand()%200 + 1000;
        int yPos = rand()%200 + 1000;
        enemy = new Enemy(this);
        enemyCollection.push_back(enemy);
        scene->addItem(enemy);
        enemy->setPos(xPos, yPos);
        enemyCount++;
    }
}

void Game::setEnemyDestination()
{
    foreach(auto e, enemyCollection)
        e->getDestination(player);
}

Game::~Game()
{

}

