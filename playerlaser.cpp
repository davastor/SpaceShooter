#include "playerlaser.h"


PlayerLaser::PlayerLaser()
{
    QPixmap p(":/images/PlayerLaser.png");
    auto item = new QGraphicsPixmapItem(p);
    setPixmap(p);

    damageValue = 10;

}

PlayerLaser::~PlayerLaser()
{

}

