#include "playerprojectile.h"
#include <QGraphicsScene>
#include "Enemy.h"

PlayerProjectile::PlayerProjectile(QObject *parent) : QObject(parent)
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
    timer->start(1000/60);
}

void PlayerProjectile::updateState()
{
    dx = 5*qCos(qDegreesToRadians(rotation()));
    dy = 5*qSin(qDegreesToRadians(rotation()));
    setPos(x()+dx, y()+dy);
    collItems = collidingItems();
    int n = collItems.size();

    if(pos().y() > 1000 || pos().y() < -1000)
    {
      scene()->removeItem(this);
      delete(this);
    }

    for(int i = 0; i < n; i++)
    {
        if(typeid(*(collItems[i])) == typeid(Enemy))
        {
            scene()->removeItem(this);
            delete(this);

        }
    }
}



PlayerProjectile::~PlayerProjectile()
{


}


