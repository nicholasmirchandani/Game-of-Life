#ifndef CLASSIC_H
#define CLASSIC_H
#include "Gamemode.h"
class Classic : public Gamemode {
    public:
        void calcNeighbors(Grid* g, int column, int row) override;
};
#endif