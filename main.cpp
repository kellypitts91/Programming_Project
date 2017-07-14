#include <QApplication>
#include <QMouseEvent>
#include "game.h"
#include "gravity.h"
#include "player.h"

//Global variables
Game *game;
Gravity *gravity;
Player *player;
QVector<int> *enemyPosititons = new QVector<int>;
int bulletTimer = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Start the game
    game = new Game();
    game->setStyleSheet("background-image:url(./desktop/pic.jpg);");
    game->show();

    return a.exec();
}

