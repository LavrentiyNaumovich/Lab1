#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

struct Block {
    sf::RectangleShape shape;
    int health;
    bool indestructible;
    bool hasBonus;
    bool speedUpBall;

    Block(float x, float y, int hp, bool indestruct, bool bonus, bool speedUp);
};

struct Bonus {
    sf::CircleShape shape;
    bool active;
    enum Type { PaddleSize, BallSpeed, BallStick, ExtraLife, BallRandomTrajectory } type;

    Bonus(float x, float y, Type bonusType);
};

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void checkCollisions();
    void handleBonus(Bonus::Type bonusType);

    sf::RenderWindow window;
    sf::RectangleShape paddle;
    sf::CircleShape ball;
    sf::Vector2f ballVelocity;
    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;

    int score;
    int lives;
};

#endif // GAME_H
