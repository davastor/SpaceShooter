#ifndef PLAYERMISSILE_H
#define PLAYERMISSILE_H

#include "playerprojectile.h"
#include <QObject>

class PlayerMissile: public PlayerProjectile
{
public:
    explicit PlayerMissile();
    ~PlayerMissile();
};

#endif // PLAYERMISSILE_H
