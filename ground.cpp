#include "ground.h"
using namespace std;

extern Game *game;

Ground::Ground(int x, int y, int w, int h, QGraphicsItem *parent):QGraphicsRectItem(parent) {
    gWidth = w;
    gHeight = h;
    setRect(x, y, gWidth, gHeight);
    setPos(x, y);
    setBrush(QBrush(Qt::green, Qt::SolidPattern));
}

void Ground::initGround(b2World *world, float x, float y)
{
    //Creates ground definition
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(x, y); //10% of screen height

    //adds ground to the box2d world
    b2Body *groundBody = world->CreateBody(&groundBodyDef);

    //creates the shape of the box
    b2PolygonShape groundBox;
    groundBox.SetAsBox(gWidth/2, -0.5); //screen width and box height

    //Adding fixtures to the ground
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.restitution = 0.1f;
    fixtureDef.density = 5.0f;

    //adding fixtures to box2d body
    groundBody->CreateFixture(&fixtureDef);
}

//get methods
int Ground::getWidth()
{
    return gWidth;
}
int Ground::getHeight()
{
    return gHeight;
}
