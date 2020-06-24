#include <iostream>

#include "Snake1D.h"
#include "SnakeVectors.h"

using namespace std;

void aboutMenu() {
    int key = 0;

    // Clear screen and draws about screen
    system("cls");
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout <<"======================================================\nMEET THE CREW\n=======================================================\n\n";
                
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout <<"STANLLY: LEAD PROGRAMMER AND DEBUG TESTER/FIXER\nPROGRAMMER OF 1D ARRAY VER\n\n";

    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    cout << "GADTARDI: ORGANIZER, DOCUMENTATION AND QUALITY ASSURANCE\n\n";

    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    cout << "MIKA: SECONDARY PROGRAMMER WHO STRIVES TO WIN AGAINST AI\nPROGRAMMER OF VECTOR VER\n\n";
        
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << "=======================================================\n";

    SetConsoleTextAttribute(h, 12 | FOREGROUND_INTENSITY);
    cout << ">>> BACK";

    // Keeps the game paused till Enter is pressed
    while(key != 13) {
        key = getch();
    }   
            
    // Clear the screen then show the main menu
    system("cls");
}

void controls() {
    int key = 0;

    // Clear screen and draws control scheme screen
    system("cls");

    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << "=============================================\nCONTROLS\n=============================================\n\n";

    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "USE THE ";
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    cout << "WASD ";
            
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "KEYS TO MOVE THE SNAKE\nPRESSING"; 
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED);
    cout << " X"; 
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << " WILL QUIT THE GAME\n";

    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << "\n=============================================\n";

    SetConsoleTextAttribute(h, 12 | FOREGROUND_INTENSITY);
    cout << ">>> BACK";

    // Keeps the game paused till Enter is pressed
    while(key != 13) {
        key = getch();
    }   
            
    // Clear the screen then show the main menu
    system("cls");
}

void showMenu() {
    system("cls");
    // Initializes the Board
    int index = 1, key = 0;
    
    // key 13 = enter button
    while(key != 13){
        // Draws the start screen with different colors
        ClearScreen();
        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        cout<<"=================================\nSNAKE GAME\n=================================\n";
        
        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        // if the current option is selected, change color to red to indicate selection
        if(index == 1){
            SetConsoleTextAttribute(h, 12 | FOREGROUND_INTENSITY);
            }
        cout << "START 1D ARRAY VERSION\n";

        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        // if the current option is selected, change color to red to indicate selection
        if(index == 2){
            SetConsoleTextAttribute(h, 12 | FOREGROUND_INTENSITY);
            }
        cout << "START VECTOR VERSION\n";
        
        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        // if the current option is selected, change color to red to indicate selection
        if(index == 3){
            SetConsoleTextAttribute(h, 12 | FOREGROUND_INTENSITY);
            }
        cout  << "CONTROLS\n";

        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        // if the current option is selected, change color to red to indicate selection
        if(index == 4){
            SetConsoleTextAttribute(h, 12 | FOREGROUND_INTENSITY);
            }
        cout << "ABOUT\n";

        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        // if the current option is selected, change color to red to indicate selection
        if(index == 5){
            SetConsoleTextAttribute(h, 12 | FOREGROUND_INTENSITY);
            }
        cout << "EXIT\n";

        // Menu footer with custom colors and message
        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        cout<< "\n=================================\nBROUGHT TO YOU BY ";
        SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "GOOMERS INC.";
        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        cout << "\nUSE THE ";
        SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        cout << "ARROW KEYS ";
        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        cout << "TO NAVIGATE\n";
        SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "ENTER"; 
        SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
        cout << " TO SELECT AN OPTION\n=================================\n";

        // Switch statement to figure out whether the cursor is moved
        key = getch();
        switch(key) {
            case 80:
                index++;
                break;
            case 72:
                index--;
                break;
        }

        // Switch statement that governs the selection to make sure it loops instead of brekaing
        switch(index) {
            case 6:
                index = 1;
                break;
            case 0:
                index = 5;
                break;
        }
    }

    // Switch statement that chooses which part of the program to execute
    switch(index) {
        case 1:
            // Main game loop
            game();  
            showMenu();
            break;
        case 2:
            VectorGame();
            showMenu();
            break;
        case 3:
            controls();
            showMenu();
            break;
        case 4:
            aboutMenu();
            showMenu();
            break;
        case 5:
            // Return ends the function and exits the program
            return;
    }
}
