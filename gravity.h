#ifndef GRAVITY_H
#define GRAVITY_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <iostream>

//header files
#include "ground.h"
#include "player.h"
#include "game.h"

class Gravity: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    //Constructor
    Gravity(QGraphicsItem *parent=0);

    //Public methods
    void initGround_Gravity(b2World *world, float w, float h);
    float getTimeStep();
    int getVelocityIterations();
    int getPositionIterations();

public slots:
    //method to iterate the box2d step() function
    void step();
private:
    float timeStep;
    int velocityIterations;
    int positionIterations;
    int remainingSteps;
    b2Vec2 *gravity;
};

#endif // GRAVITY_H
