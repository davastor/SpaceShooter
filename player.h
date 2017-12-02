#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPointF>
#include <QTimer>

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


public:
    explicit Player(QObject *parent = 0);
    ~Player();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void subtractHealth(int x);
    void subtractShield(int x);
    void setPlayerAngle(int _angle);
    int getPlayerAngle();
    int getHealth();
    QPointF getOrigin();

signals:

public slots:
    void updateState();
};

#endif // PLAYER_H
