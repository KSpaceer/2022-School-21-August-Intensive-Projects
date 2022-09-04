#include <stdio.h>

#define LEN 100

void input(int *buff, int *len, int *error);
void sum(const int *buff1, int len1, const int *buff2, int len2, int *result,
         int *result_length, int error);
void sub(int *buff1, int len1, const int *buff2, int len2, int *result,
         int *result_length, int *error);
void output(int *sum_result, int sum_length, int *sub_result, int sub_length,
            int error);

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод:
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод:
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main(void) {
  int buff1[LEN], buff2[LEN];
  int len1 = 0, len2 = 0;
  int error = 0;
  input(buff1, &len1, &error);
  input(buff2, &len2, &error);
  int sum_result[LEN + 1] = {0};
  int sum_length = 0;
  sum(buff1, len1, buff2, len2, sum_result, &sum_length, error);
  int sub_result[LEN] = {0};
  int sub_length = 0;
  sub(buff1, len1, buff2, len2, sub_result, &sub_length, &error);
  output(sum_result, sum_length, sub_result, sub_length, error);
  return 0;
}

void input(int *buff, int *len, int *error) {
  char term = 0;
  while (!(*error) && term != '\n') {
    if (2 != scanf("%d%c", buff, &term) || (term != '\n' && term != ' ') ||
        *buff < 0 || *buff > 9) {
      *error = 1;
    }
    buff++;
    (*len)++;
  }
}

void output(int *sum_result, int sum_length, int *sub_result, int sub_length,
            int error) {
  if (error) {
    printf("n/a");
  } else {
    while (0 == *sum_result && sum_length > 1) {
      sum_result++;
      sum_length--;
    }
    for (int i = 0; i < sum_length - 1; i++) {
      printf("%d ", sum_result[i]);
    }
    printf("%d\n", sum_result[sum_length - 1]);
    while (0 == *sub_result && sub_length > 1) {
      sub_result++;
      sub_length--;
    }
    for (int i = 0; i < sub_length - 1; i++) {
      printf("%d ", sub_result[i]);
    }
    printf("%d", sub_result[sub_length - 1]);
  }
}

void sub(int *buff1, int len1, const int *buff2, int len2, int *result,
         int *result_length, int *error) {
  *error = *error || len2 > len1 ? 1 : 0;
  int buff1_index, buff2_index, result_index;
  *result_length = len1;
  result_index = buff1_index = len1 - 1;
  buff2_index = len2 - 1;
  int borrowed = 0;
  for (; buff1_index >= 0 && buff2_index >= 0 && !(*error);
       buff1_index--, buff2_index--, result_index--) {
    if (buff1[buff1_index] < buff2[buff2_index]) {
      if (buff1_index) {
        borrowed = 1;
        buff1[buff1_index - 1] -= 1;
      } else {
        *error = 1;
      }
    }
    result[result_index] =
        10 * borrowed + buff1[buff1_index] - buff2[buff2_index];
    borrowed = 0;
  }
  for (; buff1_index >= 0 && !(*error); buff1_index--, result_index--) {
    if (buff1[buff1_index] == -1) {
      if (buff1_index) {
        borrowed = 1;
        buff1[buff1_index - 1] -= 1;
      } else {
        *error = 1;
      }
    }
    result[result_index] = 10 * borrowed + buff1[buff1_index];
    borrowed = 0;
  }
}

void sum(const int *buff1, int len1, const int *buff2, int len2, int *result,
         int *result_length, int error) {
  if (!error) {
    int buff1_index, buff2_index, result_index;
    *result_length = 0;
    result_index = len1 > len2 ? len1 : len2;
    buff1_index = len1 - 1;
    buff2_index = len2 - 1;
    int carried = 0;
    for (; buff1_index >= 0 && buff2_index >= 0;
         buff1_index--, buff2_index--, result_index--) {
      result[result_index] =
          (carried + buff1[buff1_index] + buff2[buff2_index]) % 10;
      carried = (carried + buff1[buff1_index] + buff2[buff2_index]) / 10;
      (*result_length)++;
    }
    if (len1 > len2) {
      for (; buff1_index >= 0; buff1_index--, result_index--) {
        result[result_index] = (carried + buff1[buff1_index]) % 10;
        carried = (carried + buff1[buff1_index]) / 10;
        (*result_length)++;
      }
    } else if (len2 > len1) {
      for (; buff2_index >= 0; buff2_index--, result_index--) {
        result[result_index] = (carried + buff2[buff2_index]) % 10;
        carried = (carried + buff2[buff2_index]) / 10;
        (*result_length)++;
      }
    }
    result[result_index] += carried;
    (*result_length)++;
  }
}
