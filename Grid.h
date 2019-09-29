#ifndef GRID_H
#define GRID_H
#include "Cell.h"
class Grid {
    private:
        Cell** cells;
        int rows;
        int columns;
    public:
        Grid();
        Grid(int columns, int rows);
        Grid(Grid* g);
        ~Grid();
        Cell* getCell(int column, int row);
        int getRows();
        void setRows(int rows);
        int getColumns();
        void setColumns(int columns);
        bool isOutOfBounds(int column, int row);
        bool equals(Grid* g);
};
#endif