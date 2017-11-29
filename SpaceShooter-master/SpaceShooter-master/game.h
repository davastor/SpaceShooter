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

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene* scene;
    //QGraphicsView* view;
    Player* player;
    bool isShootingLaser;
    bool isShootingRocket;
    QTimer* spawnTimer;
    QTimer* enemyDestinationTimer;
    QTimer* enemyAngleTimer;
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


};

#endif // GAME_H
