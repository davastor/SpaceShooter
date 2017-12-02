#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Player.h"
#include <QMouseEvent>
#include <QWidget>
#include <QTimer>
#include "Enemy.h"
#include <QList>
#include "playerlaser.h"
#include "playerprojectile.h"

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene* scene;
    double angle;
    //QGraphicsView* view;
    QPointF p1;
    QPointF p2;
    QLineF line;
    int xSpawn;
    int ySpawn;
    Player* player;
    bool isShootingLaser;
    bool isShootingRocket;
    QTimer* spawnTimer;
    QTimer* enemyDestinationTimer;
    QTimer* enemyAngleTimer;
    QTimer* updateLaserTimer;
    QTimer* playerFireTimer;
    QTimer* updateRocketTimer;
    QList <Enemy*> enemyCollection;
    int enemyCount;
    Enemy* enemy;
    int xRand;
    int yRand;
    int spawnArea;

public:
    explicit Game(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    ~Game();

signals:

public slots:
    void spawn();
    void setEnemyDestination();
    void setEnemyAngle();
    void playerFire();

};

#endif // GAME_H
