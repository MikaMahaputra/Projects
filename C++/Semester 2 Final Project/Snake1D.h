#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;

// Initialize game board of size 20x20
const int width = 40;
const int height = 20;

/* x and y (Coordinates of Snake Head),
fruitX and fruitY (Coordinates of fruit),
score (Game Score) */
int x, y, fruitX, fruitY, score;

// Coordinate List of tail
int tailX[100], tailY[100];

// Length of tail
int nTail;

enum Directons { STOP = 0, LEFT, RIGHT, UP, DOWN};
Directons dir;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

// Function sets cursor position to 0 in order to redraw the screen without flickering
void ClearScreen() {	
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(h, cursorPosition);
}

// Function that sets up the start of the program
void Setup() {
    system("cls");
    gameOver = false;
    dir = STOP;

    // Initialize snake x and y coordinates
    x = width / 2;
    y = height / 2;

    // Initialize fruit x and y coordinates
    fruitX = rand() % width;
    fruitY = rand() % height;

    // Initialize Score
    score = 0;

    // Hides Console cursor (No flashing between screen refreshes)
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 100;
    ci.bVisible = false;

    SetConsoleCursorInfo(h, &ci);
}

// Function that governs the drawing of the screen or "frames"
void Draw() {
    ClearScreen();

    for (int i = 0; i < width+1; i++) {
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "#";
    }
    cout << endl;
 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "#";
            } else if (i == y && j == x) {
                SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "O";
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            } else if (i == fruitY && j == fruitX) {
                SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "F";
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
            } else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        cout << "o";
                        print = true;
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    }
                }

                if (!print) {
                    cout << " ";
                }
            }
 
            if (j == width - 1) {
                cout << "#";
            }
            
        }
        cout << endl;
    }
 
    for (int i = 0; i < width+1; i++)
        cout << "#";
        
    cout << endl;
    
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "Score:" << score << endl;
}

//function to get the movement direction of snake using WASD and X for exit
void KeyInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if(dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
                if(dir != LEFT)
                    dir = RIGHT;
                break;
            case 'w':
                if(dir != DOWN)
                    dir = UP;
                break;
            case 's':
                if(dir != UP)
                    dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

// Function that governs the snake movement and food placement
void MovementAndFoodPlacement() {
    // set the previous coordinates
    int prevX = tailX[0];
    int prevY = tailY[0];

    // temporary variables to store coordinates to be updated
    int prev2X, prev2Y;

    // sets the first value in coordinate list as current coordinate
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    /* logic to control x and y coordinates
    based on control inputs */
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    // Lets the snake move between screens (exit left, reappear on right)
    if (x >= width) x = 1; else if (x <= 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    
    // Checks if the snake touches its tail/head
    for (int i = 0; i < nTail; i++){
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
    
    /* if Snake Head collides with Fruit, score +10
    spawn a new fruit, tail size +1*/
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

// Function that houses the game loop
void game() {
    Setup();
    // Clear screen and draws about screen
    system("cls");
    
    int key = 0;
    
    while (!gameOver) {
        Draw();
        KeyInput();
        MovementAndFoodPlacement();
        Sleep(75);
    }

    // Prints custom message with instructions
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    cout << "Press ";
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED);
    cout << "Enter ";
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    cout << "to Return to Main Menu";

    // Keeps the game paused till Enter is pressed
    while(key != 13) {
        key = getch();
    }

    // Clear the screen then show the main menu
    system("cls");
}
