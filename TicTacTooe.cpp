#include <iostream>
#include <ctype.h>  // 'toupper' function
#include <conio.h>
#include <time.h>
#include <Windows.h>

using namespace std;

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard(){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            board[i][j] = ' ';  // player or computer
}

void printBoard(){
    /*
     * X|   |
     *  | X |
     * O| O | X
     * */
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2];
    cout << "\n--|---|--\n";
    cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2];
    cout << "\n--|---|--\n";
    cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

int checkFreeSpaces(){
    int freeSpaces = 9;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (board[i][j] != ' ') freeSpaces--;
        }
    }
    return freeSpaces;
}

void playerMove(){
    int num_row, num_col;

    do{
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 5});
        cout << "Enter row #(1-3): " << endl;
        cin >> num_row;
        num_row--;  // row index begin with 0
        cout << "Enter column #(1-3): " << endl;
        cin >> num_col;
        num_col--;

        if(board[num_row][num_col] != ' ') cout << "Invalid Move !!!" << endl;
        else{
            board[num_row][num_col] = PLAYER;
            break;
        }
    } while (board[num_row][num_col] != ' ');
}

void printWinner(char winner){
    if(winner == PLAYER) cout << "YOU WIN!!!";
    else if(winner == COMPUTER) cout << "YOU LOSE!!!";
    else cout << "It's a TIE";
}

void computerMove(){
    // creates a SEED based on current time
    srand(time(0));
    int x, y;
    if(checkFreeSpaces() > 0){
        do{
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        board[x][y] = COMPUTER;
    } else{
        printWinner(' ');
    }
}

char checkWinner(){
    // check rows
    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }

    // check columns
    for(int j = 0; j < 3; j++){
        if(board[0][j] == board[1][j] && board[0][j] == board[2][j])
            return board[0][j];
    }

    // check diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];
    else if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return board[0][2];

    return ' ';
}

int run_game() {
    char winner;
    char response;
    do{
        winner = ' ';
        response = ' ';
        resetBoard();

        while(checkFreeSpaces() != 0){
            printBoard();

            playerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0)  // game over
                break;

            computerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0)  // game over
                break;
        }
        printBoard();
        printWinner(winner);

        cout << " Would you like to play again? (Y/N): ";
        response = toupper(_getch());
    } while (response == 'Y');

    cout << "Thanks for playing!" << endl;
    return 0;
}
