#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPointF>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QMediaPlayer>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    int health;
    int shield;
    //double angle;
    QTimer* timer;
    bool isMovingLeft;
    bool isMovingRight;
    bool isMovingUp;
    bool isMovingDown;
    int playerAngle;
    bool destroyed;
    bool damaged;
    QMediaPlayer* hitSound;
    QMediaPlayer* playerExplosionSound;


public:
    explicit Player(QObject *parent = 0);
    ~Player();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setPlayerAngle(int _angle);
    int getPlayerAngle();
    bool getDestroyedStatus(){return destroyed;}
    QPointF getOrigin();
    int getHealth(){return health;}
    int getShield(){return shield;}

signals:

public slots:
    void updateState();
};

#endif // PLAYER_H
