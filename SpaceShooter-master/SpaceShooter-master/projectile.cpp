#include "projectile.h"

Projectile::Projectile(QObject *parent) : QObject(parent)
{

}

int Projectile::getDamageValue()
{
    return damageValue;
}

Projectile::~Projectile()
{

}

