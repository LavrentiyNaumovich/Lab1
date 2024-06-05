#include "Board.hpp"
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>


Board::Board(int width, int height) : width(width), height(height), animating(false) {
    for (int i = 0; i < width; ++i) {
        std::vector<Circle> column;
        for (int j = 0; j < height; ++j) {
            column.push_back(Circle(static_cast<Circle::Color>(rand() % 5)));
            column.back().getShape().setPosition(i * 50 + 25, j * 50 + 25);
        }
        grid.push_back(column);
    }
    initializeTargetPositions();
}


Board::~Board() {
    for (auto bonus : bonuses) {
        delete bonus;
    }
}


void Board::initializeTargetPositions() {
    targetPositions.clear();
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            targetPositions.push_back(sf::Vector2f(i * 50 + 25, j * 50 + 25));
        }
    }
}

void Board::draw(sf::RenderWindow& window) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            window.draw(grid[i][j].getShape());
        }
    }
}


void Board::swap(int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 >= width || y1 < 0 || y1 >= height || x2 < 0 || x2 >= width || y2 < 0 || y2 >= height) {
        return;  
    }

    if (abs(x1 - x2) + abs(y1 - y2) != 1) {
        return;
    }

    std::swap(grid[x1][y1], grid[x2][y2]);
    std::swap(targetPositions[x1 * height + y1], targetPositions[x2 * height + y2]);

    if (!checkMatches()) {
        std::swap(grid[x1][y1], grid[x2][y2]);
        std::swap(targetPositions[x1 * height + y1], targetPositions[x2 * height + y2]);
    }
    else {

        animating = true;
        animationClock.restart();
    }
    checkMatches();
}



void Board::update() {
    if (!animating) {
        if (checkMatches()) {
            applyBonuses(); 
            startDropAnimation();
            
        }
    }
    else {
        
       startDropAnimation();
       
    }
}


bool Board::checkMatches() {
    bool matchFound = false;
    std::vector<std::pair<int, int>> toDestroy;

 
    for (size_t j = 0; j < height; ++j) {
        int matchLength = 1; 
        for (size_t i = 0; i < width; ++i) {
            bool endOfRow = (i == width - 1);
            bool match = (i < width - 1 && grid[i][j].getColor() == grid[i + 1][j].getColor() && grid[i][j].getColor() != Circle::EMPTY);

            if (match) {
                ++matchLength;
            }

            if (!match || endOfRow) {
                if (matchLength >= 3) {
                    for (int k = i - matchLength + 1; k <= i; ++k) {
                        toDestroy.push_back({ k, j });
                    }
                    matchFound = true;
                }
                matchLength = 1;
            }
        }
    }

  
    for (size_t i = 0; i < width; ++i) {
        int matchLength = 1; 
        for (size_t j = 0; j < height; ++j) {
            bool endOfColumn = (j == height - 1);
            bool match = (j < height - 1 && grid[i][j].getColor() == grid[i][j + 1].getColor() && grid[i][j].getColor() != Circle::EMPTY);

            if (match) {
                ++matchLength;
            }

            if (!match || endOfColumn) {
                if (matchLength >= 3) {
                    for (int k = j - matchLength + 1; k <= j; ++k) {
                        toDestroy.push_back({ i, k });
                    }
                    matchFound = true;
                }
                matchLength = 1;
            }
        }
    }

    for (auto& pos : toDestroy) {
        grid[pos.first][pos.second].setColor(Circle::EMPTY);
        // Generate bonus 
        if (rand() % 10 == 0) {
            bonuses.push_back(new ColorChangeBonus(pos.first, pos.second));
        }
        if (rand() % 10 == 0) {
            bonuses.push_back(new BombBonus(pos.first, pos.second));
        }

    }

    return matchFound;
}





void Board::applyBonuses() {
    for (auto bonus : bonuses) {
        bonus->apply(grid);
    }
    bonuses.clear(); 
}



void Board::createNewCircles() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (grid[i][j].getColor() == Circle::EMPTY) {
                grid[i][j].setColor(static_cast<Circle::Color>(rand() % 5));
            }
        }
    }
  
}



void Board::dropCircles() {
    for (int i = 0; i < width; ++i) {
        for (int j = height - 1; j >= 0; --j) {
            if (grid[i][j].getColor() == Circle::EMPTY) {
                int k = j;
                while (k > 0 && grid[i][k].getColor() == Circle::EMPTY) {
                    --k;
                }
                if (k >= 0) {
                    std::swap(grid[i][j], grid[i][k]);
                }
            }
        }
    }
    createNewCircles();
}


void Board::startDropAnimation() {
    dropCircles();
    animate();
    animating = true;
    animationClock.restart();
  
}

void Board::animate() {
    bool stillAnimating = false;
    sf::Time deltaTime = animationClock.restart();
    float speed = 1000.0f; 

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            sf::Vector2f currentPosition = grid[i][j].getShape().getPosition();
            sf::Vector2f targetPosition = targetPositions[i * height + j];
            if (currentPosition != targetPosition) {
                stillAnimating = true;
                sf::Vector2f direction = targetPosition - currentPosition;
                float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                if (distance > 1) {
                    direction /= distance;
                    direction *= speed * deltaTime.asSeconds();
                }
                grid[i][j].getShape().move(direction);
            }
        }
       
    }

    if (!stillAnimating) {
        animating = false;
      
        if (checkMatches()) {
            applyBonuses();
            startDropAnimation();
        }
    }
}

