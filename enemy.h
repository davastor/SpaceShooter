#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Player.h"
#include <QVector2D>
#include "playerprojectile.h"
#include <QList>
#include <QMediaPlayer>


class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    QTimer* timer;
    QLineF line;
    QPointF p0;
    QPointF p1;
    QPointF p2;
    QLineF line2;
    bool destinationSet;
    bool destroyed;
    bool damaged;
    int health;
    //QList <QGraphicsItem*> collItems;
    //PlayerProjectile* projectileType;
    QMediaPlayer* hitSound;


public:
    explicit Enemy(QObject *parent = 0);
    void setDestination(Player* player, int xRand, int yRand);
    void setAngle(Player* player);
    bool getDestroyedStatus(){return destroyed;}
    QPointF getOrigin(){ return mapToScene(transformOriginPoint());}

    ~Enemy();

signals:

public slots:
    void updateState();
};

#endif // ENEMY_H
