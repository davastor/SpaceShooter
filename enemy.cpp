#include "enemy.h"
#include <QLineF>
#include <QGraphicsScene>
#include "PlayerLaser.h"
#include "playermissile.h"
#include "player.h"
#include "enemylaser.h"

Enemy::Enemy(QObject *parent) : QObject(parent)
{

    setPixmap(QPixmap(":/images/alien.png"));
    setTransformOriginPoint(62, 119);
    timer = new QTimer(this);
    destinationSet = false;
    destroyed =false;
    damaged = false;
    health = 100;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));

    hitSound = new QMediaPlayer(this);
    hitSound->setMedia(QUrl("qrc:/audio/hitsound.mp3"));
    hitSound->setVolume(15);

    timer->start(10);

}

void Enemy::setDestination(Player* player, int xRand, int yRand)
{
    destinationSet = true;
    p0 = QPointF(player->getOrigin().x()+xRand, player->getOrigin().y()+yRand);
    p1 = QPointF(player->getOrigin());
    p2 = QPointF(pos());
    line = QLineF(p0, p2);
}

void Enemy::setAngle(Player* player)
{
    p1 = QPointF(player->getOrigin());
    p2 = QPointF(pos());
    line2 =  QLineF(p1, p2);
    setRotation(-1*line2.angle()-100);
}

void Enemy::updateState()
{
    //hitSound->stop();

    if(damaged == true)
    {
        setPixmap(QPixmap(":/images/alien.png"));
        damaged = false;
    }
    QList <QGraphicsItem*> collItems = collidingItems();

    for(int i = 0; i < collItems.size(); i++)
    {
       /* if(typeid(*(collItems[i])) == typeid(EnemyLaser) || typeid(*(collItems[i])) == typeid(Enemy))
        {
            collItems.removeAll(collItems[i]);
            return;
        }*/

        if(typeid(*(collItems[i])) == typeid(PlayerLaser))
        {
            scene()->removeItem(collItems[i]);
            delete(collItems[i]);

            health -= 10;
            setPixmap(QPixmap(":images/alienDamaged.png"));
            damaged = true;
            hitSound->play();

            if(health <= 0)
            {
                //setPixmap(QPixmap(":images/explosion.png"));
                destroyed = true;
                return;
            }

            return;
        }
        if(typeid(*(collItems[i])) == typeid(PlayerMissile))
        {
            scene()->removeItem(collItems[i]);
            delete(collItems[i]);
           // setPixmap(QPixmap(":images/explosion.png"));
            destroyed = true;
            return;

        }


    }


    if(destinationSet)
     {
         if(pos().x() != (p1.x()))
             setPos(x()-(4*(line.dx()+75)/line.length()), y());
         if(pos().y() != (p1.y()))
             setPos(x(), y()-(4*(line.dy()+145)/line.length()));
     }


    collItems.clear();
}



Enemy::~Enemy()
{


}

