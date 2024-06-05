#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/Graphics.hpp>

class Circle {
public:
    enum Color { RED, GREEN, BLUE, YELLOW, PURPLE, EMPTY };

    Circle(Color color);
    Color getColor() const;
    void setColor(Color color);
    sf::CircleShape& getShape();
    sf::Vector2f getPosition() const;

private:
    Color color;
    sf::CircleShape shape;
};

#endif // CIRCLE_HPP
