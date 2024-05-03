#include <iostream>
#include <unistd.h>
#include <signal.h> 
#include <stdlib.h>
#include <ncurses.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw() {
    clear();
    for (int i = 0; i < width+2; i++)
        printw("#");
    printw("\n");

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            if (j == 0)
                printw("#");
            if (i == y && j == x)
                printw("O");
            else if (i == fruitY && j == fruitX)
                printw("F");            
            else {
                bool prnt = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printw("o");
                        prnt = true;
                    }
                }
                if (!prnt)
                   printw(" ");
                
            }
            if (j == width-1)
                printw("#");
            
        }
        printw("\n");
    }

    for (int i = 0; i < width+2; i++)
        printw("#");
    printw("\n");
    printw("Score:%d\n", score);
    refresh();
        
}

void Input() {
    int ch = wgetch(stdscr);
    if (ch != ERR) {
        switch (ch) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;    
    default:
        break;
    }
    if (x < 0)
        x = width - 1;
    if (x >= width)
        x = 0;
    if (y < 0)
        y = height - 1;
    if (y >= height)
        y = 0;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    
}


void SigIntHandler(int sig) {
    gameOver = true;
    printw("\nReceived SIGINT. Exiting...\n");
}

int main() {
    initscr();
    cbreak();              
    noecho();               
    keypad(stdscr, TRUE);   
    nodelay(stdscr, TRUE);
    signal(SIGINT, SigIntHandler);
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(100000);
    }
    endwin();
    return 0;
}