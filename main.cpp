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
using namespace std;

char getCharFromUser();
int getIntFromUser(string message);
double getDoubleFromUser(string message);
void pause();

int main(int argc, char** argv) {
    bool usingFileInput;
    int rows;
    int columns;
    GameOfLife* gol;
    Gamemode* gamemode;
    cout << "Would you classic mode ('c'), mirror mode ('m') or donut mode('d'): " << flush;
    char response = getCharFromUser();
    if(response == 'c') {
        gamemode = new Classic();
    } else if (response == 'm') {
        gamemode = new Mirror();
    } else if (response == 'd') {
        gamemode = new Donut();
    } else {
        cout << "Invalid input.  Defaulting to classic mode." << endl;
        gamemode = new Classic();
    }
    cout << "Would you like to read from a map file ('f') or randomly generate the board ('r')? " << flush;
    response = getCharFromUser();
    if(response == 'f') {
        string filepath;
            cout << "Enter the file path: ";
            getline(cin, filepath);
            ifstream is(filepath);
            if(is.fail()) {
                cout << "File '" + filepath + "' could not be opened.  Exiting." << endl;
                exit(1);
            }
            is >> rows;
            is >> columns;
            gol = new GameOfLife(columns, rows, gamemode);
            string line;
            getline(is, line); //Skipping empty line
            int rowNum = -1; //Starting at -1 so first loop is row 0
            while(!is.eof()) {
                getline(is, line);
                ++rowNum;
                if(rowNum >= gol->getCurrent()->getRows()) {
                    cout << "WARNING: More lines in file than expected.  Discarding additional lines." << endl;
                    break;
                }
                for(int i = 0; i < line.length(); ++i) {
                    if(i >= gol->getCurrent()->getColumns()) {
                        if(line[i] == 13) {
                            break; //Silently exit if there's a return as the final character on the line, as that's expected
                        }
                        cout << "WARNING: More characters in line " << rowNum + 3 << " than expected.  Discarding additional characters." << endl;
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
        cout << "Input type not recognized.  Exiting." << endl;
        exit(1);
    }
    string unused;
    cout << "Would you like a brief pause between generations ('p'), have to press the enter key ('e'), or output to a file ('f')?: " << flush;
    response = getCharFromUser();
    if(response == 'p') {
        gol->start();
        while(!gol->getHasFinished()) {
            pause();
            cout << '\n'; //Formatting
            gol->showCells(gol->getCurrent());
            gol->update();
        }
        pause(); //Pausing before displaying finished to maintain flow
        cout << '\n'; //Formatting
    } else if (response == 'e') {
        gol->start();
        cout << '\n'; //Formatting
        while(!gol->getHasFinished()) {
            gol->showCells(gol->getCurrent());
            gol->update();
            getline(cin, unused); //Wait for return to show next update
        }
    } else if (response == 'f') {
        string filename;
        cout << "What file would you like to output to? ";
        getline(cin, filename);
        ofstream os(filename);
        if(os.fail()) {
            cout << "File '" + filename + "' could not be opened.  Exiting." << endl;
            exit(1);
        }
        gol->start();
        while(!gol->getHasFinished()) {
            gol->showCells(gol->getCurrent(), os);
            gol->update();
        }
    }


    cout << "Finished." << endl;
    cout << "Press enter to exit..." << flush;
    getline(cin, unused);

    return 0;
}

/*
    Handles char input from users
    Returns char value user typed in
*/
char getCharFromUser() { //Accounting for bad input and clearing the buffer, Function taken from interterm c++ assignments
    char input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

/*
    Handles int input from users; if non-int value is typed in, it'll take another input
    message: Message to reprompt with for another input
    Returns int value user typed in
*/
int getIntFromUser(string message)
{
    int input; //Declaring input inside the while loop would cause an error
    while(true) //Going to keep looping this until they enter valid input
    {
        cout << message;
        cin >> input;
        if(cin.fail()) //Accounting for non-double input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoring everything left in cin's buffer in case it messes with the next user input
            return input;
        }
    }
}

/*
    Handles double input from users; if non-double value is typed in, it'll take another input
    message: Message to reprompt with for another input
    Returns double value user typed in
*/
double getDoubleFromUser(string message)
{
    double input; //Declaring input inside the while loop would cause an error
    while(true) //Going to keep looping this until they enter valid input
    {
        cout << message;
        cin >> input;
        if(cin.fail()) //Accounting for non-double input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignoring everything left in cin's buffer in case it messes with the next user input
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