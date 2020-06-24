#include <conio.h>
#include <stdio.h> 
#include <ctime>
#include <vector>
#include <windows.h>

const int PLANEHEIGHT         = 20; //Height
const int PLANEWIDTH          = 50; //Width
const int INITIALSNAKELENGTH = 3; //SnakeLength
const int FPS   = 30;

#include <iostream>
using namespace std;

//Builds the snake
struct SnakeSegment
{
    SnakeSegment() {};
    SnakeSegment(  short x1, short y1 )
    {
        x = x1;
        y = y1;
    }
     short x;
     short y;
};

short snakeLength = INITIALSNAKELENGTH;
char lastDirection = 'd';
char lastlastDir = lastDirection;
std::vector< SnakeSegment > m_Snake;

short foodX;
short foodY;

char plane[ PLANEHEIGHT * PLANEWIDTH ];

void DisplayPlane();
void NormalisePlane();
void SnakeInit();
void FoodInit();
void Move();
void DeleteLastSnakeSegment();
bool HasEatenFood();

void WipeConsole();

bool Won();
bool Lost();


void VectorGame() {  
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 100;
    ci.bVisible = false;

    SetConsoleCursorInfo(h, &ci);

    srand( (int)time( NULL ) );
    snakeLength = INITIALSNAKELENGTH;

    SnakeInit();
    NormalisePlane();
    FoodInit();

    while(true) {
        for ( ;; )
        {
            clock_t start;
            double time = 0.0;
            start = clock();

            while( time < 1.0 / FPS )
            {
                time = ( clock() - start ) / (double)CLOCKS_PER_SEC;
            }

            if( HasEatenFood() )
            {
                snakeLength++; 
                SnakeSegment segment( foodX,foodY );
                m_Snake.push_back( segment ); //Adds a new snake part when we eat the food
                FoodInit(); //Spawns a new food
            }

            WipeConsole();
            DisplayPlane();
            Move();

            if( Won() )
            {
                printf( "Congratulation, you have won!\n" );
                break;
            }
            if( Lost() )
            {
                printf( "You have lost!\n" );
                break;
            }
        }
        system( "PAUSE" );
        break;
    }
}

void DisplayPlane()
{
    for(  short i = 0; i < PLANEWIDTH + 2; i++ ) printf( "%c", '/' );     printf( "\n" );

    for(  short y = 0; y < PLANEHEIGHT; y++ )
    {
        printf( "%c", '/' ); 
        for(  short x = 0; x < PLANEWIDTH; x++ )
        {
            printf( "%c",plane[ y * PLANEWIDTH + x ] ); //stuff: X = food, O     = snake segment, ' ' = blank space
        }
        printf( "%c\n",'/' ); 
    }

    for(  short i = 0; i < PLANEWIDTH + 2; i++ ) printf( "%c",'/' );     printf( "\n" );
}

void NormalisePlane()
{
    for(  short x = 0; x < PLANEWIDTH; x++ )
    {
        for(  short y = 0; y < PLANEHEIGHT; y++ )
        {
            plane[ y * PLANEWIDTH + x ] = ' ' ; //Sets all plane cells to ' ' 
        }
    }
}

void SnakeInit() //Spawns snake in the first row of plane
{ 
    for(  short i = 0; i < snakeLength; i++ )
    {
        SnakeSegment segment;
        segment.x = i;
        segment.y = 0;
        m_Snake.push_back( segment );
        plane[ i ] = 'O';
    }
}

void FoodInit()
{
    foodX = rand() % PLANEWIDTH;
    foodY = rand() % PLANEHEIGHT;

    while ( plane[ foodY * PLANEWIDTH + foodX ] != ' ' ) //New food has to be spawned at an empty cell
    {
        foodX = rand() % PLANEWIDTH;
        foodY = rand() % PLANEHEIGHT;
    }

    plane[ foodY * PLANEWIDTH + foodX ] = 'X';
}

//Notes to Stanlly:
//Tried to Implement a similiar code to yours so the snake wont die doing a 180 noscope
//Doesnt work so i reverted it back to normal
void Move()
{ 
    if( _kbhit() ) //Can get keyboard input without pressing Enter key
            {
                lastlastDir = lastDirection;
                lastDirection = _getch();
            }

    SnakeSegment segment = m_Snake.at( m_Snake.size() - 1 ); 

    if( lastDirection == 'd' && lastlastDir != 'a' ) //Snake moves to the right
    {
        segment.x++;
        m_Snake.push_back( segment );
        plane[ segment.y * PLANEWIDTH + segment.x ] = 'O';

        DeleteLastSnakeSegment();
    }
    else if( lastDirection == 's' && lastlastDir != 'w' ) //Snake moves down
    {
        segment.y++;
        m_Snake.push_back( segment );
        plane[ segment.y * PLANEWIDTH + segment.x ] = 'O';

        DeleteLastSnakeSegment();
    }
    else if(lastDirection == 'a' && lastlastDir != 'd' ) //Snake moves to the left
    {
        segment.x--;
        m_Snake.push_back( segment );
        plane[ segment.y * PLANEWIDTH + segment.x ] = 'O';

        DeleteLastSnakeSegment();
    }
    else if( lastDirection == 'w' && lastlastDir != 's' ) //Snake moves up
    {
        segment.y--;
        m_Snake.push_back( segment );
        plane[ segment.y * PLANEWIDTH + segment.x ] = 'O';

        DeleteLastSnakeSegment();
    }
}


void DeleteLastSnakeSegment()
{
    SnakeSegment temp = m_Snake[ 0 ]; 
    plane[ temp.y * PLANEWIDTH + temp.x ] = ' ';
    m_Snake.erase( m_Snake.begin() );
}

bool HasEatenFood()
{
    SnakeSegment segment = m_Snake.at( m_Snake.size() - 1 ); //First element of snake
    SnakeSegment food;
    food.x = foodX;
    food.y = foodY;
    return segment.x == food.x && segment.y == food.y; //Snake's head collides with food
}

void WipeConsole()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), cursorPosition);
}

bool Won()
{
    bool space = false;
    for(  short x = 0; x < PLANEWIDTH; x++ )
    {
        for( short y = 0; y < PLANEHEIGHT; y++ )
        {
            if( plane[ y * PLANEWIDTH + x ] == ' ' ) //If none of the cells are empty we'll win the game
            {
                space = true;
                break;
            }
        }
    }
    return !space;
}

bool Lost()
{
    SnakeSegment segment = m_Snake.at( m_Snake.size() - 1 ); //First element of snake
	//Makes the wall solid
    if( segment.x < 0 || segment.x > PLANEWIDTH - 1 ||
        segment.y < 0 || segment.y > PLANEHEIGHT - 1 ) return true; //if colides with boundries
    
    for( short i = 0; i < m_Snake.size() - 1; i++ ) //Snake collides with itself
    {
        SnakeSegment temp = m_Snake[ i ];
        if( temp.x == segment.x && temp.y == segment.y ) return true;
    }

    return false;
}
//Final note to Stanlly:
//The snake can pass horizontally but cant pass vertically
