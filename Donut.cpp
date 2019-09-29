/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 2: Game of Life

The donut class extends the functionality of the base Gamemode class to contain the game logic for donut.
*/

#include "Donut.h"

/*
    Calculuates number of neighbors of a cell at a specific row/column in a given grid following donut game logic
    g: Grid you're operating on
    column: column of the desired cell
    row: row of the desired cell
    Returns number of neighbors
*/
void Donut::calcNeighbors(Grid* g, int column, int row) {
    int numNeighbors = 0;
    for(int i = row-1; i <= row+1; ++i) {
        for(int j = column-1; j <= column+1; ++j) {
            if(i == row && j == column) {
                //Skip the cell itself when counting neighbors
                continue;
            }
            if(g->isOutOfBounds(j, i)) {
                //Donut Logic; is neighbor if it is wrapped around
                int tempColumn = j;
                int tempRow = i; //using temporary values so as to not overrite i and j during iteration

                if(tempColumn < 0) {
                    tempColumn = g->getColumns() - 1;
                } else if (tempColumn > g->getColumns() - 1) {
                    tempColumn = 0;
                }

                if(tempRow < 0) {
                    tempRow = g->getRows() - 1;
                } else if (tempRow > g->getRows() - 1) {
                    tempRow = 0;
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