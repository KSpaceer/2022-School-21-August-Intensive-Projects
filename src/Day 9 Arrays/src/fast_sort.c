#include <stdio.h>

#define ARRAY_SIZE 10

int input(int *array);
void copyArray(const int *array, int *array2);
void quickSort(int *array, int size);
void buildHeap(int *array, int size);
void heapify(int *array, int root, int size);
void heapSort(int *array, int size);
void output(int *array, int *array2, int error);

int main(void) {
  int array[ARRAY_SIZE], array2[ARRAY_SIZE], error;
  error = input(array);
  if (!error) {
    copyArray(array, array2);
    quickSort(array, ARRAY_SIZE);
    heapSort(array2, ARRAY_SIZE);
  }
  output(array, array2, error);
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

void copyArray(const int *array, int *array2) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    array2[i] = array[i];
  }
}

void quickSort(int *array, int size) {
  int pivot = array[size / 2];
  int left = 0;
  int right = size - 1;
  while (left <= right) {
    while (array[left] < pivot) {
      left++;
    }
    while (array[right] > pivot) {
      right--;
    }
    if (left <= right) {
      int temp = array[left];
      array[left] = array[right];
      array[right] = temp;
      left++;
      right--;
    }
  }
  if (right > 0) {
    quickSort(array, right + 1);
  }
  if (size > left) {
    quickSort(array + left, size - left);
  }
}

void buildHeap(int *array, int size) {
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(array, i, size);
  }
}

void heapify(int *array, int root, int size) {
  int node = root;
  int swapped = 1;
  while (swapped) {
    swapped = 0;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;
    int max = node;
    if (left_child < size && array[left_child] > array[max]) {
      max = left_child;
    }
    if (right_child < size && array[right_child] > array[max]) {
      max = right_child;
    }
    if (max != node) {
      int temp = array[node];
      array[node] = array[max];
      array[max] = temp;
      swapped = 1;
      node = max;
    }
  }
}

void heapSort(int *array, int size) {
  buildHeap(array, size);
  for (int i = size - 1; i >= 0; i--) {
    int temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    heapify(array, 0, i);
  }
}

void output(int *array, int *array2, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
      printf("%d ", array[i]);
    }
    printf("%d", array[ARRAY_SIZE - 1]);
    printf("\n");
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
      printf("%d ", array2[i]);
    }
    printf("%d", array2[ARRAY_SIZE - 1]);
  }
}
