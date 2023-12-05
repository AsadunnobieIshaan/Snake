//
// Created by ISHAAN on 10/16/2023.
//
#include <iostream>
#include <conio.h>
#include "../lib/Screen.cpp"

using namespace std;

class Game {
private:
    int screenSIZE1, screenSIZE2;
    char fh;
    char ch;
public:
    void GameLoop();
};


void Game::GameLoop() {
    {
        cout << "your game size" << endl;
        cin >> screenSIZE1 >> screenSIZE2;
        ch = '\0';
//        screenSIZE1 = 50;
//        screenSIZE2 = 500;
        Screen screen(screenSIZE1, screenSIZE2);
        screen.Print_screen();
        while (true) {
            if (kbhit()) {
                ch = getch();
                break;
            }
        }
//        int* foodloc = screen.giveFoodLocation();
        while (true) {

            if (kbhit()) {
                ch = getch();
            }

            system("cls");
            if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
                fh = ch;
                screen.moveSnake(fh);
            } else if (ch == 'k') {
                break;
            }
            screen.Print_screen();


            screen.Sleep();


        }
    }
}