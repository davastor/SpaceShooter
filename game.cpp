#include "game.h"
#include <QCursor>
#include <CTime>
#include <QDebug>
#include <QMath.h>


Game::Game(QWidget*parent) : QGraphicsView(parent)
{

    scene = new QGraphicsScene(this);
    //view = new QGraphicsView(scene);
    player = new Player(this);

    setScene(scene);

    scene->setBackgroundBrush(QBrush(QImage(":/images/space.png")));

    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    isShootingLaser = false;
    isShootingMissile = false;
    enemyCount = 0;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920, 1080);
    setSceneRect(0,0,1920,1080);
    setCursor(QCursor(Qt::CrossCursor));
    setMouseTracking(true);

    srand(time(NULL));
    xRand = rand()%1000-500;
    yRand = rand()%1000-500;

    missileTimer = 3;

    spawnTimer = new QTimer(this);
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawn()));
    spawnTimer->start(1000);

    enemyDestinationTimer = new QTimer(this);
    connect(enemyDestinationTimer, SIGNAL(timeout()), this, SLOT(setEnemyDestination()));
    enemyDestinationTimer->start(2000);

    enemyAngleTimer = new QTimer(this);
    connect(enemyAngleTimer, SIGNAL(timeout()), this, SLOT(setEnemyAngle()));
    enemyAngleTimer->start(10);

    playerFireTimer = new QTimer(this);
    connect(playerFireTimer, SIGNAL(timeout()), this, SLOT(playerFire()));
    playerFireTimer->start(200);

    enemyFireTimer = new QTimer(this);
    connect(enemyFireTimer, SIGNAL(timeout()), this, SLOT(enemyFire()));
    enemyFireTimer->start(2000);

    deathCheckTimer = new QTimer(this);
    connect(deathCheckTimer, SIGNAL(timeout()), this, SLOT(deathCheck()));
    deathCheckTimer->start(100);

    healthText = new QGraphicsTextItem();
    healthText->setPlainText("Health: " + QString::number(player->getHealth()));
    healthText->setDefaultTextColor(Qt::red);
    healthText->setFont(QFont("tarial", 30));
    healthText->setPos(0,0);

    shieldText = new QGraphicsTextItem();
    shieldText->setPlainText("Shield: " + QString::number(player->getShield()));
    shieldText->setDefaultTextColor(Qt::blue);
    shieldText->setFont(QFont("arial", 30));
    shieldText->setPos(0,50);

    score = 0;
    scoreText = new QGraphicsTextItem();
    scoreText->setPlainText("Score: " + QString::number(score));
    scoreText->setDefaultTextColor(Qt::green);
    scoreText->setFont(QFont("arial", 50));
    scoreText->setPos(1920/2,0);

    scene->addItem(healthText);
    scene->addItem(shieldText);
    scene->addItem(scoreText);
    textUpdateTimer = new QTimer(this);
    connect(textUpdateTimer, SIGNAL(timeout()), this, SLOT(updateText()));
    textUpdateTimer->start(100);

    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/audio/gamemusic.mp3"));
    music->setVolume(10);
    music->play();

    playerLaserSound = new QMediaPlayer(this);
    playerLaserSound->setMedia(QUrl("qrc:/audio/lasersound.mp3"));
    playerLaserSound->setVolume(5);

    enemyLaserSound = new QMediaPlayer(this);
    enemyLaserSound->setMedia(QUrl("qrc:/audio/enemylasersound.mp3"));
    enemyLaserSound->setVolume(5);


    missileSound = new QMediaPlayer(this);
    missileSound->setMedia(QUrl("qrc:/audio/missileSound.wav"));
    missileSound->setVolume(10);

    explosionSound = new QMediaPlayer(this);
    explosionSound->setMedia(QUrl("qrc:/audio/explosion.mp3"));
    explosionSound->setVolume(10);

    connect(music, SIGNAL(stateChanged(QMediaPlayer::State)),this, SLOT(replayMusic(QMediaPlayer::State s)));

    show();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    p1 = player->getOrigin();
    p2 = event->pos();
    line = QLineF(p1, p2);
    angle = -1*line.angle()+90;
    player->setRotation(angle);
    player->setPlayerAngle(player->rotation());
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        isShootingLaser = true;
    if(event->button() == Qt::RightButton)
        isShootingMissile = true;
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        isShootingLaser = false;
    if(event->button() == Qt::RightButton)
        isShootingMissile = false;
}

void Game::mouseDoubleClickEvent(QMouseEvent *event)
{
   // music->play();
    return;
}

void Game::playerFire()
{
    playerLaserSound->stop();
    if(isShootingLaser == true)
    {
        PlayerLaser* laser = new PlayerLaser();
        scene->addItem(laser);

        laser->setTransformOriginPoint(0, 0);
        laser->setRotation(player->getPlayerAngle()-90);
        laser->setPos(player->getOrigin().x(), player->getOrigin().y());
        //playerLaserSound->setMedia(QUrl("qrc:/audio/lasersound.aiff"));
        playerLaserSound->play();
        //qDebug()<< "debug";
    }

    if(isShootingMissile == true && missileTimer >= 3)
    {
        PlayerMissile* missile = new PlayerMissile();
        scene->addItem(missile);

        missile->setTransformOriginPoint(0, 0);
        missile->setRotation(player->getPlayerAngle()-90);
        missile->setPos(player->getOrigin().x(), player->getOrigin().y());
        qDebug()<< "debug";
        missileSound->play();
        missileTimer = 0;
    }

    missileTimer += .24;
}

void Game::enemyFire()
{
    foreach(auto e, enemyCollection)
    {
        if(e->getDestroyedStatus() == true)
        {
            scene->removeItem(e);
            enemyCollection.removeAll(e);
            delete e;
            enemyCount--;
            score++;
            explosionSound->play();
        }
    }

    if(enemyCount != 0 && !enemyCollection.empty())
    {
        foreach(auto e, enemyCollection)
        {
                EnemyLaser* laser = new EnemyLaser();
                scene->addItem(laser);
                laser->setRotation(e->rotation()-90);
                int dx = 50*qCos(qDegreesToRadians(laser->rotation()));
                int dy = 15*qSin(qDegreesToRadians(laser->rotation()));
                laser->setTransformOriginPoint(18,19);
                laser->setPos(e->getOrigin());//e->x()-dx, e->y()+dy);
                enemyLaserSound->play();
        }
    }
}


void Game::spawn()
{
    srand(time(NULL));
    spawnArea = rand()%4;
    xSpawn = 0;
    ySpawn = 0;

    if(spawnArea == 0)  //spawn from top
    {
        xSpawn = rand()%300;
        ySpawn = rand()%300-1000;
    }
    if(spawnArea == 1) // spawn from bottom
    {
        xSpawn = rand()%300;
        ySpawn = rand()%300+1000;
    }
    if(spawnArea == 2) // spawn from left
    {
        xSpawn = rand()%300-1900;
        ySpawn = rand()%300;
    }

    if(spawnArea == 3)    //spawn from right
    {
        xSpawn = rand()%300+2100;
        ySpawn = rand()%300;
    }

    if(enemyCount < 3)
    {
        enemy = new Enemy(this);
        enemyCollection.push_back(enemy);
        scene->addItem(enemy);
        enemy->setPos(xSpawn, ySpawn);
        enemyCount++;
    }
}


void Game::setEnemyDestination()
{
    foreach(auto e, enemyCollection)
    {
        if(e->getDestroyedStatus() == true)
        {
            enemyCollection.removeAll(e);
            scene->removeItem(e);
            delete e;
            enemyCount--;
            score++;
            explosionSound->play();
        }
    }

    if(enemyCount != 0 && !enemyCollection.empty())
    {
        foreach(auto e, enemyCollection)
        {
                xRand = rand()%750-370;
                yRand = rand()%750-370;
                e->setDestination(player, xRand, yRand);
        }
    }
}

void Game::setEnemyAngle()
{
    foreach(auto e, enemyCollection)
    {
        if(e->getDestroyedStatus() == true)
        {
            scene->removeItem(e);
            enemyCollection.removeAll(e);
            delete e;
            enemyCount--;
            score++;

            explosionSound->play();
        }
    }

    if(enemyCount != 0 && !enemyCollection.empty())
    {
        foreach(auto e, enemyCollection)
            e->setAngle(player);
    }
}


void Game::updateText()
{
    healthText->setPlainText("Health: " + QString::number(player->getHealth()));
    shieldText->setPlainText("Shield: " + QString::number(player->getShield()));
    scoreText->setPlainText("Score: " + QString::number(score));
}

void Game::replayMusic(QMediaPlayer::State s)
{
    if (s == QMediaPlayer::StoppedState)
        music->play();
}

void Game::deathCheck()
{
    if(player->getDestroyedStatus() == true)
    {
        QGraphicsTextItem* gameOverText = new QGraphicsTextItem();
        gameOverText->setPlainText("GAME OVER");
        gameOverText->setDefaultTextColor(Qt::red);
        gameOverText->setFont(QFont("times", 40));
        gameOverText->setPos(1920/2-150, 1080/2);
        scene->addItem(gameOverText);
        setDisabled(true);
    }
}

Game::~Game()
{

}

