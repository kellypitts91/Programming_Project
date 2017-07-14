#include "game.h"

using namespace std;
extern Gravity *gravity;
extern Player *player;

Game::Game(QWidget *parent): QGraphicsView(parent)
{
    screenWidth = 700;
    screenHeight = 500;

    //creating scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, screenWidth, screenHeight);

    //flipping y axis of scene to match box2d
    QGraphicsView *view = new QGraphicsView(this);
    view->setScene(scene);
    view->scale(1, -1);//flips y axis here

    //changing background colors
    //view->setBackgroundBrush(QBrush(Qt::blue, Qt::SolidPattern));
    setScene(scene);

    //turn off horizontal scrolling
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth, screenHeight);

    //gravity initilization
    world = new b2World (b2Vec2(0, -9.8f));
    gravity = new Gravity();

    // ************** Ground
    Ground *gameGround = new Ground(0, 0, screenWidth, screenHeight*0.05);

    //add static box2d object to ground
    gameGround->initGround(world, 0, 0);

    //add ground to QT scene
    scene->addItem(gameGround);

    // ************** Stairs -- this took a lot of playing around with
    int width = 200;
    float x = screenWidth - width;      //500
    float y = 25;
    float box2dx = x * 0.02;            //500*0.02 = 10
    float box2dy = -y * 0.02 + 0.1;     //-25*0.02 = -0.5
    for(int i = 0; i < 5; i++) {        // 5 steps
        Stairs *stair = new Stairs(x, y, width, screenHeight);
        stair->initStairs(world, box2dx, box2dy);
        scene->addItem(stair);
        x += 20;
        y += 15;
        box2dy += 0.3;
        box2dx += 0.3;
    }

    // ************** Player
    player = new Player();

    //add dynamic box2d object to player with initial position
    player->initPlayer(world, 10, gameGround->getHeight());

    player->setRect(0,0, 50, 50); // player size = 50 by 50
    player->setPos(10, gameGround->getHeight()); //pos: x = 10, y = 25 (screenHeight = 500 * 0.05)

    //player is focusable -- sets focus onload
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //add player to QT scene
    scene->addItem(player);

    //create the score
    score = new Score();
    score->setPos(0, screenHeight);
    scene->addItem(score);

    //create the high score
    totalScore = new HighScore();
    totalScore->setPos(totalScore->x() + screenWidth-150, totalScore->y() + screenHeight);
    scene->addItem(totalScore);

    //create the health
    health = new Health();
    health->setPos(health->x(), health->y() + screenHeight - 25);
    scene->addItem(health);

    // ************** Game loop
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), gravity, SLOT(step()));
    timer->start(20);

    // ************** Enemy spawn loop
    QTimer *timer1 = new QTimer();
    QObject::connect(timer1, SIGNAL(timeout()), player, SLOT(spawn()));
    timer1->start(3000);

    //display the QT scene
    show();
}

//get and set methods
int Game::getScreenWidth()
{
    return screenWidth;
}

int Game::getScreenHeight()
{
    return screenHeight;
}

b2World* Game::getWorld() {
    return world;
}

//flips the y axis back to original for certain objects. eg. Text
QTransform Game::transformY() {
    QTransform t;
    t.translate(1, -1);
    t.scale(1, -1);
    return t;
}


