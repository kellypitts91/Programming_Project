#ifndef BULLET_H
#define BULLET_H

#include "game.h"
#include "player.h"
#include <cmath>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QList>
#include <QMouseEvent>
#include <typeinfo>
#include <iostream>
#include <QDebug>

class Bullet: public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    //Constructor
    Bullet(QGraphicsItem *parent = 0);

    //Public Methods
    void initBullet();  //Initialize the bullet
    float getX();
    float getY();
    void setX(float xx);
    void setY(float yy);
    void setAngle(float a);

    //get Box2d body
    b2Body *getBulletBody();

public slots:
    void move(); //moves the bullet every so often
private:
    int bulletSize;
    int bulletDirection;
    b2Body *bulletBody;
};

#endif // BULLET_H
