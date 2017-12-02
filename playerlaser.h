#ifndef PLAYERLASER_H
#define PLAYERLASER_H

#include "playerprojectile.h"
#include <QObject>

class PlayerLaser: public PlayerProjectile
{
public:
    explicit PlayerLaser();
    ~PlayerLaser();
};

#endif // PLAYERLASER_H
