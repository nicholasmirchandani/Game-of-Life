/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 2: Game of Life

GameOfLife is the abstracted class containing the game logic and all required game components
*/

#include "GameOfLife.h"

using namespace std;

/*
    Default Constructor: as a game should always have a set amount of rows and columns, this is intentionally left empty
*/
GameOfLife::GameOfLife() {
    //Default Constructor; shouldn't be used
}

/*
    Overloaded Constructor: Properly intializes a game with a set amount of rows and columns and a gamemode
    columns: number of columns in the game
    rows: number of rows in the game
    gamemode: gamemode for the game
*/
GameOfLife::GameOfLife(int columns, int rows, Gamemode* gamemode) {
    previous = new Grid(columns, rows);
    current = new Grid(columns, rows);
    future = new Grid(columns, rows);
    this->gamemode = gamemode;
}

/*
    Destructor: Properly deallocates dynamically allocated memory in the constructor
*/
GameOfLife::~GameOfLife() {
    delete previous;
    delete current;
    delete future;
}

/*
    Shows all cells from a grid to standard output
    g: Grid to show cells from
*/
void GameOfLife::showCells(Grid* g) {
    cout << generation << endl;
    int rows = g->getRows(); //Defining rows and columns outside so it only runs once instead of once per loop
    int columns = g->getColumns();
    for(int i = 0; i < rows; ++i) { 
        for(int j = 0; j < columns; ++j) {
            cout << ((g->getCell(j, i)->getIsAlive()) ? 'X' : '-'); //iterating through rows second to easily format output
        }
        cout << '\n'; //Formatting, using \n instead of endl to avoid flushing preemptively
    }
    cout << flush;
}

/*
    Shows all cells from a grid to output file stream
    g: Grid to show cells from
    os: output file stream to output to
*/
void GameOfLife::showCells(Grid* g, ofstream& os) {
    os << generation << endl;
    int rows = g->getRows(); //Defining rows and columns outside so it only runs once instead of once per loop
    int columns = g->getColumns();
    for(int i = 0; i < rows; ++i) { 
        for(int j = 0; j < columns; ++j) {
            os << ((g->getCell(j, i)->getIsAlive()) ? 'X' : '-'); //iterating through rows second to easily format output
        }
        os << endl; //Formatting
    }
}

/*
    Starts the game
*/
void GameOfLife::start() {
    current = new Grid(future); //When game starts, current grid is given some initial value based on the future grid (set when generating board)
}

/*
    Runs code for a single generation; calculates neighbors, updates cells, and checks for stabilization
*/
void GameOfLife::update() {
    gamemode->calcAllNeighbors(future);
    gamemode->updateCells(future);
    if(current->equals(future) || future->equals(previous)) { //Using previous and future to check as far back as 2 generations for stabilization
        hasFinished = true;
    }
    previous = new Grid(current);
    current = new Grid(future);
    ++generation;
}

/*
    Accessor for hasFinished
    Returns true if the game has finished, false otherwise
*/
bool GameOfLife::getHasFinished() {
    return hasFinished;
}

/*
    Accessor for future
    Returns pointer to future grid
*/
Grid* GameOfLife::getFuture() {
    return future;
}

/*
    Accessor for current
    Returns pointer to current grid
*/
Grid* GameOfLife::getCurrent() {
    return current;
}
