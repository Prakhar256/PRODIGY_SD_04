#include <iostream>
using namespace std;
const int N = 9;

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}
bool isSafe(int grid[N][N], int row, int col, int num) {

    // Check if 'num' is not present in the current row and column
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    // Check if 'num' is not present in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to find an empty position in the grid
bool findEmptyPosition(int grid[N][N], int& row, int& col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there are no empty positions, the puzzle is solved
    if (!findEmptyPosition(grid, row, col))
        return true;

    // Try placing numbers 1 to 9 in the empty position
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // Place the number if it's safe
            grid[row][col] = num;

            // Recursively solve the rest of the puzzle
            if (solveSudoku(grid))
                return true;

            // If placing 'num' at the current position doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // No number can be placed at the current position
    return false;
}

int main() {
    int grid[N][N];

    // Input the Sudoku puzzle (0 represents empty cells)
    cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            cin >> grid[row][col];

    // Solve the Sudoku puzzle
    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}
