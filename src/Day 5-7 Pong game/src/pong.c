// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25

#define PLAYER1 0
#define PLAYER2 1

#define RACKET1_POS 1
#define RACKET2_POS (FIELD_WIDTH - 2)

int Score(int digit, int x, int y, int shift);
void Rendering(int ball_x, int ball_y, int racket1, int racket2, int points1,
               int points2);
int MoveRacket(int racket, int player);
int UpdateBallX(int ball_x, int ball_y, int vel_x, int racket1, int racket2);
int UpdateBallY(int ball_y, int vel_y);
int UpdateBallVelX(int ball_x, int ball_y, int vel_x, int racket1, int racket2);
int UpdateBallVelY(int ball_y, int vel_y);

int main(void) {
  int ball_x = 40;
  int ball_y = 12;
  int vel_x = 1;
  int vel_y = 1;
  int racket1 = 12;
  int racket2 = 12;
  int points1 = 0;
  int points2 = 0;
  int turn = PLAYER1;
  printf("@--------------------------------------------------------------------"
         "------------@\n");
  printf("@                       Добро пожаловать в игру Pong!                "
         "            @\n");
  printf("@            Управление для первого игрока: A для перемещения "
         "ракетки            @\n");
  printf("@                    вверх, Z для перемещения ракетки вниз.          "
         "            @\n");
  printf("@            Управление для второго игрока: K для перемещения "
         "ракетки            @\n");
  printf("@                    вверх, M для перемещения ракетки вниз.          "
         "            @\n");
  printf("@                     Для пропуска хода нажмите пробел.              "
         "            @\n");
  printf("@--------------------------------------------------------------------"
         "------------@\n");
  Rendering(ball_x, ball_y, racket1, racket2, points1, points2);
  while (points1 < 21 && points2 < 21) {
    if (PLAYER1 == turn) {
      racket1 = MoveRacket(racket1, PLAYER1);
      turn = PLAYER2;
    } else {
      racket2 = MoveRacket(racket2, PLAYER2);
      turn = PLAYER1;
    }
    ball_x = UpdateBallX(ball_x, ball_y, vel_x, racket1, racket2);
    ball_y = UpdateBallY(ball_y, vel_y);
    vel_x = UpdateBallVelX(ball_x, ball_y, vel_x, racket1, racket2);
    vel_y = UpdateBallVelY(ball_y, vel_y);
    Rendering(ball_x, ball_y, racket1, racket2, points1, points2);
    if (0 == ball_x) {
      points2 += 1;
      ball_y = racket1;
      ball_x = 2;
      vel_x = 1;
      turn = PLAYER2;
    } else if ((FIELD_WIDTH - 2) == ball_x) {
      points1 += 1;
      ball_y = racket2;
      ball_x = FIELD_WIDTH - 3;
      vel_x = -1;
      turn = PLAYER1;
    }
  }
  int winner = points1 == 21 ? PLAYER1 : PLAYER2;
  printf("====================================================================="
         "=============\n");
  printf("|                            Игрок %d победил!                       "
         "            |\n",
         winner + 1);
  printf("====================================================================="
         "=============\n");
  return 0;
}

int Score(int digit, int x, int y, int shift) {
  int first_sym = 15 == x - shift;
  int second_sym = 16 == x - shift;
  int third_sym = 17 == x - shift;
  if (5 == y) {
    first_sym *= digit != 1;
    second_sym *= digit != 4;
    third_sym *= digit != 1;
  } else if (6 == y) {
    first_sym *= !(digit >= 1 && digit <= 3);
    second_sym *= digit == 1;
    third_sym *= digit != 1 && digit != 5 && digit != 6;
  } else if (7 == y) {
    first_sym *= digit != 1 && digit != 7;
    second_sym *= digit != 0 && digit != 7;
    third_sym *= digit != 1;
  } else if (8 == y) {
    first_sym *= digit % 2 == 0 && digit != 4;
    second_sym *= digit == 1;
    third_sym *= digit != 1 && digit != 2;
  } else if (9 == y) {
    first_sym *= digit != 1 && digit != 4 && digit != 7;
    second_sym *= digit != 4 && digit != 7;
    third_sym *= digit != 1;
  } else {
    first_sym = 0;
    second_sym = 0;
    third_sym = 0;
  }
  return first_sym || second_sym || third_sym;
}

void Rendering(int ball_x, int ball_y, int racket1, int racket2, int points1,
               int points2) {
  for (int y = -1; y <= FIELD_HEIGHT; y++) {
    for (int x = -1; x <= FIELD_WIDTH; x++) {
      if (x == -1 || y == -1 || x == FIELD_WIDTH || y == FIELD_HEIGHT) {
        printf("#");
      } else if (y == ball_y && x == ball_x) {
        printf("o");
      } else if (x == RACKET1_POS &&
                 (y == racket1 || y == racket1 - 1 || y == racket1 + 1)) {
        printf("|");
      } else if (x == RACKET2_POS &&
                 (y == racket2 || y == racket2 - 1 || y == racket2 + 1)) {
        printf("|");
      } else if (Score(points1 % 10, x, y, 4) ||
                 Score(points2 % 10, x, y, 44)) {
        printf("*");
      } else if ((points1 / 10 && Score(points1 / 10, x, y, 0)) ||
                 (points2 / 10 && Score(points2 / 10, x, y, 40))) {
        printf("*");
      } else if (FIELD_WIDTH / 2 == x) {
        printf("|");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

int MoveRacket(int racket, int player) {
  char command = getchar();
  while (getchar() != '\n') {}
  command = command > 64 && command < 91 ? command + 32 : command;
  if (player == PLAYER1) {
    if (command == 'a' && racket - 1 != 0) {
      racket--;
    } else if (command == 'z' && racket + 1 != FIELD_HEIGHT - 1) {
      racket++;
    } else if (command != 'z' && command != 'a' && command != ' ') {
      printf("Ошибка! Неизвестная команда!\n");
    }
  } else {
    if (command == 'k' && racket - 1 != 0) {
      racket--;
    } else if (command == 'm' && racket + 1 != FIELD_HEIGHT - 1) {
      racket++;
    } else if (command != 'k' && command != 'm' && command != ' ') {
      printf("Ошибка! Неизвестная команда!\n");
    }
  }
  return racket;
}

int UpdateBallX(int ball_x, int ball_y, int vel_x, int racket1, int racket2) {
  int y_ball_racket1_intersection =
      ball_y == racket1 || ball_y - 1 == racket1 || ball_y + 1 == racket1;
  int y_ball_racket2_intersection =
      ball_y == racket2 || ball_y - 1 == racket2 || ball_y + 1 == racket2;
  int ball_racket1_collision =
      y_ball_racket1_intersection && ball_x - 1 == RACKET1_POS && vel_x == -1;
  int ball_racket2_collision =
      y_ball_racket2_intersection && ball_x + 1 == RACKET2_POS && vel_x == 1;
  if (!(ball_racket1_collision || ball_racket2_collision)) {
    ball_x += vel_x;
  }
  return ball_x;
}

int UpdateBallY(int ball_y, int vel_y) {
  int ball_border_collision = (ball_y == 0 && vel_y == -1) ||
                              (ball_y == FIELD_HEIGHT - 1 && vel_y == 1);
  if (!ball_border_collision) {
    ball_y += vel_y;
  }
  return ball_y;
}

int UpdateBallVelX(int ball_x, int ball_y, int vel_x, int racket1,
                   int racket2) {
  int y_ball_racket1_intersection =
      ball_y == racket1 || ball_y - 1 == racket1 || ball_y + 1 == racket1;
  int y_ball_racket2_intersection =
      ball_y == racket2 || ball_y - 1 == racket2 || ball_y + 1 == racket2;
  if (ball_x + 1 == RACKET2_POS && y_ball_racket2_intersection) {
    vel_x = -1;
  } else if (ball_x - 1 == RACKET1_POS && y_ball_racket1_intersection) {
    vel_x = 1;
  }
  return vel_x;
}

int UpdateBallVelY(int ball_y, int vel_y) {
  if (ball_y == 0 || ball_y == FIELD_HEIGHT - 1) {
    vel_y *= -1;
  }
  return vel_y;
}
