#ifndef BONUS_HPP
#define BONUS_HPP

#include <vector>
#include "Circle.hpp"

class Bonus {
public:
    virtual void apply(std::vector<std::vector<Circle>>& grid) = 0;
};

class ColorChangeBonus : public Bonus {
public:
    ColorChangeBonus(int x, int y) : x(x), y(y) {}
    void apply(std::vector<std::vector<Circle>>& grid) override;

private:
    int x, y;
};

class BombBonus : public Bonus {
public:
    BombBonus(int x, int y) : x(x), y(y) {}
    void apply(std::vector<std::vector<Circle>>& grid) override;

private:
    int x, y;
};

#endif // BONUS_HPP
