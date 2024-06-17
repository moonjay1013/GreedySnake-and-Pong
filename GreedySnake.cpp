//
// Created by moonjay on 2024/5/8.
//

#include "include/games.h"

/*
 * Ooooo
 *
 * ooooO
 *
 * o
 * oooO
 * */
bool gameOver = true;  // global variable
// if gameOver not declaration in *.h, when main.cpp use gameOver, need use 'extern'

const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];  // eat fruit tail++
int nTail;

enum eDirection { STOP1=0, LEFT1, RIGHT1, UP1, DOWN1};
eDirection dir;

void Setup(){
    gameOver = false;
    dir = STOP1;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void Draw(){
//    system("cls"); // clear the console screen    Linux -- System("clear");
// remove the flickering (it just takes your cursor to first word of top line and starts to overwrite the text so the flickering just stops.)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    for (int i = 0; i < width+1; i++) cout << "#";  // Top wall
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            if (j ==0 || j == width-1) cout << "#";
            if (i == y && j == x) cout << "O";  // snake head
            else if (i == fruitY && j == fruitX) cout << "F";
            else{
                bool print_tail = false;
                for (int k = 0; k < nTail; k++){  // snake tail
                    if(tailX[k] == j && tailY[k] == i){
                        cout << 'o';
                        print_tail = true;
                    }
                }
                if(!print_tail) cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width+1; i++) cout << "#";  // bottom wall

    cout << endl;
    cout << "Score:" << score;
}

void Input(){
    if (_kbhit()){
        switch (_getch()) {
            case 'a':
            case KEY_LEFT:
                dir = LEFT1;
                break;
            case 'd':
            case KEY_RIGHT:
                dir = RIGHT1;
                break;
            case 'w':
            case KEY_UP:
                dir = UP1;
                break;
            case 's':
            case KEY_DOWN:
                dir = DOWN1;
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }
}

void Logic(){
    // tail position
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case STOP1:
            break;
        case LEFT1:
            x--;
            break;
        case RIGHT1:
            x++;
            break;
        case UP1:
            y--;
            break;
        case DOWN1:
            y++;
            break;
        default:
            break;
    }
    if (x > width || x < 0 || y > height-1 || y < 0) gameOver = true;
    for (int i = 0; i < nTail; i++)  // eat itself
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    if (x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;

        nTail++;  // eat fruit
    }
}
