#include "health.h"
#include "game.h"

extern Game *game;

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //initialize the health to 3
    health = 3;

    //draw the text
    setPlainText(QString("Health: ") + QString::number(health));  //Health: 3
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 16));

    //transform y back to original state -- to avoid upside down text
    this->setTransform(game->transformY());
}

void Health::decrease() {
    health--;
    setPlainText(QString("Health: ") + QString::number(health));
}

int Health::getHealth() {
    return health;
}

void Health::reset() {
    health = 3;
    setPlainText(QString("Health: ") + QString::number(health));
}
