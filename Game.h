#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <ctime>

using namespace sf;
using namespace std;

#define SCREEN_WIDTH    600
#define SCREEN_HEIGHT   768
#define SIZE 60
#define SIZE2F {SIZE,SIZE}
struct Obstacle{
    int pos;
    RectangleShape body;
    Obstacle(){
        body.setSize(SIZE2F);
        body.setFillColor(Color::White);
    }
};

class Game{
public:
    Game();
    void run();
private:
    void processEvents();
    void update();
    void render();

    void createRandomObstacles(int numOfObstacles);
    void updateObstacles();
    bool checkCollision();

    RectangleShape line[2];

    RenderWindow window;
    CircleShape player;
    list<Obstacle*> obstacles;
    Music music;
    int color;
    bool right;

};