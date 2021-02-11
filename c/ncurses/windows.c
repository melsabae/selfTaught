#include <ncurses.h>

int main(int argc, char **argv)
{
  (void) argc;
  (void) argv;
  initscr();
  noecho();

  char pressed = 0;

  mvprintw(10, 10, "ahoy, matey!");

  while (1) {
    pressed = getch();
    if (27 == pressed) {
      break;
    }
    else {
      pressed++;
    }

    mvprintw(0, 0, "%-3.d", pressed);

    refresh();
  }

  endwin();
  return 0;
}
