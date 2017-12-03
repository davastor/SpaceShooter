#include "playerhealth.h"

PlayerHealth::PlayerHealth(QObject *parent) : QObject(parent)
{
    health = 100;
    setPlainText("Health: " + QString::number(health));
}

void PlayerHealth::setHealthValue(int _health)
{
    health = _health;
}

PlayerHealth::~PlayerHealth()
{

}

