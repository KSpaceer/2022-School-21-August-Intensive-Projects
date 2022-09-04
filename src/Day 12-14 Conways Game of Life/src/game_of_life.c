#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define SQUARE 2000

#define SLOWEST 5000000
#define FASTEST 50000
#define DELAY_STEP 10000

int allocateMemory(int ***current_generation, int ***next_generation);
void input(int **current_generation, int *error);
void greetingMessage(void);
void inputRequest(void);
void evolve(int **current_generation, int **next_generation);
int checkNeighbourhood(int **current_generation, int row, int column);
void swapGenerations(int ***current_generation, int ***next_generation);
void freeMemory(int **current_generation, int **next_generation);
void render(int **current_generation);
void readCommand(char *key, int *current_delay);
void outputError(int error);
void initWindow(void);
void feedbackRequest(void);

int main(void) {
  greetingMessage();
  int **current_generation = NULL, **next_generation = NULL;
  int error = allocateMemory(&current_generation, &next_generation);
  input(current_generation, &error);
  if (!error) {
    initWindow();
    int current_delay = 100000;
    char key = 0;
    while (key != 'q') {
      readCommand(&key, &current_delay);
      render(current_generation);
      evolve(current_generation, next_generation);
      swapGenerations(&current_generation, &next_generation);
      usleep(current_delay);
    }
    endwin();
  } else {
    outputError(error);
  }
  freeMemory(current_generation, next_generation);
  feedbackRequest();
  return 0;
}

void initWindow(void) {
  nodelay(initscr(), 1);
  noecho();
}

int allocateMemory(int ***current_generation, int ***next_generation) {
  *current_generation = malloc(SQUARE * sizeof(int) + HEIGHT * sizeof(int *));
  *next_generation = malloc(SQUARE * sizeof(int) + HEIGHT * sizeof(int *));
  int error = 0;
  if (NULL == *current_generation || NULL == *next_generation) {
    error = 1;
  } else {
    int *cur_gen_beginning = (int *)(*current_generation + HEIGHT);
    int *next_gen_beginning = (int *)(*next_generation + HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
      (*current_generation)[i] = cur_gen_beginning + WIDTH * i;
      (*next_generation)[i] = next_gen_beginning + WIDTH * i;
      for (int j = 0; j < WIDTH; j++) {
        (*current_generation)[i][j] = 0;
        (*next_generation)[i][j] = 0;
      }
    }
  }
  return error;
}

void input(int **current_generation, int *error) {
  inputRequest();
  for (int i = 0; i < HEIGHT && 0 == *error; i++) {
    for (int j = 0; j < WIDTH && 0 == *error; j++) {
      if (1 != scanf("%1d", *(current_generation + i) + j) ||
          (current_generation[i][j] != 0 && current_generation[i][j] != 1)) {
        *error = 2;
      }
    }
  }
}

void greetingMessage(void) {
  printf("@--------------------------------------------------------------------"
         "------------@\n");
  printf("                   Welcome to the Game of Life!              \n");
  printf("@--------------------------------------------------------------------"
         "------------@\n");
}

void inputRequest(void) {
  printf("Please, type the initial state of the universe (80x25)...\n");
}

void evolve(int **current_generation, int **next_generation) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int alive_neighbours = checkNeighbourhood(current_generation, i, j);
      if (3 == alive_neighbours && 0 == current_generation[i][j]) {
        next_generation[i][j] = 1;
      } else if (1 == current_generation[i][j] && alive_neighbours != 2 &&
                 alive_neighbours != 3) {
        next_generation[i][j] = 0;
      } else {
        next_generation[i][j] = current_generation[i][j];
      }
    }
  }
}

int checkNeighbourhood(int **current_generation, int row, int column) {
  int alive_neighbours = 0;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = column - 1; j <= column + 1; j++) {
      if (i != row || j != column) {
        int neighbour_row = (i + HEIGHT) % HEIGHT;
        int neighbour_column = (j + WIDTH) % WIDTH;
        alive_neighbours += current_generation[neighbour_row][neighbour_column];
      }
    }
  }
  return alive_neighbours;
}

void swapGenerations(int ***current_generation, int ***next_generation) {
  int **tempptr = *current_generation;
  *current_generation = *next_generation;
  *next_generation = tempptr;
}

void freeMemory(int **current_generation, int **next_generation) {
  free(current_generation);
  free(next_generation);
}

void render(int **current_generation) {
  move(0, 0);
  clear();
  printw("@--------------------------------------------------------------------"
         "------------@\n");
  printw("|                                                                    "
         "            |\n");
  printw("|                        Type \"d\" to speed up the game.            "
         "              |\n");
  printw("|                       Type \"a\" to speed down the game.           "
         "              |\n");
  printw("|                          Type \"q\" to exit the game.              "
         "              |\n");
  printw("|                                                                    "
         "            |\n");
  printw("@--------------------------------------------------------------------"
         "------------@\n");
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = -1; j <= WIDTH; j++) {
      if (-1 == j || WIDTH == j) {
        printw("|");
      } else if (1 == current_generation[i][j]) {
        printw("*");
      } else {
        printw(" ");
      }
    }
    printw("\n");
  }
  printw("@--------------------------------------------------------------------"
         "------------@\n");
  refresh();
}

void readCommand(char *key, int *current_delay) {
  *key = 0;
  char current_symbol = 0;
  if ((current_symbol = getch()) == 'a' || current_symbol == 'A') {
    *key = 'a';
    *current_delay = *current_delay == SLOWEST ? *current_delay
                                               : *current_delay + DELAY_STEP;
  } else if ('d' == current_symbol || current_symbol == 'D') {
    *key = 'd';
    *current_delay = *current_delay == FASTEST ? *current_delay
                                               : *current_delay - DELAY_STEP;
  } else if ('q' == current_symbol || current_symbol == 'Q') {
    *key = 'q';
  }
  while (getch() != ERR) {}
}

void outputError(int error) {
  if (1 == error) {
    printf("Memory allocation failed.\n");
  } else if (2 == error) {
    printf("Incorrect input.\n");
  }
}

void feedbackRequest(void) {
  printf("Please, write your expressions about the game.\n");
}
