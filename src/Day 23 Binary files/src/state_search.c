#include "date_processing.h"
#include "doorstate_struct.h"
#include <stdio.h>

#define PATHMAX 256

int input(char *filename, doorstate *door);
int searching(char *filename, doorstate desired_door, int *error);
void output(int code, int error);
int scan_door_data(doorstate *door);
int date_matching(doorstate desired_door, doorstate door);

int main(void) {
  char filename[PATHMAX] = {0};
  doorstate desired_door = {0};
  int error = input(filename, &desired_door);
  int code = 0;
  if (!error) {
    code = searching(filename, desired_door, &error);
  }
  output(code, error);
  return 0;
}

int input(char *filename, doorstate *door) {
  int error = 0;
  if (1 != scanf("%255s", filename) || scan_door_data(door) ||
      !validate_door_data(*door)) {
    error = 1;
  }
  return error;
}

int searching(char *filename, doorstate desired_door, int *error) {
  FILE *file = NULL;
  int end_of_file = 0;
  int code = 0;
  if (NULL == (file = fopen(filename, "rb")) || fseek(file, 0, SEEK_END) ||
      (end_of_file = ftell(file)) <= 0 || end_of_file % sizeof(doorstate)) {
    *error = 1;
  } else {
    int have_found = 0;
    doorstate cur_door = {0};
    int size = end_of_file / sizeof(doorstate);
    for (int i = 0; i < size && !have_found; i++) {
      fseek(file, i * sizeof(doorstate), SEEK_SET);
      fread(&cur_door, sizeof(doorstate), 1, file);
      if (date_matching(desired_door, cur_door)) {
        code = cur_door.code;
        have_found = 1;
      }
    }
    if (!have_found) {
      *error = 1;
    }
    fclose(file);
  }
  return code;
}

void output(int code, int error) {
  if (error) {
    printf("n/a\n");
  } else {
    printf("%d\n", code);
  }
}

int scan_door_data(doorstate *door) {
  return 3 != scanf("%2d.%2d.%4d", &(door->day), &(door->month), &(door->year));
}

int date_matching(doorstate desired_door, doorstate door) {
  int year_matching = desired_door.year == door.year;
  int month_matching = desired_door.month == door.month;
  int day_matching = desired_door.day == door.day;
  return year_matching && month_matching && day_matching;
}
