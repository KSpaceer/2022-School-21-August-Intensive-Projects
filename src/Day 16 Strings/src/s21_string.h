#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#include <stdio.h>
#include <stdlib.h>

size_t s21_strlen(const char *str);
int s21_strcmp(const char *string1, const char *string2);
char *s21_strcpy(char *restrict destination, const char *restrict source);
char *s21_strcat(char *restrict destination, const char *restrict source);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *string1, const char *string2);
char *s21_strtok(char *str, const char *sep);

#endif  // SRC_S21_STRING_H_
