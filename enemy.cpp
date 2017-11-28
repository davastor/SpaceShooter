#include "enemy.h"
#include <QLineF>

Enemy::Enemy(QObject *parent) : QObject(parent)
{

    setPixmap(QPixmap(":/images/alien.png"));
    setTransformOriginPoint(62, 119);
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));

    timer->start(10);

}

void Enemy::getDestination(Player* player)
{
    p1 = QPointF(player->getOrigin());
    p2 = QPointF(pos());
    line = new QLineF(p1, p2);


    setRotation(-1*line->angle()-90);

}

void Enemy::updateState()
{
    if(pos().x() != (p1.x()))
        setPos(x()-((line->dx()+75)/line->length()), y());
    if(pos().y() != (p1.y()))
        setPos(x(), y()-((line->dy()+145)/line->length()));


    setPos(x(), y());
}

Enemy::~Enemy()
{
    delete timer;
    delete line;
}

