#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <Box2D/Box2D.h>
#include <iostream>
#include <typeinfo>

//header files
#include "bullet.h"
#include "game.h"
#include "enemy.h"

class Player: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    //Constructor
    Player (QGraphicsItem *parent=0);
    //overriding keyPressEvent()
    void keyPressEvent(QKeyEvent *event);

    //Public methods
    void initPlayer(b2World *world, float xx, float yy);
    float getX();
    float getY();
    void setX(float xx);
    void setY(float yy);
    int getBulletDirection();
    qint64 getLastBulletTime();

    //get Box2d body
    b2Body* getPlayerBody();

public slots:
    //spawn enemies using a timer
    void spawn();
private:
    float xx;
    float yy;
    int bulletDirection;
    QTimer *timer;
    b2Body *playerBody;
    QElapsedTimer elapsedTime;
    qint64 lastBulletTime[2];
};
#endif // PLAYER_H



