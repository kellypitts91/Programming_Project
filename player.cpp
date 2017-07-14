#include "player.h"
using namespace std;

extern Game *game;
extern QVector<int> *enemyPosititons;
extern int bulletTimer;

Player::Player(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    xx = 0;
    yy = 0;
    setBrush(QBrush(Qt::white, Qt::SolidPattern));
    elapsedTime.start();
    lastBulletTime[0] = -500; //allows user to shoot instantly
}

void Player::initPlayer(b2World *world, float xx, float yy) {
    //body def for player
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(xx * 0.01, yy * 0.01); //original position of player

    //adds body definition to the box2d world
    playerBody = world->CreateBody(&bodyDef);

    //moving position of player
    setX(0.2);
    setY(1);

    //creating the shape of the player
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    //adding fixtures to the player
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 5.0f;

    //adding fixtures to the box2d body
    playerBody->CreateFixture(&fixtureDef);
}

//if user presses a key, this event will fire
void Player::keyPressEvent(QKeyEvent *event) {
    b2Vec2 vel = playerBody->GetLinearVelocity();
    xx = getX();
    yy = getY();

    //move left
    if(event->key() == Qt::Key_Left) {
        if(xx > 0) {    //stops player from going too far left (outside screen)
            vel.x = -2;
        }
        bulletDirection = 1;
        playerBody->SetLinearVelocity(vel);
    }

    //move right
    else if(event->key() == Qt::Key_Right) {
        if(xx*50 < game->getScreenWidth()-50) { //stops player from going too far right (outside screen)
            vel.x = 2;
        }
        bulletDirection = 2;
        playerBody->SetLinearVelocity(vel);
    }

    //Jump
    else if(event->key() == Qt::Key_Up) {
        //checking if player touching another object otherwise will not jump
        QList<QGraphicsItem *> colliding_items = collidingItems();
        if(!colliding_items.empty()) {
        //applying force to player to get it to jump
            b2Vec2 vel = playerBody->GetLinearVelocity();
            switch(bulletDirection) {
                case 1:
                    vel.x = -0.4;   //left
                    break;
                default:
                    vel.x = 0.4;    //right
                    break;
            }
            vel.y = 4; //upwards
            playerBody->SetLinearVelocity(vel);
        }
    }
    //fire bullet
    else if (event->key() == Qt::Key_Space) {
        // create a bullet -- cannot fire bullets in quick succession
        lastBulletTime[1] = elapsedTime.elapsed();
        if(lastBulletTime[1] - lastBulletTime[0] >= 500) {
            Bullet *bullet = new Bullet();
            bullet->initBullet();
            bullet->setPos(x(), y());
            scene()->addItem(bullet);
            lastBulletTime[0] = lastBulletTime[1];
        }
    }
}

void Player::spawn() {
    // create an enemy
    Enemy *newEnemy = new Enemy();
    enemyPosititons->append(newEnemy->pos().x()); //stores the x position of each monster
    //add enemy to the scene
    scene()->addItem(newEnemy);
}

//set and get methods
float Player::getX() {
    return playerBody->GetPosition().x;
}

float Player::getY() {
    return playerBody->GetPosition().y;
}

void Player::setX(float xx) {
    playerBody->SetTransform(b2Vec2(xx, playerBody->GetPosition().y), playerBody->GetAngle());
}

void Player::setY(float yy) {
    playerBody->SetTransform(b2Vec2(playerBody->GetPosition().x, yy), playerBody->GetAngle());
}

b2Body* Player::getPlayerBody() {
    return playerBody;
}

int Player::getBulletDirection() {
    return bulletDirection;
}

qint64 Player::getLastBulletTime() {
    return lastBulletTime[1] - lastBulletTime[0];
}
