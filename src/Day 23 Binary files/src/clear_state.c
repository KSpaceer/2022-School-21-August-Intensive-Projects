#include "date_processing.h"
#include "doorstate_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define PATHMAX 256

int input(char *filename, doorstate *door1, doorstate *door2);
void clear_doors(char *filename, doorstate door1, doorstate door2, int *error);
void output(char *filename, int error);
void output_file_data(FILE *file, int end_of_file);
int scan_door_data(doorstate *door1, doorstate *door2);
int door_compare(doorstate door1, doorstate door2);
void print_doorstate(doorstate door);

int main(void) {
  char filename[PATHMAX] = {0};
  doorstate door1 = {0};
  doorstate door2 = {0};
  int error = input(filename, &door1, &door2);
  if (!error) {
    clear_doors(filename, door1, door2, &error);
  }
  output(filename, error);
  return 0;
}

int input(char *filename, doorstate *door1, doorstate *door2) {
  int error = 0;
  if (1 != scanf("%255s", filename) || scan_door_data(door1, door2) ||
      !validate_door_data(*door1) || !validate_door_data(*door2)) {
    error = 1;
  }
  return error;
}

void clear_doors(char *filename, doorstate door1, doorstate door2, int *error) {
  FILE *file = NULL;
  doorstate *doors = NULL;
  int end_of_file = 0;
  if (NULL == (file = fopen(filename, "rb")) || fseek(file, 0, SEEK_END) ||
      (end_of_file = ftell(file)) <= 0 || end_of_file % sizeof(doorstate)) {
    *error = 1;
  } else {
    int max_size = end_of_file / sizeof(doorstate);
    doors = malloc(end_of_file);
    if (NULL == doors) {
      *error = 1;
    }
    int new_size = 0;
    doorstate new_door = {0};
    for (int i = 0; i < max_size && 0 == *error; i++) {
      fseek(file, i * sizeof(doorstate), SEEK_SET);
      fread(&new_door, sizeof(doorstate), 1, file);
      if (!(door_compare(new_door, door1) * door_compare(new_door, door2) <=
            0)) {
        doors[new_size++] = new_door;
      }
    }
    fclose(file);
    if (0 != *error || NULL == (file = fopen(filename, "wb"))) {
      *error = 1;
    } else {
      fwrite(doors, sizeof(doorstate), new_size, file);
      fclose(file);
    }
  }
  free(doors);
}

void output(char *filename, int error) {
  FILE *file = NULL;
  int end_of_file;
  if (error || NULL == (file = fopen(filename, "rb")) ||
      fseek(file, 0, SEEK_END) ||
      (end_of_file = ftell(file)) % sizeof(doorstate)) {
    printf("n/a\n");
  } else {
    output_file_data(file, end_of_file);
  }
  if (file) {
    fclose(file);
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

int scan_door_data(doorstate *door1, doorstate *door2) {
  int d1_result =
      3 != scanf("%2d.%2d.%4d", &(door1->day), &(door1->month), &(door1->year));
  int d2_result =
      3 != scanf("%2d.%2d.%4d", &(door2->day), &(door2->month), &(door2->year));
  return d1_result || d2_result;
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

void print_doorstate(doorstate door) {
  printf("%d %d %d ", door.year, door.month, door.day);
  printf("%d %d %d ", door.hour, door.minute, door.second);
  printf("%d %d\n", door.status, door.code);
}
