#include "Snake.hpp"
#include "View.hpp"
#include "BotSnake.hpp"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL)); // Initialize random seed

    int width = 20;
    int height = 20;
    Snake snake(width, height);
    BotSnake bot(width, height);
    while (!snake.IsGameOver()) {
        //View::Draw(snake);
        //View::Input(snake);
        //View::Logic(snake);
        View::Draw(bot);
        View::Input(bot);
        View::Logic(bot);
        usleep(100000);
    }

    endwin();
    return 0;
}
