#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

#define CLOSED 0
#define OPEN

void initialize_doors(struct door *doors);
void sort_doors(struct door *doors);
void close_doors(struct door *doors);
void output_doors(struct door *doors);

int main() {
  struct door doors[DOORS_COUNT];
  initialize_doors(doors);
  sort_doors(doors);
  close_doors(doors);
  output_doors(doors);
  return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door *doors) {
  srand(time(0));

  int seed = rand() % MAX_ID_SEED;
  for (int i = 0; i < DOORS_COUNT; i++) {
    doors[i].id = (i + seed) % DOORS_COUNT;
    doors[i].status = rand() % 2;
  }
}

void sort_doors(struct door *doors) {
  for (int i = 0; i < DOORS_COUNT; i++) {
    for (int j = 0; j < DOORS_COUNT - i - 1; j++) {
      if (doors[j].id > doors[j + 1].id) {
        struct door tempdoor = doors[j];
        doors[j] = doors[j + 1];
        doors[j + 1] = tempdoor;
      }
    }
  }
}

void close_doors(struct door *doors) {
  for (int i = 0; i < DOORS_COUNT; i++) {
    doors[i].status = CLOSED;
  }
}
void output_doors(struct door *doors) {
  for (int i = 0; i < DOORS_COUNT; i++) {
    printf("%d, %d", doors[i].id, doors[i].status);
    if (i != DOORS_COUNT - 1) {
      printf("\n");
    }
  }
}
