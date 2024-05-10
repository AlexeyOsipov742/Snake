#pragma once

#include <iostream>
#include <unistd.h>
#include <signal.h> 
#include <stdlib.h>
#include <ncurses.h>
#include "Snake.hpp"

class View {
public:
    static void Draw(Snake& snake) {
        clear();
        int width = snake.width;
        int height = snake.height;
        int x = snake.x;
        int y = snake.y;
        int fruitX = snake.fruitX;
        int fruitY = snake.fruitY;
        int score = snake.score;
        int nTail = snake.nTail;
        int* tailX = snake.tailX;
        int* tailY = snake.tailY;

        for (int i = 0; i < width + 2; i++)
            printw("#");
        printw("\n");

        for (int i = 0; i < height; i++) {
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
                if (j == width - 1)
                    printw("#");

            }
            printw("\n");
        }

        for (int i = 0; i < width + 2; i++)
            printw("#");
        printw("\n");
        printw("Score:%d\n", score);
        refresh();
    }

    static void Input(Snake& snake) {
        int ch = wgetch(stdscr);
        if (ch != ERR) {
            switch (ch) {
            case 'a':
                snake.dir = Snake::LEFT;
                break;
            case 'd':
                snake.dir = Snake::RIGHT;
                break;
            case 'w':
                snake.dir = Snake::UP;
                break;
            case 's':
                snake.dir = Snake::DOWN;
                break;
            case 'q':
                snake.gameOver = true;
                break;
            }
        }
    }

    static void Logic(Snake& snake) {
        snake.UpdatePosition();
    }
};
