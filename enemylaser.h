#ifndef ENEMYLASER_H
#define ENEMYLASER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class EnemyLaser : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
 private:
     int dx;
     int dy;
     //int damageValue;
     QTimer* timer;
     double duration;

 public:
     explicit EnemyLaser(QObject *parent = 0);
     //int getDamageValue(){return damageValue;}
     ~EnemyLaser();

 signals:

 public slots:
     void updateState();
 };


#endif // ENEMYLASER_H
