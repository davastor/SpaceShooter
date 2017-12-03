#include "enemylaser.h"
#include <QGraphicsScene>
#include <QMath.h>
#include "Player.h"

EnemyLaser::EnemyLaser(QObject *parent) : QObject(parent)
{
    setPixmap(QPixmap(":/images/EnemyLaser.png"));
    //etScale(2);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
    timer->start(1000/60);
    duration = 0;
}


void EnemyLaser::updateState()
{
    QList <QGraphicsItem*> collItems = collidingItems();

    for(int i = 0; i < collItems.size(); i++)
    {
        if(typeid(*(collItems[i])) == typeid(Player))
        {
                scene()->removeItem(this);
                delete(this);
                return;

        }
    }

    duration += 0.0179;
    dx = 12*qCos(qDegreesToRadians(rotation()));
    dy = 12*qSin(qDegreesToRadians(rotation()));
    setPos(x()+dx, y()+dy);

    if(duration >= 4.5)
    {
      scene()->removeItem(this);
      delete(this);
    }
}


EnemyLaser::~EnemyLaser()
{

}

