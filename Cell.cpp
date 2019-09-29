/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 2: Game of Life

The cell class defines what a cell is, an object that can be alive or not with a certain number of neighbors
*/

#include "Cell.h"

/*
    Default constructor: the cell isn't alive and has no neighbors on generation
*/
Cell::Cell() {
    isAlive = false;
    numNeighbors = 0;
}

/*
    Default destructor: nothing needs to be done when the object is destroyed, so it is left empty.
*/
Cell::~Cell() {
    //Empty Default Destructor
}

/*
    Accessor for isAlive
    Returns whether or not the cell is alive
*/
bool Cell::getIsAlive() {
    return isAlive;
}

/*
    Mutator for isAlive
    isAlive: value you want to set isAlive to
*/
void Cell::setIsAlive(bool isAlive) {
    this->isAlive = isAlive;
}

/*
    Accessor for numNeighbors
    Returns cell's number of neighbors
*/
int Cell::getNumNeighbors() {
    return numNeighbors;
}

/*
    Mutator for numNeighbors
    numNeighbors: value you want to set numNeighbors to
*/
void Cell::setNumNeighbors(int numNeighbors) {
    this->numNeighbors = numNeighbors;
}

/*
    Boolean comparison as to whether or not cells are identical
    Returns true if the cells are identical, and false otherwise
*/
bool Cell::equals(Cell c) {
    if(c.getIsAlive() == isAlive && c.getNumNeighbors() == numNeighbors) {
        return true;
    }
    return false;
}