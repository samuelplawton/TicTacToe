#pragma once
#include "driver.h"
#include <utility>

class Interface {
public:
    int run();

private:
    TicTacToe game{};
    std::pair<int,int> promptMove() const;
    bool promptPlayAgain() const;
    void draw() const;
};