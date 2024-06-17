//
// Created by moonjay on 2024/5/12.
//
#include "include/games.h"


cBall::cBall(int posX, int posY){
    originalX = posX;
    originalY = posY;
    x = posX;
    y = posY;
    direction = STOP;
}

void cBall::Reset(){
    x = originalX;
    y = originalY;
    direction = STOP;
}

void cBall::changeDirection(eDir d){
    direction = d;
}

void cBall::randomDirection(){
    direction = (eDir) (rand() % 6 + 1);
}

inline int cBall::getX() { return x; }
inline int cBall::getY() { return y; }
inline eDir cBall::getDirection() { return direction; }

void cBall::Move(){
    switch (direction) {
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP_LEFT:
            y--; x--;
            break;
        case DOWN_LEFT:
            y++; x--;
            break;
        case UP_RIGHT:
            y--; x++;
            break;
        case DOWN_RIGHT:
            y++; x++;
            break;
        default:
            break;

    }
}


cPaddle::cPaddle() { x = y = 0; }

cPaddle::cPaddle(int posX, int posY) : cPaddle() {
    originalX = posX;
    originalY = posY;
    x = posX;
    y = posY;
}

void cPaddle::Reset() {
    x = originalX;
    y = originalY;
}

inline int cPaddle::getX() { return x; }
inline int cPaddle::getY() { return y; }
inline void cPaddle::moveUp() { y--; }
inline void cPaddle::moveDown() { y++; }

cGameManager::cGameManager(int w, int h) {
    srand(time(NULL));
    quit = false;
    up1 = 'w'; up2 = 'i';
    down1 = 's'; down2 = 'k';
    score1 = score2 =0;
    width = w; height = h;
    ball = new cBall(w/2, h/2);
    player1 = new cPaddle(1, h/2-3);
    player2 = new cPaddle(w-2, h/2-3);
}

cGameManager::~cGameManager() {
    delete ball, player1, player1;
}

bool cGameManager::getStatus() {
    return quit;
}

void cGameManager::scoreUp(cPaddle *player) {
    if(player == player1) score1++;
    else if(player == player2) score2++;

    ball->Reset();
    player1->Reset();
    player2->Reset();
}

void cGameManager::Draw() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    for (int i = 0; i < width+2; i++) cout << "\u2593";  // Top wall
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++){
           int ballx = ball->getX();
           int bally = ball->getY();
           int player1x = player1->getX();
           int player1y = player1->getY();
           int player2x = player2->getX();
           int player2y = player2->getY();

           if (j == 0 || j == width) cout << "\u2593";

           if (ballx == j && bally ==i) cout << "\u25CB"; //ball

           else if (player1x == j && player1y == i) cout << "\u2588"; // player1
           else if (player1x == j && player1y+1 == i) cout << "\u2588"; // player1
           else if (player1x == j && player1y+2 == i) cout << "\u2588"; // player1
           else if (player1x == j && player1y+3 == i) cout << "\u2588"; // player1

           else if (player2x == j && player2y == i) cout << "\u2588"; // player2
           else if (player2x == j && player2y+1 == i) cout << "\u2588"; // player2
           else if (player2x == j && player2y+2 == i) cout << "\u2588"; // player2
           else if (player2x == j && player2y+3 == i) cout << "\u2588"; // player2
           else cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++) cout << "\u2593";  // bottom wall

    cout << endl;

    cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
}

void cGameManager::Input() {
    ball->Move();

    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player1y = player1->getY();
    int player2x = player2->getX();
    int player2y = player2->getY();

    if(_kbhit()){
        char current = _getch();
        if (current == up1)
            if(player1y > 0) player1->moveUp();
        if (current == up2)
            if(player2y > 0) player2->moveUp();
        if (current == down1)  // player have 4 segments
            if(player1y+4 < height) player1->moveDown();
        if (current == down2)
            if(player2y+4 < height) player2->moveDown();

        if (ball->getDirection() == STOP) ball->randomDirection();

        if (current == 'q') quit = true;
    }
}

void cGameManager::Logic() {
    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player1y = player1->getY();
    int player2x = player2->getX();
    int player2y = player2->getY();

    for (int i = 0; i < 4; i++) {
        if (ballx == player1x + 1 && bally == player1y + i)  // player1 hit the ball  (on the left)
            ball->changeDirection((eDir) ((rand() % 3) + 4));  // [0, 1, 2] + 4 --> [4, 5, 6] -- > RIGHT
        if (ballx == player2x - 1 && bally == player2y + i)  // player2 hit the ball  (on the right)
            ball->changeDirection((eDir) ((rand() % 3) + 1));  // [0, 1, 2] + 1 --> [1, 2, 3] -- > LEFT

        if (bally == height - 1) // ball hit the bottom wall
            ball->changeDirection(ball->getDirection() == DOWN_RIGHT ? UP_RIGHT : UP_LEFT);

        if (bally == 1) // ball hit the top wall
            ball->changeDirection(ball->getDirection() == UP_RIGHT ? DOWN_RIGHT : DOWN_LEFT);

        if (ballx == width - 1)  // ball hit the right wall
            scoreUp(player1);

        if (ballx == 1)  // ball hit the right wall
            scoreUp(player2);
    }

}