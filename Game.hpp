#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"

class Game {
public:
    Game(int width, int height);
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleMouseClick(int x, int y);

    sf::RenderWindow window;
    Board board;
    Circle* selected;  
};

#endif // GAME_HPP
