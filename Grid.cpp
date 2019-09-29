/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 2: Game of Life

The grid class defines what a grid is, an aggregation of cells with a set amount of rows and columns
*/

#include "Grid.h" //Already includes Cell

/*
    Default Constructor: as a Grid for a game should always have a set amount of rows and columns, this is intentionally left empty
*/
Grid::Grid() {
    //Empty Default Constructor; shouldn't be used
}

/*
    Overloaded Constructor: Properly initializes a grid with a set amount of rows and columns
    columns: number of columns in the grid
    rows: number of rows in the grid
*/
Grid::Grid(int columns, int rows) {
    this->rows = rows;
    this->columns = columns;
    cells = new Cell*[columns];
    for(int i = 0; i < columns; ++i) {
        cells[i] = new Cell[rows];
    }
}

/*
    Copy Constructor: Makes a deep copy of a grid
    g: Grid to copy from
*/
Grid::Grid(Grid* g) {
    this->rows = g->getRows();
    this->columns = g->getColumns();
    cells = new Cell*[columns];
    for(int i = 0; i < columns; ++i) {
        cells[i] = new Cell[rows];
    }
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            cells[j][i] = *(g->getCell(j, i));
        }
    }
}

/*
    Destructor: Properly deallocates memory to avoid memory leaks
*/
Grid::~Grid() {
    for(int i = 0; i < rows; ++i) {
        delete[] cells[i];
    }
    delete[] cells;
}

/*
    Returns a pointer to a Cell at a given column and row in the grid
    column: Column of the cell in the grid
    row: Row of the cell in the grid
*/
Cell* Grid::getCell(int column, int row) {
    return &cells[column][row];
}

/*
    Accessor for rows
    Returns number of rows in the grid
*/
int Grid::getRows() {
    return rows;
}

/*
    Mutator for rows
    rows: value you want to set rows to
*/
void Grid::setRows(int rows) {
    this->rows = rows;
}

/*
    Accessor for columns
    Returns number of columns in the grid
*/
int Grid::getColumns() {
    return columns;
}

/*
    Mutator for columns
    columns: value you want to set columns to
*/
void Grid::setColumns(int columns) {
    this->columns = columns;
}

/*
    Checks whether or not a column and row refer to a cell that is out of bounds of the grid
    column: Column being checked
    row: Row being checked
    Returns true if row and column refer to something out of bounds of the grid, false otherwise
*/
bool Grid::isOutOfBounds(int column, int row) {
    return (column < 0 || column >= this->columns || row < 0 || row >= this->rows);
}

/*
    Checks whether or not two grids are equal
    g: Grid to compare this grid against
    Returns true if grids are equal, false otherwise
*/
bool Grid::equals(Grid* g) {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(!(getCell(j, i)->equals(*(g->getCell(j,i))))) { //Very confusing parentheses :(.  If any cell between the grids aren't equal, then the grids aren't equal
                return false; //If any cell is not equal, return false
            }
        }
    }
    return true;
}