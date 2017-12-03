#include "player.h"
#include <QGraphicsSceneMouseEvent>
#include "EnemyLaser.h"
#include "Enemy.h"
#include <QGraphicsScene>
#include <QDebug>

Player::Player(QObject *parent) : QObject(parent)
{
    setPixmap(QPixmap(":/images/player.png"));
    setRotation(90);
    setTransformOriginPoint(64, 64);
    setPos(500,500);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
    timer->start(1000/60);

    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;
    
    health = 100;
    shield = 100;
    destroyed = false;
    damaged = false;

    hitSound = new QMediaPlayer(this);
    hitSound->setMedia(QUrl("qrc:/audio/playerhitsound.mp3"));
    hitSound->setVolume(30);

    playerExplosionSound = new QMediaPlayer(this);
    playerExplosionSound->setMedia(QUrl("qrc:/audio/playerexplosion.wav"));
    playerExplosionSound->setVolume(10);

}

QPointF Player::getOrigin(){
    return mapToScene(transformOriginPoint());
}

void Player::setPlayerAngle(int _angle)
{
    playerAngle = _angle;
}

int Player::getPlayerAngle()
{
    return playerAngle;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        isMovingUp = true;
    }
    if(event->key() == Qt::Key_S)
    {
       isMovingDown = true;
    }
    if(event->key() == Qt::Key_A)
    {
       isMovingLeft = true;
    }
    if(event->key() == Qt::Key_D)
    {
       isMovingRight = true;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        isMovingUp = false;
    }
    if(event->key() == Qt::Key_S)
    {
       isMovingDown = false;
    }
    if(event->key() == Qt::Key_A)
    {
       isMovingLeft = false;
    }
    if(event->key() == Qt::Key_D)
    {
       isMovingRight = false;
    }
}

void Player::updateState()
{
    if(damaged == true)
    {
        setPixmap(QPixmap(":/images/player.png"));
        damaged = false;
    }

    QList <QGraphicsItem*> collItems = collidingItems();

    for(int i = 0; i < collItems.size(); i++)
    {
        if(typeid(*(collItems[i])) == typeid(EnemyLaser))
        {
            setPixmap(QPixmap(":images/playerDamaged.png"));
            damaged = true;
            hitSound->play();

            if(shield != 0)
                shield -= 10;
            else
                health -= 10;

            if(health <= 0)
            {
                scene()->removeItem(this);
                playerExplosionSound->play();
                destroyed = true;
                return;

            }
        }
        if(typeid(*(collItems[i])) == typeid(Enemy))
        {

            health -= 1;
            hitSound->play();
            if(health <= 0)
            {
                scene()->removeItem(this);
                playerExplosionSound->play();
                destroyed = true;
                return;
            }
        }
    }

    if(isMovingUp)
        setY(pos().y() - 5);
    if(isMovingDown)
        setY(pos().y() + 5);
    if(isMovingLeft)
        setX(pos().x() - 5);
    if(isMovingRight)
        setX(pos().x() + 5);

    //setRotation(angle);
}

Player::~Player()
{

}

