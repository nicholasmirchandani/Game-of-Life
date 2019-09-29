/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 2: Game of Life

The gamemode class defines essential game logic and serves as a parent class for any gamemode
*/


#include "Gamemode.h"

/*
    Updates whether or not cells are alive or dead on a given grid based on their respective number of neighbors
    g: Grid to update all cells on
*/
void Gamemode::updateCells(Grid* g) {
    for(int i = 0; i < g->getRows(); ++i) {
        for(int j = 0; j < g->getColumns(); ++j) {
            switch(g->getCell(j, i)->getNumNeighbors()) {
                case 0:
                case 1:
                    //Cell ded
                    g->getCell(j,i)->setIsAlive(false);
                    break;
                case 2:
                    //Nothing happens
                    break;
                case 3:
                    //Cell lives
                    g->getCell(j,i)->setIsAlive(true);
                    break;
                default: //4+ neighbors
                    //Cell ded
                    g->getCell(j,i)->setIsAlive(false);
                    break;
            }
        }
    }
}
/*
    Procedurally runs calcNeighbors for all cells on a given grid.
    g: grid to calculateAllNeighbors on
*/
void Gamemode::calcAllNeighbors(Grid* g) {
    int rows = g->getRows(); //Initializing variables before loop to save instructions
    int columns = g->getColumns();
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            calcNeighbors(g, j, i); //Calls the correct calcNeighbors thanks to polymorphism
        }
    }
}