/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

#define MAXLEN 10

int input(int *buffer, int *length);
void output(int sum, int *numbers, int n_length, int error);
int sum_numbers(const int *buffer, int length, int *error);
int find_numbers(const int *buffer, int length, int number, int *numbers, int *error);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
  int buffer[MAXLEN], length, error;
  error = input(buffer, &length);
  int sum = sum_numbers(buffer, length, &error);
  int numbers[MAXLEN];
  int n_length = find_numbers(buffer, length, sum, numbers, &error);
  output(sum, numbers, n_length, error);
  return 0;
}

int input(int *buffer, int *length) {
  int error = 0;
  if (1 != scanf("%d", length) || *length <= 0 || *length > MAXLEN) {
    error = 1;
  }
  for (int i = 0; i < *length && !error; i++) {
    if (1 != scanf("%d", &(buffer[i]))) {
      error = 1;
    }
  }
  return error;
}

void output(int sum, int *numbers, int n_length, int error) {
  if (error) {
    printf("n/a");
  } else {
    printf("%d\n", sum);
    if (n_length > 0) {
      for (int i = 0; i < n_length - 1; i++) {
        printf("%d ", numbers[i]);
      }
      printf("%d", numbers[n_length - 1]);
    }
  }
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(const int *buffer, int length, int *error) {
  int sum = 0;
  if (0 == *error) {
    *error = 1;
    for (int i = 0; i < length; i++) {
      if (buffer[i] % 2 == 0) {
        sum += buffer[i];
        *error = 0;
      }
    }
  }
  return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(const int *buffer, int length, int number, int *numbers,
                 int *error) {
  int n_length = 0;
  if (*error || 0 == number) {
    *error = 1;
  } else {
    int j = 0;
    for (int i = 0; i < length; i++) {
      if (buffer[i] != 0 && number % buffer[i] == 0) {
        numbers[j] = buffer[i];
        j++;
      }
    }
    n_length = j;
  }
  return n_length;
}
