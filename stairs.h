#ifndef STAIRS_H
#define STAIRS_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <Box2D/Box2D.h>
#include <iostream>

//header files
#include "game.h"

class Stairs: public QGraphicsRectItem {
public:
    //Constructor
    Stairs (float x, float y, float w, float h, QGraphicsItem *parent=0);

    //public methods
    void initStairs(b2World *world, float x = 0, float y = 0);
    int getWidth();
    int getHeight();
private:
    int gWidth;
    int gHeight;
};

#endif // STAIRS_H
