#include <stdio.h>
#include <stdlib.h>

int input(int **array, int *size);
void bubbleSort(int *array, int size);
void output(int *array, int size, int error);

int main(void) {
  int *array = NULL;
  int size, error;
  error = input(&array, &size);
  if (!error) {
    bubbleSort(array, size);
  }
  output(array, size, error);
  free(array);
  return 0;
}

int input(int **array, int *size) {
  int error = 0;
  if (1 != scanf("%d", size)) {
    error = 1;
  }
  if (error || (*array = malloc(*size * sizeof(int))) == NULL) {
    error = 1;
  }
  for (int i = 0; i < *size && !error; i++) {
    if (1 != scanf("%d", *array + i)) {
      error = 1;
    }
  }
  return error;
}

void bubbleSort(int *array, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

void output(int *array, int size, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < size - 1; i++) {
      printf("%d ", array[i]);
    }
    printf("%d", array[size - 1]);
  }
}
