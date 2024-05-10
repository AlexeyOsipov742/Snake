#pragma once

#include <iostream>
#include <unistd.h>
#include <signal.h> 
#include <stdlib.h>
#include <ncurses.h>

class Snake {
protected:
    int x, y;
    int width, height;
    int fruitX, fruitY;
    int score;
    int* tailX;
    int* tailY;
    int nTail;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    Direction dir;
    bool gameOver;

public:
    Snake(int w, int h) : width(w), height(h) {
        x = width / 2;
        y = height / 2;
        tailX = new int[100];
        tailY = new int[100];
        nTail = 0;
        score = 0;
        gameOver = false;
        fruitX = rand() % width;
        fruitY = rand() % height;
        dir = STOP;
    }

    ~Snake() {
        delete[] tailX;
        delete[] tailY;
    }

    void UpdatePosition() {
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

    bool IsGameOver() {
        return gameOver;
    }

    friend class View;
};
