#include "./brick_game/tetris/tetris.h"
#include "./gui/cli/brick_game_frontend.h"

void tetris_game();

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(40);
  srand((unsigned int)time(NULL));

  print_overlay();
  tetris_game();

  endwin();
  return 0;
}

void tetris_game() {
  GameInfo_t gameInfo;
  infoInit(&gameInfo);
  change_GameInfo_t(&gameInfo);

  game_loop(NULL, -1);

  int state = -1;

  while (state != EXIT_STATE) {
    UserAction_t sig = get_signal(getch());
    state = game_loop(&gameInfo, sig);
    updateCurrentState();
  }

  print_banner(&gameInfo);

  while (1) {
    UserAction_t sig = get_signal(getch());
    if (sig == Terminate) {
      break;
    }
  }

  infoFree(&gameInfo);
}