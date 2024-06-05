#include "Game.hpp"

Game::Game(int width, int height) : window(sf::VideoMode(width * 50, height * 50), "GEMS"), board(width, height) {
    selected = nullptr;
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }
}

void Game::handleMouseClick(int x, int y) {
    int gridX = x / 50;
    int gridY = y / 50;
    if (selected == nullptr) {
        selected = &board.getCircle(gridX, gridY);
    }
    else {
        board.swap(selected->getPosition().x / 50, selected->getPosition().y / 50, gridX, gridY);
        selected = nullptr;
    }
}

void Game::update() {
    board.update();
}

void Game::render() {
    window.clear();
    board.draw(window);
    window.display();
}
