/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 2: Game of Life

The classic class extends the functionality of the base Gamemode class to contain the game logic for classic.
*/

#include "Classic.h"

/*
    Calculuates number of neighbors of a cell at a specific row/column in a given grid following mirror game logic
    g: Grid you're operating on
    column: column of the desired cell
    row: row of the desired cell
    Returns number of neighbors
*/
void Classic::calcNeighbors(Grid* g, int column, int row) {
    int numNeighbors = 0;
    for(int i = row-1; i <= row+1; ++i) {
        for(int j = column-1; j <= column+1; ++j) {
            if(i == row && j == column) {
                //Skip the cell itself when counting neighbors
                continue;
            }
            if(g->isOutOfBounds(j, i)) {
                //Classic Logic: Neighbor doesn't count
                continue;
            } else {
                if(g->getCell(j, i)->getIsAlive()) {
                    //If the cell is alive, it's a neighbor
                    ++numNeighbors;
                }
            }
        }
    }
    g->getCell(column, row)->setNumNeighbors(numNeighbors);
}