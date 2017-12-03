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
#include "EnemyLaser.h"
#include "playermissile.h"
#include <QGraphicsTextItem>
#include <QMediaPlayer>

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
    bool isShootingMissile;
    double missileTimer;
    QTimer* spawnTimer;
    QTimer* enemyDestinationTimer;
    QTimer* enemyAngleTimer;
    QTimer* playerFireTimer;
    QTimer* enemyFireTimer;
    QTimer* deathCheckTimer;
    QGraphicsTextItem* healthText;
    QGraphicsTextItem* shieldText;
    QGraphicsTextItem* scoreText;
    int score;
    QTimer* textUpdateTimer;
    int enemyCount;
    Enemy* enemy;
    int xRand;
    int yRand;
    int spawnArea;
    QList <Enemy*> enemyCollection;
    QMediaPlayer* music;
    QMediaPlayer* playerLaserSound;
    QMediaPlayer* missileSound;
    QMediaPlayer* explosionSound;
    QMediaPlayer* enemyLaserSound;

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
    void enemyFire();
    void updateText();
    void replayMusic(QMediaPlayer::State s);
    void deathCheck();


};

#endif // GAME_H
