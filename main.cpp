/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 2: Game of Life

main.cpp is the driver, handling prompts and user inputs into GameOfLife
*/

#include "GameOfLife.h"
#include <limits>

//Using column/row instead of row/column because column/row gives the familiar x/y

char getCharFromUser();
int getIntFromUser(std::string message);
double getDoubleFromUser(std::string message);
void pause();

int main(int argc, char** argv) {
    bool usingFileInput;
    int rows;
    int columns;
    GameOfLife* gol;
    Gamemode* gamemode;
    std::cout << "Would you classic mode ('c'), mirror mode ('m') or donut mode('d'): " << std::flush;
    char response = getCharFromUser();
    if(response == 'c') {
        gamemode = new Classic();
    } else if (response == 'm') {
        gamemode = new Mirror();
    } else if (response == 'd') {
        gamemode = new Donut();
    } else {
        std::cout << "Invalid input.  Defaulting to classic mode." << std::endl;
        gamemode = new Classic();
    }
    std::cout << "Would you like to read from a map file ('f') or randomly generate the board ('r')? " << std::flush;
    response = getCharFromUser();
    if(response == 'f') {
        std::string filepath;
            std::cout << "Enter the file path: ";
            getline(std::cin, filepath);
            std::ifstream is(filepath);
            if(is.fail()) {
                std::cout << "File '" + filepath + "' could not be opened.  Exiting." << std::endl;
                exit(1);
            }
            is >> rows;
            is >> columns;
            gol = new GameOfLife(columns, rows, gamemode);
            std::string line;
            getline(is, line); //Skipping empty line
            int rowNum = -1; //Starting at -1 so first loop is row 0
            while(!is.eof()) {
                getline(is, line);
                ++rowNum;
                if(rowNum >= gol->getCurrent()->getRows()) {
                    std::cout << "WARNING: More lines in file than expected.  Discarding additional lines." << std::endl;
                    break;
                }
                for(int i = 0; i < line.length(); ++i) {
                    if(i >= gol->getCurrent()->getColumns()) {
                        if(line[i] == 13) {
                            break; //Silently exit if there's a return as the final character on the line, as that's expected
                        }
                        std::cout << "WARNING: More characters in line " << rowNum + 3 << " than expected.  Discarding additional characters." << std::endl;
                        break;
                    }
                    if(line[i] == 'X') { //If character is neither X nor -, cell starts with default isAlive value of dead
                        //Cell is Alive
                        gol->getFuture()->getCell(i, rowNum)->setIsAlive(true);
                    } else if (line[i] == '-'){
                        //Cell is Dead
                        gol->getFuture()->getCell(i, rowNum)->setIsAlive(false); 
                    }
                }
            }
            is.close();
    } else if (response == 'r'){
        double density;
        columns = getIntFromUser("How many columns would you like in your simulation?  ");
        rows = getIntFromUser("How many rows would you like in your simulation?  ");
        gol = new GameOfLife(columns, rows, gamemode);
        density = -1; //Initializing density so we can enter our loop for certain
        while(!(density > 0 && density <= 1)) {
            density = getDoubleFromUser("On a scale from 0 to 1 (not including 0), what would you like the density of the cells to be?  ");
        }
        srand(time(0));
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < columns; ++j) {
                if((rand() / (double)RAND_MAX) < density) {
                    gol->getFuture()->getCell(j, i)->setIsAlive(true); 
                } else {
                    gol->getFuture()->getCell(j, i)->setIsAlive(false); 
                }
            }
        }
    } else {
        std::cout << "Input type not recognized.  Exiting." << std::endl;
        exit(1);
    }
    std::string unused;
    std::cout << "Would you like a brief pause between generations ('p'), have to press the enter key ('e'), or output to a file ('f')?: " << std::flush;
    response = getCharFromUser();
    if(response == 'p') {
        gol->start();
        while(!gol->getHasFinished()) {
            pause();
            std::cout << '\n'; //Formatting
            gol->showCells(gol->getCurrent());
            gol->update();
        }
        pause(); //Pausing before displaying finished to maintain flow
        std::cout << '\n'; //Formatting
    } else if (response == 'e') {
        gol->start();
        std::cout << '\n'; //Formatting
        while(!gol->getHasFinished()) {
            gol->showCells(gol->getCurrent());
            gol->update();
            getline(std::cin, unused); //Wait for return to show next update
        }
    } else if (response == 'f') {
        std::string filename;
        std::cout << "What file would you like to output to? ";
        getline(std::cin, filename);
        std::ofstream os(filename);
        if(os.fail()) {
            std::cout << "File '" + filename + "' could not be opened.  Exiting." << std::endl;
            exit(1);
        }
        gol->start();
        while(!gol->getHasFinished()) {
            gol->showCells(gol->getCurrent(), os);
            gol->update();
        }
    }


    std::cout << "Finished." << std::endl;
    std::cout << "Press enter to exit..." << std::flush;
    getline(std::cin, unused);

    return 0;
}

/*
    Handles char input from users
    Returns char value user typed in
*/
char getCharFromUser() { //Accounting for bad input and clearing the buffer, Function taken from interterm c++ assignments
    char input;
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

/*
    Handles int input from users; if non-int value is typed in, it'll take another input
    message: Message to reprompt with for another input
    Returns int value user typed in
*/
int getIntFromUser(std::string message)
{
    int input; //Declaring input inside the while loop would cause an error
    while(true) //Going to keep looping this until they enter valid input
    {
        std::cout << message;
        std::cin >> input;
        if(std::cin.fail()) //Accounting for non-double input
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignoring everything left in cin's buffer in case it messes with the next user input
            return input;
        }
    }
}

/*
    Handles double input from users; if non-double value is typed in, it'll take another input
    message: Message to reprompt with for another input
    Returns double value user typed in
*/
double getDoubleFromUser(std::string message)
{
    double input; //Declaring input inside the while loop would cause an error
    while(true) //Going to keep looping this until they enter valid input
    {
        std::cout << message;
        std::cin >> input;
        if(std::cin.fail()) //Accounting for non-double input
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignoring everything left in cin's buffer in case it messes with the next user input
            return input;
        }
    }
}

/*
    Utilizes system clock to temporarily halt program execution
*/
void pause() {
    //Utilizes system clock to make more precise pauses
    time_t initial = time(0);
    time_t current = time(0);
    while(difftime(current, initial) < 1) { //Pause cannot be shorter than 1 second because difftime returns 0 otherwise
        current = time(0);
    }
}