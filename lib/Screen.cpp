//
// Created by ISHAAN on 10/16/2023.
//
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <thread>
#include <string.h>
#include <random>
using namespace std;

class Screen {
private:
    int steps;
    int Width;
    int Height;
    char **arr;
    int **wall{};
    int **snakebody; // snakebody will be structures like snakebody = [[x,y],[x,y],[x,y]]
    int *snakehead;
    int *foodLoc;
    int snakeSize;
    int max_snakeSize;
    int *previousSnakeBody{};
    const char BACKGROUND_CHAR = ' ';
    const char SNAKE_BODY_CHAR = '#';
    const char SNAKE_HEAD_CHAR = '@';
    const char FOOD_CHAR = '*';
    const char BIG_FOOD_CHAR = 'O';
    const char WALL_CHAR = 'X';
    int fps = 10;
    const int TIME_BETWEEN_FRAMES_MILLI = 1000 / fps;
    int k;


public:
    Screen(int height, int width) {
        this-> k = 0;
        this->Height = height;
        this->Width = width;
        this->arr = new char *[height];
        this->max_snakeSize = (height - 2) * (width - 2);
        this->snakeSize = 1;
        this->snakebody = new int *[max_snakeSize];
        this->snakebody[0] = new int[2];
        snakebody[0][0] = height / 2;
        snakebody[0][1] = width / 2;
        snakehead = new int[2];
        snakehead[0] = height / 2;
        snakehead[1] = width / 2;
        this->steps = 1;
        this->foodLoc = giveFoodLocation();


        for (int i = 0; i < height; i++) {
            this->arr[i] = new char[width];
            for (int j = 0; j < width; j++) {
                this->arr[i][j] = BACKGROUND_CHAR;
            }
        }
        //initializing the borders
        for (int i = 0; i < height; i++) {
            this->arr[i][0] = WALL_CHAR;
            this->arr[i][width - 1] = WALL_CHAR;
        }
        for (int i = 0; i < width; i++) {
            this->arr[0][i] = WALL_CHAR;
            this->arr[height - 1][i] = WALL_CHAR;
        }
        setFoodPixel(foodLoc[0], foodLoc[1]);
        setSnakeHeadPixel(snakehead[0], snakehead[1]);


    }

    void write_char_array(std::ostream& os, const char* string,int strlength) {
        // faster than an ostream_iterator and std::copy
        os.write(string, strlength);
    }


    void Print_screen() {
//        for (int i = 0; i < Height; i++) {
//            for (int j = 0; j < Width; j++) {
////                printf("%c",arr[i][j]),
////                printf("%s","  ");
//                _putchar_nolock(arr[i][j]);
//                _putchar_nolock(' ');
//                _putchar_nolock(' ');
//            }
//            _putchar_nolock('\n');
////            printf("\n");
//        }

//        for (int i = 0; i < Height; i++) {
//            write_char_array(cout, arr[i], Width);
//            printf("\n");
//
//        }

        char *temp = new char[Height * (2 * (Width))+Height];

        /**
         *
         *  {{a ,b ,c },
         *  {d, e, f },
         *  {g, h , i }}
         *
         *
         *
         *
         *
         *
         */
        k =0;
        for (int i = 0; i < Height; i++) {
            for (int j = 0; j < Width; j++) {
                temp[k] = arr[i][j];
                k++;
                temp[k] = ' ';
                k++;
            }
            temp[k] = '\n';
            k++;
        }

//        int the_size_of_temp = (Height * (2 * (Width)) ) +Height;

        write_char_array(cout, temp, k);
//        write_char_array(cout, reinterpret_cast<const char *>(snakeSize), 1);
//        cout << the_size_of_temp << ' ' << k<<endl;
            printSNakeBOdyArray();
    }



    static int randomInt(int min, int max) {
        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> dist(min, max);
        return dist(mt);
    }

    int* giveFoodLocation()  {
        int *foodLocation = new int[2];

        foodLocation[0] = randomInt(1, Height - 2);
        foodLocation[1] = randomInt(1, Width - 2);

        return foodLocation;
    }

    void printSNakeBOdyArray(){
        for (int i = 0; i < steps; ++i) {
            cout << snakebody[i][0] << ' ' << snakebody[i][1] << ',';
        }
    }

    void reSetPixel(int x, int y) {
        arr[x][y] = BACKGROUND_CHAR;
    } //tail array size = snakesize -1

    void setSnakeHeadPixel(int x, int y) {
        arr[x][y] = SNAKE_HEAD_CHAR;
    }

    void setFoodPixel(int x, int y) {
        arr[x][y] = FOOD_CHAR;
    }

    void Sleep() {
        this_thread::sleep_for(chrono::milliseconds(TIME_BETWEEN_FRAMES_MILLI));
    }

    void gameOver(){
        cout << "GAME OVER" << endl;
        getch();
        exit(0);
    }
    void snakeBodyGrow(int* coord){
        snakebody[steps] = coord;
        steps++;
    }          //snakesize  -1                       //snakebody = [[x,y],[x,y],[x,y]]

    void moveSnake(char dir) {
        //dir 0 = w
        //dir 1 = a
        //dir 2 = s
        //dir 3 = d
        switch (dir) {
            case 'w':
                manipulateArray(new int[2]{snakehead[0] - 1, snakehead[1]});
                break;
            case 'a':
                manipulateArray(new int[2]{snakehead[0], snakehead[1] - 1});
                break;
            case 's':
                manipulateArray(new int[2]{snakehead[0] + 1, snakehead[1]});
                break;
            case 'd':
                manipulateArray(new int[2]{snakehead[0], snakehead[1] + 1});
                break;
            default:
                break;
        }
        reSetPixel(previousSnakeBody[0], previousSnakeBody[1]);
    }

    void manipulateArray(int *coord) { // coord = [x,y] //arr  = [x]
        int x = coord[0];
        int y = coord[1];
        if (arr[x][y] == FOOD_CHAR) {
            foodLoc = giveFoodLocation();
            setFoodPixel(foodLoc[0], foodLoc[1]);
            snakeSize++;
        }
        else if (arr[x][y] == WALL_CHAR || arr[x][y] == SNAKE_HEAD_CHAR) {
            gameOver();
        }
        snakeBodyGrow(coord);
        previousSnakeBody = snakebody[steps - snakeSize - 1];
        snakehead = coord;

        setSnakeHeadPixel(x, y);
    }


};

//
//int main(){
//
//    Screen s(10,10);
//    s.Print_screen();
//
//    return 0;
//}

