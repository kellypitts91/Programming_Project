#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsItem>
#include <QFont>
#include <QTransform>

class Health: public QGraphicsTextItem {
public:
    //Constructor
    Health(QGraphicsItem *parent = 0);

    //Public Methods
    void decrease();
    int getHealth();
    void reset();
private:
    int health;
};

#endif // HEALTH_H
