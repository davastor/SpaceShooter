#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>

class Projectile : public QObject
{
    Q_OBJECT
private:
    int damageValue;
public:
    explicit Projectile(QObject *parent = 0);
    int getDamageValue();
    ~Projectile();

signals:

public slots:
};

#endif // PROJECTILE_H
