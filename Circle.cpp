// Circle.cpp
#include "Circle.hpp"

Circle::Circle(Color color) : color(color) {
    shape.setRadius(20.0f);  // Adjust radius as needed
    shape.setOrigin(20.0f, 20.0f);  // Set origin to center of the circle
    // Set the color of the shape based on the Circle::Color
    switch (color) {
    case RED: shape.setFillColor(sf::Color::Red); break;
    case GREEN: shape.setFillColor(sf::Color::Green); break;
    case BLUE: shape.setFillColor(sf::Color::Blue); break;
    case YELLOW: shape.setFillColor(sf::Color::Yellow); break;
    case PURPLE: shape.setFillColor(sf::Color::Magenta); break;
    case EMPTY: shape.setFillColor(sf::Color::Transparent); break;
    }
}

Circle::Color Circle::getColor() const {
    return color;
}

void Circle::setColor(Color color) {
    this->color = color;
    switch (color) {
    case RED: shape.setFillColor(sf::Color::Red); break;
    case GREEN: shape.setFillColor(sf::Color::Green); break;
    case BLUE: shape.setFillColor(sf::Color::Blue); break;
    case YELLOW: shape.setFillColor(sf::Color::Yellow); break;
    case PURPLE: shape.setFillColor(sf::Color::Magenta); break;
    case EMPTY: shape.setFillColor(sf::Color::Transparent); break;
    }
}

sf::CircleShape& Circle::getShape() {
    return shape;
}

sf::Vector2f Circle::getPosition() const {
    return shape.getPosition();
}
