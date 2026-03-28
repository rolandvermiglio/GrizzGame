#include <ncurses.h>
#include <chrono>
#include <string>
#include <music.h>

struct Player {
    int current_health;
    int max_health;
};

class Enemy {
public:
    std::string name;
    float health;

};

int main() {
    initscr();           // start ncurses
    cbreak();            // don't wait for enter
    noecho();            // don't print keypresses
    keypad(stdscr, TRUE);
    timeout(0);          // non-blocking input (crucial for rhythm)
    start_color();

    // colors
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // hit
    init_pair(2, COLOR_RED, COLOR_BLACK);    // miss
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // UI

    attron(COLOR_PAIR(3));
    mvprintw(5, 10, "=== GRIZZGAME ===");
    attroff(COLOR_PAIR(3));

    mvprintw(7, 10, "Your HP: [##########]");
    mvprintw(9, 10, "Enemy: Goblin  HP: [##########]");
    mvprintw(13, 10, ">> [ ] [ ] [X] [ ] [X] [ ] <<");
    mvprintw(15, 10, "Hit SPACE on the X's!");
    mvprintw(17, 10, "Press Q to quit");

    refresh();

    int ch = 0;
    while ((ch = getch()) != 'q'){
        if (ch == 32) { //32 is space
            break;
        }
    }


    endwin(); // cleanup
    return 0;
}