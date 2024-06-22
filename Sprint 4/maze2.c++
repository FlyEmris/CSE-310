#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_ROWS = 10;
const int MAX_COLS = 10;
const int NEW_MAX_ROWS = MAX_ROWS * 2;
const int NEW_MAX_COLS = MAX_COLS * 2;

char mazes[2][MAX_ROWS][MAX_COLS] = {
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

bool solveMaze(char maze[NEW_MAX_ROWS][NEW_MAX_COLS], int row, int col) {
    // Check boundary conditions and if cell is a wall
    if (row < 0 || col < 0 || row >= NEW_MAX_ROWS || col >= NEW_MAX_COLS || maze[row][col] == '#') {
        return false;
    }
    
    // Check if we have reached the exit
    if (row == NEW_MAX_ROWS - 2 && col == NEW_MAX_COLS - 2) {
        maze[row][col] = 'X'; // Mark the exit
        return true;
    }
    
    // Check if the current cell is a valid path
    if (maze[row][col] == ' ' || maze[row][col] == 'S') {
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

void printMaze(const char maze[NEW_MAX_ROWS][NEW_MAX_COLS]) {
    for (int i = 0; i < NEW_MAX_ROWS; i++) {
        for (int j = 0; j < NEW_MAX_COLS; j++) {
            std::cout << maze[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void combineMazes(const char maze1[MAX_ROWS][MAX_COLS], const char maze2[MAX_ROWS][MAX_COLS], char newMaze[NEW_MAX_ROWS][NEW_MAX_COLS]) {
    // Initialize the new maze with walls
    for (int i = 0; i < NEW_MAX_ROWS; i++) {
        for (int j = 0; j < NEW_MAX_COLS; j++) {
            newMaze[i][j] = '#';
        }
    }

    // Copy maze1 to the top left of newMaze
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            newMaze[i][j] = maze1[i][j];
        }
    }

    // Copy maze2 to the bottom right of newMaze
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            newMaze[i + MAX_ROWS][j + MAX_COLS] = maze2[i][j];
        }
    }

    // Add a clear connecting path between the two mazes
    for (int i = 0; i < MAX_ROWS; i++) {
        newMaze[MAX_ROWS + i][MAX_COLS - 1] = ' ';
    }
    for (int j = MAX_COLS - 1; j < MAX_COLS + 1; j++) {
        newMaze[MAX_ROWS - 1][j] = ' ';
    }
    for (int i = MAX_ROWS - 1; i < MAX_ROWS + 1; i++) {
        newMaze[i][MAX_COLS] = ' ';
    }
    for (int j = MAX_COLS; j < NEW_MAX_COLS; j++) {
        newMaze[MAX_ROWS][j] = ' ';
    }
}

int main() {
    srand(time(0));
    char newMaze[NEW_MAX_ROWS][NEW_MAX_COLS];
    
    combineMazes(mazes[0], mazes[1], newMaze);

    // Mark the start position
    newMaze[1][1] = 'S';
    
    std::cout << "Combined Maze:\n";
    printMaze(newMaze);

    if (solveMaze(newMaze, 1, 1)) {
        std::cout << "\nSolved Maze:\n";
        printMaze(newMaze);
    } else {
        std::cout << "No solution found\n";
    }

    return 0;
}
