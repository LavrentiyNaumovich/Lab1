#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Circle.hpp"
#include "Bonus.hpp"

class Board {
public:
    Board(int width, int height);
    ~Board();
    void draw(sf::RenderWindow& window);
    void swap(int x1, int y1, int x2, int y2);
    void update();
    Circle& getCircle(int x, int y) { return grid[x][y]; }

private:
    void initializeTargetPositions();
    bool checkMatches();
    void createNewCircles();
    void dropCircles();
    void startDropAnimation();
    void animate();
    void applyBonuses();

    int width;
    int height;
    bool animating;
    sf::Clock animationClock;
    std::vector<std::vector<Circle>> grid;
    std::vector<sf::Vector2f> targetPositions;
    std::vector<Bonus*> bonuses;
};

#endif // BOARD_HPP
