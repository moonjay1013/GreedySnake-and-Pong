#include "include/games.h"

int main() {
    cout << "choose one game to play" << endl;
    cout << "a -- Greedy Snake" << endl;
    cout << "b -- Box" << endl;
    switch (_getch()) {
        case 'a':
            Setup();
            while (!gameOver){
                Draw();
                Input();
                Logic();

//        _sleep(300);
                Sleep(300);
            }
            break;
        case 'b':
            cGameManager c(40, 20);
            while (!c.getStatus()){
                c.Draw();
                c.Input();
                c.Logic();
                Sleep(300);
            }
            break;
    }

    return 0;
}
