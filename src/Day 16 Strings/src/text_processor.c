#include "s21_string.h"

#define TEXTSIZE 101
#define PTEXTSIZE 303

int input(char text[TEXTSIZE], int *width);
void process_text(char text[TEXTSIZE], char processed_text[PTEXTSIZE],
                  size_t width);
size_t wordlen(char *word);
char *to_next_word(char *textptr);
void output(char processed_text[PTEXTSIZE], int error);

int main(int argc, char *argv[]) {
  int error = 0;
  int width = 0;
  char text[TEXTSIZE] = {0};
  char processed_text[PTEXTSIZE] = {0};
  if (2 != argc ||
      !(argv[1][0] == '-' && argv[1][1] == 'w' && argv[1][2] == '\0') ||
      input(text, &width)) {
    error = 1;
  }
  if (!error) {
    process_text(text, processed_text, (size_t)width);
  }
  output(processed_text, error);
  return 0;
}

int input(char text[TEXTSIZE], int *width) {
  int error = 0;
  if (1 != scanf("%d\n", width) || *width <= 1) {
    error = 1;
  } else {
    char *textptr = (char *)text;
    size_t text_size = 0;
    while (scanf("%c", textptr) && *textptr != '\n' &&
           text_size < TEXTSIZE - 1) {
      textptr++;
      text_size++;
    }
    *textptr = '\0';
  }
  return error;
}

void process_text(char text[TEXTSIZE], char processed_text[PTEXTSIZE],
                  size_t width) {
  char *ptextptr = (char *)processed_text;
  char *textptr = (char *)text;
  size_t cur_width = 0;
  size_t len = wordlen(textptr);
  while (*textptr) {
    if (0 == len) {
      textptr = to_next_word(textptr);
      len = wordlen(textptr);
      if (width != cur_width && (len <= width - cur_width - 1 ||
                                 (len > width && width - cur_width > 3))) {
        *ptextptr = ' ';
        cur_width++;
      } else {
        *ptextptr = '\n';
        cur_width = 0;
      }
      ptextptr++;
    }
    *ptextptr = *textptr;
    ptextptr++;
    textptr++;
    len--;
    cur_width++;
    if (len > 1 && width - cur_width == 1) {
      *ptextptr = '-';
      ptextptr++;
      *ptextptr = '\n';
      ptextptr++;
      cur_width = 0;
    }
  }
}

size_t wordlen(char *word) {
  size_t size = 0;
  while (*word && *word != ' ') {
    word++;
    size++;
  }
  return size;
}

char *to_next_word(char *textptr) {
  while (*textptr == ' ' || *textptr == '\t') {
    textptr++;
  }
  return textptr;
}

void output(char processed_text[PTEXTSIZE], int error) {
  if (error) {
    printf("n/a");
  } else {
    printf("%s", processed_text);
  }
}
