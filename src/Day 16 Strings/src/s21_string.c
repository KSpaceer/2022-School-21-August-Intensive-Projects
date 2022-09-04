#include "s21_string.h"

size_t s21_strlen(const char *str) {
  size_t len = 0;
  while (*str) {
    len++;
    str++;
  }
  return len;
}

int s21_strcmp(const char *string1, const char *string2) {
  while (*string1 && *string2 && 0 == (*string1 - *string2)) {
    string1++;
    string2++;
  }
  return *string1 - *string2 == 0 ? 0 : (*string1 - *string2) / abs(*string1 - *string2);
}

char *s21_strcpy(char *restrict destination, const char *restrict source) {
  char *dest_ptr = destination;
  while (*source) {
    *dest_ptr = *source;
    dest_ptr++;
    source++;
  }
  *dest_ptr = *source;
  return destination;
}

char *s21_strcat(char *restrict destination, const char *restrict source) {
  char *dest_ptr = destination;
  while (*dest_ptr) {
    dest_ptr++;
  }
  while (*source) {
    *dest_ptr = *source;
    dest_ptr++;
    source++;
  }
  *dest_ptr = *source;
  return destination;
}

char *s21_strchr(const char *str, int c) {
  char *chrptr = NULL;
  while (*str && *str != c) {
    str++;
  }
  if (*str != 0) {
    chrptr = (char*)str;
  }
  return chrptr;
}

char *s21_strstr(const char *string1, const char *string2) {
  char *occurence = NULL;
  size_t len1 = s21_strlen(string1);
  size_t len2 = s21_strlen(string2);
  size_t string1_shift = 0;
  size_t string2_shift = 0;
  size_t coincidence = 0;
  while (len1 > len2 && string1_shift < len1 - len2 && coincidence != len2) {
    if (string1[string1_shift] == string2[string2_shift]) {
      coincidence++;
      string2_shift++;
    } else {
      string2_shift = 0;
      coincidence = string1[string1_shift] == string2[string2_shift];
    }
    string1_shift++;
  }
  if (coincidence == len2) {
    occurence = (char*)string1 + string1_shift - len2;
  }
  return occurence;
}

char *s21_strtok(char *str, const char *sep) {
  static char *pos = NULL;
  char *beginning = NULL;
  size_t sep_len = s21_strlen(sep);
  int is_sep = 0;
  if (NULL != str) {
    pos = str;
  }
  while (pos != NULL && *pos && !is_sep) {
    for (size_t i = 0; i < sep_len && !is_sep; i++) {
      if (*pos == sep[i]) {
        is_sep = 1;
      }
    }
    if (beginning == NULL) {
      beginning = pos;
    }
    pos++;
  }
  if (pos != NULL && *pos) {
    pos--;
    *pos = '\0';
    pos++;
  }
  return beginning;
}

