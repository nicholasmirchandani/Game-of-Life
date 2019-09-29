/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 2: Game of Life

The mirror class extends the functionality of the base Gamemode class to contain the game logic for mirror.
*/

#include "Mirror.h"

/*
    Calculuates number of neighbors of a cell at a specific row/column in a given grid following mirror game logic
    g: Grid you're operating on
    column: column of the desired cell
    row: row of the desired cell
    Returns number of neighbors
*/
void Mirror::calcNeighbors(Grid* g, int column, int row) { 
    int numNeighbors = 0;
    for(int i = row-1; i <= row+1; ++i) {
        for(int j = column-1; j <= column+1; ++j) {
            if(i == row && j == column) {
                //Skip the cell itself when counting neighbors
                continue;
            }
            if(g->isOutOfBounds(j, i)) {
                //Mirror Logic; is neighbor if it is reflected
                int tempColumn = j;
                int tempRow = i; //using temporary values so as to not overrite i and j during iteration

                if(tempColumn < 0) {
                    tempColumn = 0;
                } else if (tempColumn > g->getColumns() - 1) {
                    tempColumn = g->getColumns() - 1;
                }

                if(tempRow < 0) {
                    tempRow = 0;
                } else if (tempRow > g->getRows() - 1) {
                    tempRow = g->getRows() - 1;
                }

                if(g->getCell(tempColumn, tempRow)->getIsAlive()) {
                    //If the cell is alive, it's a neighbor
                    ++numNeighbors;
                }
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