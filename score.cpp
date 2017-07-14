#include "score.h"
#include "game.h"

extern Game *game;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //initialize the score to zero
    score = 0;

    //draw the text
    setPlainText(QString("Score: ") + QString::number(score));  //Score: 0
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 16));

    //transform y back to original state -- to avoid upside down text
    this->setTransform(game->transformY());
}

void Score::increase() {
    score++;
    setPlainText(QString("Score: ") + QString::number(score));
}

void Score::decrease() {
    score--;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore() {
    return score;
}

void Score::reset() {
    score = 0;
    setPlainText(QString("Score: ") + QString::number(score));
}
