#include <stdio.h>

#define ARRAY_SIZE 10

int input(int *array);
void bubbleSort(int *array);
void output(int *array, int error);

int main(void) {
  int array[ARRAY_SIZE], error;
  error = input(array);
  if (!error) {
    bubbleSort(array);
  }
  output(array, error);
  return 0;
}

int input(int *array) {
  int error = 0;
  for (int i = 0; i < ARRAY_SIZE && !error; i++) {
    if (1 != scanf("%d", &(array[i]))) {
      error = 1;
    }
  }
  return error;
}

void bubbleSort(int *array) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

void output(int *array, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
      printf("%d ", array[i]);
    }
    printf("%d", array[ARRAY_SIZE - 1]);
  }
}
