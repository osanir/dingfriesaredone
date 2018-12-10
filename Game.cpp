#include "Game.h"

Game::Game() : window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT) , "Rider", Style::Default) {
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    srand(time(NULL));

    line[0].setSize( Vector2f(2, SCREEN_HEIGHT) );
    line[0].setFillColor(Color::White);
    line[0].setPosition( Vector2f(SCREEN_WIDTH/3, 0) );
    line[1].setSize( Vector2f(2, SCREEN_HEIGHT) );
    line[1].setFillColor(Color::White);
    line[1].setPosition( Vector2f(SCREEN_WIDTH*2/3, 0) );

    player.setRadius(SIZE/2);
    player.setFillColor(Color::White);
    player.setPosition( Vector2f(SCREEN_WIDTH/6-player.getRadius() , SCREEN_HEIGHT-player.getRadius()*3) );

    createRandomObstacles(1000);
    color = rand()%255;
    music.openFromFile("dingfriesaredone.wav");
    music.setLoop(true);
    music.play();
}

void Game::run(){
    while(window.isOpen() ){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents(){
    Event e;
    while( window.pollEvent(e) ){
        switch (e.type){
            case Event::Closed:
                window.close();
                break;
            default:
                break;
        }
        Vector2i player_pos;
        player_pos.x = player.getPosition().x;
        player_pos.y = player.getPosition().y;
        if( Keyboard::isKeyPressed(Keyboard::Right) )
            player.setPosition( (player_pos.x +SCREEN_WIDTH/3)%SCREEN_WIDTH, player_pos.y);
        if( Keyboard::isKeyPressed(Keyboard::Left) )
            player.setPosition( ( (player_pos.x - SCREEN_WIDTH/3)+SCREEN_WIDTH )%SCREEN_WIDTH, player_pos.y);
        
    }
}

void Game::update(){
    //SoundBuffer snd;
    updateObstacles();
    if(checkCollision())
        player.setFillColor(Color(color,color,color));
    else
        player.setFillColor(Color( 255-color, 255-color, 255-color));

    line[0].setFillColor(Color( 255-color, 255-color, 255-color));
    line[1].setFillColor(Color( 255-color, 255-color, 255-color));


    if( color >= 255 )
        right = false;
    if( color <= 0 )
        right = true;

    if( right ) color++;
    else        color--;

}

void Game::render(){
    static bool right = true;


    window.clear(Color(color,color,color));
    window.draw(line[0]);
    window.draw(line[1]);
    
    for( auto iter : obstacles)
        window.draw(iter->body);

    window.draw(player);
    window.display();
}

void Game::createRandomObstacles(int numOfObstacles){
    for(int i=0; i<numOfObstacles; i++){
        Obstacle *obstacle = new Obstacle;
        obstacle->pos = rand()%3;
        obstacle->body.setFillColor(Color::White);
        obstacle->body.setSize(SIZE2F);
        obstacle->body.setPosition( ((SCREEN_WIDTH/3)*obstacle->pos)+SCREEN_WIDTH/6-SIZE/2 , i*-SIZE*3 );
        obstacles.push_back(obstacle);
    }
}

void Game::updateObstacles(){
    for( auto iter : obstacles){
        iter->body.move( Vector2f(0, 10) );
        iter->body.setFillColor(Color( 255-color, 255-color, 255-color));
    }
}

bool Game::checkCollision(){
    for( auto iter : obstacles ){
        if( iter->body.getGlobalBounds().intersects( player.getGlobalBounds() ))
            return true;
    }
    return false;
}
