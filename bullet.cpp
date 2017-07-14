#include "bullet.h"
using namespace std;

extern Game *game;
extern Player *player;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsEllipseItem(parent)
{
    //gets the direction in which to shoot
    bulletDirection = player->getBulletDirection();
    bulletSize = 10;

    //draw rect -- draws a circle with rect co-ordinates
    switch (bulletDirection) {
        case 1:                     //Left
            setRect(-bulletSize, 25 - bulletSize/2, bulletSize, bulletSize); //x = -10, y = 20, w = 10, h = 10
            break;
        case 2:                    //Right
            setRect(50, 25 - bulletSize/2, bulletSize, bulletSize); //x = 50, y = 20, w = 10, h = 10
            break;
        default:                    //Right
            setRect(50, 25 - bulletSize/2, bulletSize, bulletSize); //x = 50, y = 20, w = 10, h = 10
            break;
    }

    //sets color to bullet
    setBrush(QBrush(Qt::gray, Qt::SolidPattern));

    //connect - calls the timer on the move() method
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    //bullet moves every 20mil/sec
    timer->start(10);
}

void Bullet::initBullet() {
    //body def for bullet
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    switch (bulletDirection) {
        case 1:                     //Left              Getting position of player so bullet moves relative to player
            bodyDef.position.Set(player->getX() - 0.5, player->getY() + 0.07);
            break;
        case 2:                     //Right
            bodyDef.position.Set(player->getX() + 0.5, player->getY() + 0.07);
            break;
        default:                    //Right
            bodyDef.position.Set(player->getX() + 0.5, player->getY() + 0.07);
            break;
    }

    //adds body definition to the box2d world
    bulletBody = game->getWorld()->CreateBody(&bodyDef);

    //giving box2d a circle shape to match the QT circle shape
    b2CircleShape circleShape;
    circleShape.m_radius = 0.6;

    //adding fixtures to the bullet
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.restitution = 0.9f;
    fixtureDef.density = 1.2f;
    fixtureDef.friction = 0.1f;

    //adding the fixtures to the box2d body
    bulletBody->CreateFixture(&fixtureDef);
}

void Bullet::move()
{
    // if bullet collides with enemy, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            // increase the score
            game->score->increase();

            // remove them both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // delete all objects involved in collision
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    //adding linear velocity to "push" the bullet in the intended direction
    b2Vec2 vel = bulletBody->GetLinearVelocity();

    switch (bulletDirection) {
        case 1:                     //Left
            vel.x = -4;
            break;
        case 2:                     //Right
            vel.x = 4;
            break;
        default:                    //Right
            vel.x = 4;
            break;
    }
    bulletBody->SetLinearVelocity(vel);
    int x = getX()*50;
    int y = getY()*50;
    //set QT position with new x and y co-ordinates
    setPos(x, y);

    //removing bullet if goes outside the field of view
    if ((pos().y() < 0)                                     //bottom border
            || (pos().y() > game->getScreenHeight())        //top border
            || (pos().x() < 0)                              //left border
            || (pos().x() > game->getScreenWidth()))        //right border
    {
        scene()->removeItem(this);
        delete this;
        return;
    }
}

//get and set methods
float Bullet::getX() {
    return bulletBody->GetPosition().x;
}

float Bullet::getY() {
    return bulletBody->GetPosition().y;
}

void Bullet::setX(float xx) {
    bulletBody->SetTransform(b2Vec2(xx, bulletBody->GetPosition().y), bulletBody->GetAngle());
}

void Bullet::setY(float yy) {
    bulletBody->SetTransform(b2Vec2(bulletBody->GetPosition().x, yy), bulletBody->GetAngle());
}

b2Body *Bullet::getBulletBody() {
    return bulletBody;
}

void Bullet::setAngle(float a) {
    if((a >= 0) && (a <= 360)) {
        bulletBody->SetTransform(b2Vec2(bulletBody->GetPosition().x, bulletBody->GetPosition().y), (a / 180) * M_PI);
    }
}


