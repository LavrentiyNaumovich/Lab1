#include "Bonus.hpp"
#include <cstdlib>

void ColorChangeBonus::apply(std::vector<std::vector<Circle>>& grid) {
    int width = grid.size();
    int height = grid[0].size();
    Circle::Color color = grid[x][y].getColor();
    grid[x][y].setColor(static_cast<Circle::Color>(rand() % 5));

    for (int i = 0; i < 2; ++i) {
        int randX, randY;
        do {
            randX = x + (rand() % 7 - 3);
            randY = y + (rand() % 7 - 3);
        } while (randX < 0 || randX >= width || randY < 0 || randY >= height || (randX == x && randY == y));

        grid[randX][randY].setColor(color);
    }
}

void BombBonus::apply(std::vector<std::vector<Circle>>& grid) {
    int width = grid.size();
    int height = grid[0].size();
    for (int i = 0; i < 5; ++i) {
        int randX = rand() % width;
        int randY = rand() % height;
        grid[randX][randY].setColor(Circle::EMPTY);
    }
}
