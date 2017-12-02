#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "player.h"
#include <QMath.h>

class PlayerProjectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    int dx;
    int dy;
    int damageValue;
    QTimer* timer;
    QList <QGraphicsItem*> collItems;

public:
    explicit PlayerProjectile(QObject *parent = 0);
    int getDamageValue(){return damageValue;}
    ~PlayerProjectile();

signals:

public slots:
    void updateState();
};

#endif // PLAYERPROJECTILE_H
