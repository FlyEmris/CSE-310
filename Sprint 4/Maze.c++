#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_ROWS = 10;
const int MAX_COLS = 10;

char mazes[3][MAX_ROWS][MAX_COLS] = {
    {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    },
    {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    }
};

bool solveMaze(char maze[MAX_ROWS][MAX_COLS], int row, int col) {
    // Check boundary conditions and if cell is a wall
    if (row < 0 || col < 0 || row >= MAX_ROWS || col >= MAX_COLS || maze[row][col] == '#') {
        return false;
    }
    
    // Check if we have reached the exit
    if (row == MAX_ROWS - 2 && col == MAX_COLS - 2) {
        maze[row][col] = 'X'; // Mark the exit
        return true;
    }
    
    // Check if the current cell is a valid path
    if (maze[row][col] == ' ') {
        maze[row][col] = 'X'; // Mark the current cell as visited

        // Recursively explore each direction
        if (solveMaze(maze, row + 1, col) || solveMaze(maze, row - 1, col) ||
            solveMaze(maze, row, col + 1) || solveMaze(maze, row, col - 1)) {
            return true;
        }

        maze[row][col] = ' '; // Mark the current cell as unvisited
    }
    return false;
}

void printMaze(const char maze[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            std::cout << maze[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    srand(time(0)); // Seed the random number generator
    int mazeIndex = rand() % 3; // Randomly select a maze
    char selectedMaze[MAX_ROWS][MAX_COLS];
    
    // Copy the selected maze to a new array to avoid modifying the original maze
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            selectedMaze[i][j] = mazes[mazeIndex][i][j];
        }
    }

    std::cout << "Selected Maze:\n";
    printMaze(selectedMaze);

    if (solveMaze(selectedMaze, 1, 1)) {
        std::cout << "\nSolved Maze:\n";
        printMaze(selectedMaze);
    } else {
        std::cout << "No solution found\n";
    }

    return 0;
}
