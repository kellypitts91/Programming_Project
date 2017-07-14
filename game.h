#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <iostream>

//header files
#include "ground.h"
#include "gravity.h"
#include "score.h"
#include "health.h"
#include "highscore.h"
#include "player.h"
#include "stairs.h"

class Game: public QGraphicsView {
public:
    //Constructor
    Game(QWidget *parent=0);

    //public methods
    QTransform transformY(); //flips y axis for a certain item
    int getScreenWidth();
    int getScreenHeight();
    b2World *getWorld();

    //public variables
    QGraphicsScene *scene;
    Score *score;
    Health *health;
    HighScore *totalScore;
private:
    int screenWidth;
    int screenHeight;
    b2World *world;
};

#endif // GAME_H
