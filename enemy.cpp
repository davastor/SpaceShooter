#include "enemy.h"
#include <QLineF>


Enemy::Enemy(QObject *parent) : QObject(parent)
{

    setPixmap(QPixmap(":/images/alien.png"));
    setTransformOriginPoint(62, 119);
    timer = new QTimer(this);
    destinationSet = false;
    health = 100;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));

    timer->start(10);

}

void Enemy::setDestination(Player* player, int xRand, int yRand)
{
    destinationSet = true;
    QPointF p(player->getOrigin().x()+xRand, player->getOrigin().y()+yRand);
    p1 = QPointF(player->getOrigin());
    p2 = QPointF(pos());
    line = new QLineF(p, p2);


}

void Enemy::setAngle(Player* player)
{
    p1 = QPointF(player->getOrigin());
    p2 = QPointF(pos());
    line2 = new QLineF(p1, p2);
    setRotation(-1*line2->angle()-100);
}

void Enemy::updateState()
{

    if(destinationSet)
    {
        ;
        if(pos().x() != (p1.x()))
            setPos(x()-((line->dx()+75)/line->length()), y());
        if(pos().y() != (p1.y()))
            setPos(x(), y()-((line->dy()+145)/line->length()));
    }
}

void Enemy::subtractHealth(int x)
{
    health -= x;
}

int Enemy::getHealth()
{
    return health;
}

Enemy::~Enemy()
{
    delete timer;
    delete line;
    delete line2;
}

