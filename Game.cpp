#include "Game.h"
#include <cstdlib>
#include <ctime>

Block::Block(float x, float y, int hp, bool indestruct, bool bonus, bool speedUp)
    : health(hp), indestructible(indestruct), hasBonus(bonus), speedUpBall(speedUp) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(60, 20));
    shape.setFillColor(sf::Color::White);
}

Bonus::Bonus(float x, float y, Type bonusType) : active(true), type(bonusType) {
    shape.setPosition(x, y);
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Yellow);
}

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid Game"), score(0), lives(3), ballVelocity(0.3f, 0.3f) {
    paddle.setSize(sf::Vector2f(100, 20));
    paddle.setFillColor(sf::Color::Green);
    paddle.setPosition(WINDOW_WIDTH / 2 - paddle.getSize().x / 2, WINDOW_HEIGHT - 50);

    ball.setRadius(10.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    // Initialize blocks
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            blocks.emplace_back(60 * j, 20 * i, 1, false, (rand() % 5 == 0), (rand() % 10 == 0));
        }
    }

    srand(static_cast<unsigned int>(time(0)));
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
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        paddle.move(-0.6f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        paddle.move(0.6f, 0.f);
    }
}

void Game::update() {
    ball.move(ballVelocity);

   
    if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= WINDOW_WIDTH) {
        ballVelocity.x = -ballVelocity.x;
    }
    if (ball.getPosition().y <= 0) {
        ballVelocity.y = -ballVelocity.y;
    }

    if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
        ballVelocity.y = -ballVelocity.y;
    }


    if (ball.getPosition().y + ball.getRadius() * 2 >= WINDOW_HEIGHT) {
        lives--;
        ball.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        if (lives == 0) {
            window.close();
        }
    }

    checkCollisions();
}

void Game::checkCollisions() {
    for (auto& block : blocks) {
        if (block.shape.getGlobalBounds().intersects(ball.getGlobalBounds())) {
            ballVelocity.y = -ballVelocity.y;
            if (!block.indestructible) {
                block.health--;
                if (block.health <= 0) {
                    if (block.hasBonus) {
                        bonuses.emplace_back(block.shape.getPosition().x, block.shape.getPosition().y, static_cast<Bonus::Type>(rand() % 5));
                    }
                    score += 1;
                    block.shape.setPosition(-100, -100); 
                }
            }
            if (block.speedUpBall) {
                ballVelocity.x *= 1.1f;
                ballVelocity.y *= 1.1f;
            }
        }
    }

    for (auto& bonus : bonuses) {
        if (bonus.active) {
            bonus.shape.move(0, 0.2f);
            if (bonus.shape.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
                handleBonus(bonus.type);
                bonus.active = false;
            }
        }
    }
}

void Game::handleBonus(Bonus::Type bonusType) {
    switch (bonusType) {
    case Bonus::PaddleSize:
        paddle.setSize(sf::Vector2f(paddle.getSize().x * 1.5f, paddle.getSize().y));
        break;
    case Bonus::BallSpeed:
        ballVelocity.x *= 1.5f;
        ballVelocity.y *= 1.5f;
        break;
    case Bonus::BallStick:
    
        break;
    case Bonus::ExtraLife:
        lives++;
        break;
    case Bonus::BallRandomTrajectory:
        ballVelocity.x = (rand() % 2 == 0) ? 0.3f : -0.3f;
        ballVelocity.y = (rand() % 2 == 0) ? 0.3f : -0.3f;
        break;
    }
}

void Game::render() {
    window.clear();

    window.draw(paddle);
    window.draw(ball);

    for (const auto& block : blocks) {
        window.draw(block.shape);
    }

    for (const auto& bonus : bonuses) {
        if (bonus.active) {
            window.draw(bonus.shape);
        }
    }

    window.display();
}
