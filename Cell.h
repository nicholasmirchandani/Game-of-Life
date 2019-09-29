#ifndef CELL_H
#define CELL_H
class Cell {
    private:
        bool isAlive;
        int numNeighbors;
    public:
        Cell();
        ~Cell();
        bool getIsAlive();
        void setIsAlive(bool isAlive);
        int getNumNeighbors();
        void setNumNeighbors(int numNeighbors);
        bool equals(Cell c);
};
#endif