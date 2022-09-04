#include "doorstate_struct.h"
#include "date_processing.h"
#include <stdio.h>

#define PATHMAX 256

#define OUTPUT 0
#define SORT 1
#define INSERTION 2

int input(char *filename, int *mode);
void output_file_mode(char *filename, int *error);
void sort_file_mode(char *filename, int *error);
void file_insertion_mode(char *filename, int *error);
void output_file_data(FILE *file, int end_of_file);
void sort_file_data(FILE *file, int end_of_file);
void insert_new_door(FILE *file, int *end_of_file, int *error);
int scan_door_data(doorstate *door);
int door_compare(doorstate door1, doorstate door2);
void swap_doors(doorstate *door1, doorstate *door2, FILE *file);
void print_doorstate(doorstate door);
void output_error(void);

int main(void) {
  char filename[PATHMAX] = {0};
  int error = 0;
  int mode = 0;
  error = input(filename, &mode);
  if (!error) {
    if (OUTPUT == mode) {
      output_file_mode(filename, &error);
    } else if (SORT == mode) {
      sort_file_mode(filename, &error);
    } else if (INSERTION == mode) {
      file_insertion_mode(filename, &error);
    }
  }
  if (error) {
    output_error();
  }
  return 0;
}

int input(char *filename, int *mode) {
  int error = 0;
  if (1 != scanf("%255s", filename) || 1 != scanf("%d", mode) ||
      !(*mode >= 0 && *mode <= 2)) {
    error = 1;
  }
  return error;
}

void output_file_mode(char *filename, int *error) {
  FILE *file = NULL;
  int end_of_file = 0;
  if (NULL == (file = fopen(filename, "rb")) || fseek(file, 0, SEEK_END) ||
      (end_of_file = ftell(file)) <= 0 || end_of_file % sizeof(doorstate)) {
    *error = 1;
  } else {
    output_file_data(file, end_of_file);
    fclose(file);
  }
}

void sort_file_mode(char *filename, int *error) {
  FILE *file = NULL;
  int end_of_file = 0;
  if (NULL == (file = fopen(filename, "r+b")) || fseek(file, 0, SEEK_END) ||
      (end_of_file = ftell(file)) <= 0 || end_of_file % sizeof(doorstate)) {
    *error = 1;
  } else {
    sort_file_data(file, end_of_file);
    output_file_data(file, end_of_file);
    fclose(file);
  }
}

void file_insertion_mode(char *filename, int *error) {
  FILE *file = NULL;
  int end_of_file = 0;
  if (NULL == (file = fopen(filename, "r+b")) || fseek(file, 0, SEEK_END) ||
      (end_of_file = ftell(file)) <= 0 || end_of_file % sizeof(doorstate)) {
    *error = 1;
  } else {
    insert_new_door(file, &end_of_file, error);
    if (0 == *error) {
      sort_file_data(file, end_of_file);
      output_file_data(file, end_of_file);
      fclose(file);
    }
  }
}

void output_file_data(FILE *file, int end_of_file) {
  rewind(file);
  doorstate cur_door = {0};
  int pos = 0;
  while (pos != end_of_file) {
    fseek(file, pos, SEEK_SET);
    fread(&cur_door, sizeof(doorstate), 1, file);
    print_doorstate(cur_door);
    pos += sizeof(doorstate);
  }
}

void sort_file_data(FILE *file, int end_of_file) {
  rewind(file);
  doorstate cur_door = {0};
  doorstate next_door = {0};
  int size = end_of_file / sizeof(doorstate);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      fseek(file, j * sizeof(doorstate), SEEK_SET);
      fread(&cur_door, sizeof(doorstate), 1, file);
      fseek(file, (j + 1) * sizeof(doorstate), SEEK_SET);
      fread(&next_door, sizeof(doorstate), 1, file);
      if (door_compare(cur_door, next_door) > 0) {
        fseek(file, j * sizeof(doorstate), SEEK_SET);
        swap_doors(&cur_door, &next_door, file);
      }
    }
  }
}

void insert_new_door(FILE *file, int *end_of_file, int *error) {
  doorstate new_door = {0};
  if (scan_door_data(&new_door) || !validate_door_data(new_door)) {
    *error = 1;
  } else {
    fseek(file, 0, SEEK_END);
    fwrite(&new_door, sizeof(doorstate), 1, file);
    *end_of_file += sizeof(doorstate);
    rewind(file);
  }
}

int scan_door_data(doorstate *door) {
  int date_result =
      scanf("%d %d %d", &(door->year), &(door->month), &(door->day));
  int time_result =
      scanf("%d %d %d", &(door->hour), &(door->minute), &(door->second));
  int door_result = scanf("%d %d", &(door->status), &(door->code));
  return (date_result + time_result + door_result) != 8;
}

int door_compare(doorstate door1, doorstate door2) {
  int dif = 0;
  if (door1.year != door2.year) {
    dif = door1.year - door2.year;
  } else if (door1.month != door2.month) {
    dif = door1.month - door2.month;
  } else if (door1.day != door2.day) {
    dif = door1.day - door2.day;
  } else if (door1.hour != door2.hour) {
    dif = door1.hour - door2.hour;
  } else if (door1.minute != door2.minute) {
    dif = door1.minute - door2.minute;
  } else if (door1.second != door2.second) {
    dif = door1.second - door2.second;
  }
  return dif;
}

void swap_doors(doorstate *door1, doorstate *door2, FILE *file) {
  doorstate *tmpdoor = door1;
  fwrite(door2, sizeof(doorstate), 1, file);
  fwrite(tmpdoor, sizeof(doorstate), 1, file);
}

void print_doorstate(doorstate door) {
  printf("%d %d %d ", door.year, door.month, door.day);
  printf("%d %d %d ", door.hour, door.minute, door.second);
  printf("%d %d\n", door.status, door.code);
}

void output_error(void) { printf("n/a\n"); }
