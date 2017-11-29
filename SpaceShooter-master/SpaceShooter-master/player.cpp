#include "player.h"
#include <QGraphicsSceneMouseEvent>

Player::Player(QObject *parent) : QObject(parent)
{
    setPixmap(QPixmap(":/images/player.png"));
    setRotation(90);
    setTransformOriginPoint(64, 64);
    setPos(500,500);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
    timer->start(1000/60);

    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;
}

QPointF Player::getOrigin(){
    return mapToScene(transformOriginPoint());
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
    if(isMovingUp)
        setY(pos().y() - 3);
    if(isMovingDown)
        setY(pos().y() + 3);
    if(isMovingLeft)
        setX(pos().x() - 3);
    if(isMovingRight)
        setX(pos().x() + 3);

    // setRotation(angle);
}

Player::~Player()
{

}
