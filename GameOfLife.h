#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
#include <iostream>
#include <fstream>
#include "Classic.h"
#include "Donut.h"
#include "Mirror.h"
class GameOfLife {
    private:
        Gamemode* gamemode;
        Grid* current;
        Grid* future;
        Grid* previous;
        bool hasFinished;
        int generation;
    public:
        GameOfLife();
        ~GameOfLife();
        GameOfLife(int columns, int rows, Gamemode* gamemode);
        void showCells(Grid* g);
        void showCells(Grid* g, std::ofstream& os);
        void start();
        void update();
        bool getHasFinished();
        Grid* getFuture();
        Grid* getCurrent();
};
#endif