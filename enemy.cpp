#include "enemy.h"
using namespace std;

extern Game *game;
extern QVector<int> *enemyPosititons;

Enemy::Enemy(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    //enemy size will be between 30 and 55 pixels
    enemySize = rand() % 30 + 25;

    //set random x position -- either 0 (left) or 1 (right) of the screen
    randNumber = rand() % 2;
    switch(randNumber) {
        case 0:
            enemyPosX = 0;                                  //left of screen
            enemyPosY = 25;
            break;
        case 1:
            enemyPosX = game->getScreenWidth()-enemySize;   //right of screen
            enemyPosY = 25;
            break;
    }

    //set QT position of the enemy -- always at the same y position
    setPos(enemyPosX, enemyPosY);

    // draw the rect
    setRect(0, 0, enemySize, enemySize);

    //sets random color to enemies
    setBrush(QBrush((QColor((rand() % 255),(rand() % 255),(rand() % 255))), Qt::SolidPattern));

    //initEnemy(game->getWorld(), enemyPosX, 25);

    // make/connect a timer to move() the enemy every so often
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // start the timer - interval = 50
    timer->start(50);
}

//This method was for box2d -- left it here incase we can get it to work
void Enemy::initEnemy(b2World *world, float xx, float yy) {
    //body def for player
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(xx*0.02, yy*0.02);

    //adds body definition to the box2d world
    enemyBody = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;

    enemyBody->CreateFixture(&fixtureDef);
}

//move the enemy - has timer attached
void Enemy::move(){

    QList<QGraphicsItem *> colliding_items = collidingItems();

    //if health = 0, the health is reset to 3 and the highscore is updated
    if(game->health->getHealth() == 0) {
        game->health->reset();
        int gameScore = game->score->getScore();
        //only update highscore if it is higher than previous highscore
        if(gameScore > game->totalScore->getHighScore()) {
            game->totalScore->setHighScore(gameScore);
        }
        game->score->reset();
        return;
    }

    //if the enemy collides with the player, the health descreses by 1
    //and enemy gets deleted
    for(int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Player)) {
            game->health->decrease();
            delete this;
            return;
        }
    }

    // move enemy across screen
    switch (randNumber) {
    case 0:
        setPos(x()+1, y()); //left
        break;
    case 1:
        setPos(x()-1, y()); //right
        break;
    }
    // ----------------------------------------

    // destroy enemy when it goes out of the screen
    if((x() < 0) || (x() > game->getScreenWidth())) {
        delete this;
        return;
    }
}

//box2d methods -- not using as was causing too many problems
float Enemy::getX() {
    return enemyBody->GetPosition().x;
}

float Enemy::getY() {
    return enemyBody->GetPosition().y;
}

void Enemy::setX(float xx) {
    enemyBody->SetTransform(b2Vec2(xx, enemyBody->GetPosition().y), enemyBody->GetAngle());
}

void Enemy::setY(float yy) {
    enemyBody->SetTransform(b2Vec2(enemyBody->GetPosition().x, yy), enemyBody->GetAngle());
}
