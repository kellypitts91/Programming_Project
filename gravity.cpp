#include "gravity.h"
using namespace std;

extern Game *game;
extern Player *player;
extern int bulletTimer;

Gravity::Gravity(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    timeStep = 0.033f; //30 frames per second
    velocityIterations = 8;
    positionIterations = 3;
}

float Gravity::getTimeStep() {
    return timeStep;
}

int Gravity::getVelocityIterations() {
    return velocityIterations;
}

int Gravity::getPositionIterations() {
    return positionIterations;
}

//Main game loop
void Gravity::step() {
    b2World *w = game->getWorld();
    w->Step(timeStep, velocityIterations, positionIterations);

    //moving player with every time step
    int x = player->getX() * 50;
    int y = player->getY() * 50;
    player->setPos(x, y);
}


