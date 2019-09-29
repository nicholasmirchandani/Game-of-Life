#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "Grid.h"
class Gamemode {
    public:
        virtual void calcNeighbors(Grid* g, int column, int row) {} //Should not be called, but must be defined since is virtual
        void calcAllNeighbors(Grid* g);
        void updateCells(Grid* g);
};
#endif