#include "stairs.h"
using namespace std;

extern Game *game;

Stairs::Stairs(float x, float y, float w, float h, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    gWidth = w;
    gHeight = h * 0.03;
    setRect(0, 0, gWidth, gHeight);
    setPos(x, y);
    setBrush(QBrush(Qt::green, Qt::SolidPattern));
}

void Stairs::initStairs(b2World *world, float x, float y)
{
    //Creates ground definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x + 1.6, y); //initial position of stairs

    //adds ground to the box2d world
    b2Body *stairBody = world->CreateBody(&bodyDef);

    //creates the shape of the box
    b2PolygonShape stair;
    stair.SetAsBox(gWidth*0.02/2, gHeight*0.02/2); //width and height of stairs

    //adding fixture to stairs
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &stair;
    fixtureDef.restitution = 0;
    fixtureDef.density = 5;
    fixtureDef.friction = 1;

    //add fixture to box2d body
    stairBody->CreateFixture(&fixtureDef);
}

//get methods
int Stairs::getWidth()
{
    return gWidth;
}
int Stairs::getHeight()
{
    return gHeight;
}
