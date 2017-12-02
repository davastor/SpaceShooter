#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Player.h"
#include <QVector2D>
#include "playerprojectile.h"



class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    QTimer* timer;
    QLineF* line;
    QPointF p0;
    QPointF p1;
    QPointF p2;
    QLineF* line2;
    bool destinationSet;
    int health;
    QList <QGraphicsItem*> collItems;
    //PlayerProjectile* projectileType;


public:
    explicit Enemy(QObject *parent = 0);
    void setDestination(Player* player, int xRand, int yRand);
    void setAngle(Player* player);
   // void subtractHealth(int x);
   //int getHealth();
    ~Enemy();

signals:

public slots:
    void updateState();
};

#endif // ENEMY_H
