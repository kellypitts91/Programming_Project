#include "highScore.h"
#include "game.h"
using namespace std;

extern Game *game;

HighScore::HighScore(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //initialize the score with 0
    score = 0;

    //draw the text
    setPlainText(QString("High Score: ") + QString::number(score));  //High Score:
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 16));

    //transform y back to original state -- to avoid upside down text
    this->setTransform(game->transformY());
}

int HighScore::getHighScore() {
    return score;
}

//tried to implement saving highscore to a txt file - kind of works
void HighScore::setHighScore(int s) {
    score = s;
    setPlainText(QString("High Score: ") + QString::number(score));  //High Score:
}
