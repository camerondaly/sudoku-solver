#include<tuple>
#include<iostream>
#include<string>
using namespace std;

// A struct to return coordinates from FindEmptyCell
struct Location {
    int x;
    int y;
};

// Prints a sudoku puzzle with a grid for readability.
void PrintPuzzle(int sudoku[9][9]) {
    for (int i=0; i<9; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << "-----------------\n"; 
        }
        for (int j=0; j<9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << sudoku[i][j] << " ";
        }   
        cout << endl;
    }
    cout << endl;
}


// Gets the puzzle to be solved via a command line input from the user.
void InputPuzzle(int sudoku[9][9]) {
    cout << "\nEnter the Sudoku puzzle you would like to solve.\nInput the puzzle as a single line of numbers from left to right and top to bottom.\n    - Use 0 to indicate empty cells, and seperate all numbers by a single space.\n";
    cout << "    - Upon submission, the puzzle will be printed below for confirmation that it appears as intended:\n\n";
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            cin >> sudoku[i][j];
        }
    }
    int is_correct = 0;
    // ensures the user input their puzzle as intended
    while (is_correct == 0) {
        cout << "\n" << "You have entered:\n\n";
        PrintPuzzle(sudoku);
        cout << "Does the puzzle appear as intended?\n\nIf it appears correctly, enter 1, and the puzzle will be solved in an instant.\nIf it does not appear correctly, enter 0 to make an edit.\n";
        cout << "If the puzzle you have entered has no valid solution, the program will quit.\n";
        cin >> is_correct;
        if (is_correct == 1) {
            cout << "\n";
            break;
        }
        int x, y; cout << "Enter the coordinates of the cell to be changed seperated by a space on a 9X9 grid indexed at 0.\n";
        cin >> x >> y;
        cout << "Input the new value for this cell:\n";
        cin >> sudoku[x][y];
    }
}

// Returns the coordinates (as a struct called "Location") of an empty cell. Returns Location {9, 9} if all cells are full. 
Location FindEmptyCell(int sudoku[9][9]) {
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (sudoku[i][j] == 0) {
                Location coordinates {i, j};
                return coordinates;
            }
        }
    }
    return Location {9, 9};
}

// For the current number being guessed at the current cell, checks whether this is valid for the row. 
bool CheckRow (int sudoku[9][9], int num_guess, int x, int y) {
    for (int i=0; i<9; i++) {
        if (sudoku[x][i] == num_guess && i != y) {
            return false;
        }
    }
    return true;
}

// The same for a column --
bool CheckCol (int sudoku[9][9], int num_guess, int x, int y) {
    for (int i=0; i<9; i++) {
        if (sudoku[i][y] == num_guess && i != x) {
            return false;
        }
    }
    return true;
}

// Checks whether the current guess appears again inside the "box" our current cell is in.
bool CheckBox (int sudoku[9][9], int num_guess, int x, int y) {
    int x_box = x / 3;
    int y_box = y / 3;
    for (int i = x_box * 3; i < x_box * 3 + 3; i++) {
        for (int j = y_box * 3; j < y_box * 3 + 3; j++) {
            if (sudoku[i][j] == num_guess && (i != x && j != y)) {
                return false;
            }
        }
    }
    return true;
}

// Checks row and col and box for a repeat of the guess. Returns false when invalid. 
bool ValidGuess (int sudoku[9][9], int num_guess, int x, int y) {
    return (CheckRow(sudoku, num_guess, x, y) && CheckCol(sudoku, num_guess, x, y) && CheckBox(sudoku, num_guess, x, y));
}

// Guesses numbers at empty cells. Recursively calls itself until base case is reached: FindEmptyCell returns 9, 9.
bool Solver (int sudoku[9][9]) {
    Location coordinates = FindEmptyCell(sudoku);
    int x = coordinates.x;
    int y = coordinates.y;
    if (x == 9 && y == 9) {
        return true;
    }
    for (int guess = 1; guess < 10; guess++) {
        if (ValidGuess(sudoku, guess, x, y) == true) {
            sudoku[x][y] = guess;
            if (Solver(sudoku) == true) {
                return true;
            }
            // Backtracks here if the sudoku is not solved, deleting the value at x, y.
            sudoku[x][y] = 0;
        }
    }
    return false;
}

// Main. Calls for input. Uses this puzzle in Solver. Prints the solved sudoku once Solver returns true.
int main () {
    int done = 0;
    int sudoku[9][9];
    InputPuzzle(sudoku);
    if (Solver(sudoku) == true) {
        cout << "Ta-da! Your puzzle's solution is as follows:\n\n";
        PrintPuzzle(sudoku);
        int done;
        cout << "Press CTRL + C to exit.\n";
        cin >> done;
        if (done == 1) {
            return true;
        }
    }
}
