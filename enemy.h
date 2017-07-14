#ifndef ENEMY_H
#define ENEMY_H

#include "game.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include <iostream>
#include <typeinfo>

class Enemy: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    //Constructor
    Enemy(QGraphicsItem *parent = 0);

    //initilize box2d enemy with x and y co-ordinates
    void initEnemy(b2World *world, float xx, float yy);

    //box2d methods -- not using as was causing too many problems
    float getX();
    float getY();
    void setX(float xx);
    void setY(float yy);
public slots:
    void move();
private:
    int enemySize;
    int randNumber;
    int enemyPosX;
    int enemyPosY;
    b2Body *enemyBody;
};

#endif // ENEMY_H
