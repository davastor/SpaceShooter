#include "playerprojectile.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Enemy.h"

PlayerProjectile::PlayerProjectile(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
    timer->start(1000/60);
    duration = 0;

}

void PlayerProjectile::updateState()
{
    duration += 0.0179;
    dx = 15*qCos(qDegreesToRadians(rotation()));
    dy = 15*qSin(qDegreesToRadians(rotation()));
    setPos(x()+dx, y()+dy);

    if(duration >= 1)
    {
      scene()->removeItem(this);
      delete(this);
    }
}

PlayerProjectile::~PlayerProjectile()
{


}


