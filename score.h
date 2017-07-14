#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsItem>
#include <QFont>

class Score: public QGraphicsTextItem {
public:
    //Constructor
    Score(QGraphicsItem *parent = 0);

    //public methods
    void increase();
    void decrease();
    int getScore();
    void reset();
private:
    int score;
};

#endif // SCORE_H
