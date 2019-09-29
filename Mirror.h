#ifndef MIRROR_H
#define MIRROR_H
#include "Gamemode.h"
class Mirror :  public Gamemode {
    public:
        void calcNeighbors(Grid* g, int column, int row) override;
};
#endif