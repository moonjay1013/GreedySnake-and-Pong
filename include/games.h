//
// Created by moonjay on 2024/5/8.
//

#ifndef GREEDYSNAKE_GAMES_H
#define GREEDYSNAKE_GAMES_H

#include <iostream>
#include <conio.h>  // Console Input/Output
#include <time.h>
#include <Windows.h>

using namespace std;

// greedy snake
#define KEY_UP 72  // use small keyboard arrow keys
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

extern bool gameOver;

extern void Setup();

extern void Draw();

extern void Input();

extern void Logic();

// Pong
enum eDir {STOP=0, LEFT=1, UP_LEFT=2, DOWN_LEFT=3, RIGHT=4, UP_RIGHT=5, DOWN_RIGHT=6};

class cBall{
private:
    int  x, y;
    int originalX, originalY;
    eDir direction;
public:
    cBall(int posX, int posY);

    void Reset();

    void changeDirection(eDir d);
    void randomDirection();

    inline int getX();
    inline int getY();
    inline eDir getDirection();

    void Move();


    friend ostream & operator<<(ostream & o, cBall c){
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return o;
    }
};

class cPaddle{
private:
    int x, y;
    int originalX, originalY;
public:
    cPaddle();
    cPaddle(int posX, int posY);

    void Reset();

    inline int getX();
    inline int getY();
    inline void moveUp();
    inline void moveDown();

    friend ostream & operator<<(ostream & o, cPaddle c){
        o << "Ball [" << c.x << "," << c.y << "]";
        return o;
    }
};

class cGameManager{
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall * ball;
    cPaddle * player1;
    cPaddle * player2;
public:
    cGameManager(int w, int h);
    ~cGameManager();

    bool getStatus();

    void scoreUp(cPaddle * player);

    void Draw();

    void Input();

    void Logic();

};

#endif //GREEDYSNAKE_GAMES_H
