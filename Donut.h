#ifndef DONUT_H
#define DONUT_H
#include "Gamemode.h"
class Donut : public Gamemode {
    public:
        void calcNeighbors(Grid* g, int column, int row) override;
};
#endif