#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

class Entity : public QObject
{
    Q_OBJECT

private:
    int health;
    int shield;

public:
    explicit Entity(QObject *parent = 0);
    ~Entity();

signals:

public slots:
    void updateState();
};

#endif // ENTITY_H
