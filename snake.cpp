#include <iostream>
#include <conio.h>
#include <list>
#include <windows.h>
#include <algorithm>
#include <array>
using namespace std;


const int height = 30;
const int width = 50;
const int snake_lenght = 100;


const char wall = '#';
const char space = ' ';
const char snake_head = '%';
const char snake = '*';
const char fruit = 'X';
const char quit = 'q';

_SMALL_RECT rect;

int xfruit;
int yfruit;

int x, y;
int score;

int x_array[snake_lenght];
int y_array[snake_lenght];


const unsigned int speed = 70;

bool game_over;


enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void set_fruit(){
    xfruit = rand() %width;
    yfruit = rand() %height;
}

// function to initialise the game
void setup(){
    // Set console size
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = height + 10;
    rect.Right = width + 10;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(handle, 1, &rect);

    game_over = false;
    cout << game_over << endl;
    score = 0;
    x = width / 2;
    y = height / 2;
    dir = STOP;
    set_fruit();

    for(int i = 0; i < snake_lenght; i++){
        x_array[i] = snake_lenght + 1;
        y_array[i] = snake_lenght + 1;
    }
}


bool array_index(int line, int row){
    // function to return if part of snake body
    for(int i = 0; i < snake_lenght; i++){
        if ( x_array[i] == line && y_array[i] == row){
            return true;
        }
    }
    return false;
}

void print_array(){
    for(int i = 0; i < snake_lenght; i++){
        cout << x_array[i] << "-";
    }
    cout << endl;
    for(int i = 0; i < snake_lenght; i++){
        cout << y_array[i] << "-";
    }
}

// function to draw the board
void draw(){
    // Reset cursur Top left.
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), {0,0} );

    // top wall
    for (int i = 0; i < width + 2; i++){
        cout << wall;
    }
    cout << endl;

    for (int r = 0; r < height; r++){
        // left vertical wall
        cout << wall;

        // line
        for(int l = 0; l < width; l++){
            // check what to draw
            if (r == y && l == x){
                // snake head
                cout << snake_head;
            }
            else if(r == yfruit && l == xfruit && dir != STOP){
                cout << fruit;
            }
            else if(array_index(l, r) && dir != STOP){
                cout << snake;
            }
            else{
                cout << space;
            }
        }
        // Right vertical wall
        cout << wall << endl;
    }

    // bottom wall
    for (int i = 0; i < width + 2; i++){
        cout << wall;
    }
    cout << endl;
    cout << "Score: " << score << endl;
    cout << "Use " << quit << " for Quit." << endl;
    cout << "X:" << x << " Y:"<< y << endl;
    cout << endl;
}

// check for keyboard entry
void input(){
    if(_kbhit()){

        switch(_getch()){
        case 's':
            dir = LEFT;
            break;
        case 75:
            dir = LEFT;
            break;

        case 'f':
            dir = RIGHT ;
            break;
        case 77:
            dir = RIGHT;
            break;

        case 'e':
            dir = DOWN;
            break;
        case 72:
            dir = DOWN;
            break;

        case 'd':
            dir = UP;
            break;
        case 80:
            dir = UP;
            break;

        case quit:
            game_over = true;
            break;
        }
    }
}

int logic(){
    // move snake head in the board
    switch(dir){
    case LEFT:
        x = x - 1;
        break;

    case RIGHT:
        x = x + 1;
        break;

    case UP:
        y = y + 1;
        break;

    case DOWN:
        y = y - 1;
    }

    for(int i = 0; i < snake_lenght; i++){
        x_array[i] = x_array[i + 1];
        y_array[i] = y_array[i + 1];
    }

    if (x < 0 || x >= width || y < 0 || y >= height ){
        cout << "outside board" << endl;

        game_over = true;
    }
    else if(x == xfruit && y == yfruit){
        cout << "fruit found" << endl;
        score = score + 100;
        do {
            set_fruit();
        }while(array_index(xfruit, yfruit));

    }
    else if((array_index(x, y)) && dir !=STOP){
        cout << "Hit Snake" << endl;
        game_over = true;
    }

    x_array[snake_lenght - 1] = x;
    y_array[snake_lenght - 1] = y;

}

int main(){
    setup();
    cout  << "Game over value: " << game_over <<  endl;
    while(!game_over){
        if (dir != STOP){  //Start score only when it move
            score = score + 1;
        }
        input();
        logic();
        draw();
        Sleep(speed);

        //game_over = true;
    }

    if(x == xfruit && y == yfruit){
       cout << "Game Over, YOU WIN!! Score is: " << score << endl;
    }
    else{
        cout << "Game Over, try again!" << endl;
    }
    return 0;
}
