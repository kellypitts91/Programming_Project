#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QGraphicsItem>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <iostream>

//header files
#include "score.h"

class HighScore: public QGraphicsTextItem {
public:
    //Constructor
    HighScore(QGraphicsItem *parent = 0);

    //public methods
    int getHighScore();
    void setHighScore(int s);
private:
    int score;
};

#endif // HIGHSCORE_H
