#include <stdio.h>

void CharEncode(void);
void CharDecode(void);

int main(int argc, char *argv[]) {
  if (2 != argc || (**(argv + 1) != '0' && **(argv + 1) != '1') ||
      *(*(argv + 1) + 1) != 0) {
    printf("n/a");
  } else {
    if ('0' == **(argv + 1)) {
      CharEncode();
    } else {
      CharDecode();
    }
  }
  return 0;
}

void CharEncode(void) {
  char printable_char = 0;
  char cur_char = 0;
  int is_correct = 1;
  while ((cur_char = getchar()) != '\n' && is_correct) {
    if (cur_char == ' ' && printable_char != 0) {
      printf("%X ", printable_char);
      printable_char = 0;
    } else if (cur_char != ' ' && 0 == printable_char) {
      printable_char = cur_char;
    } else {
      is_correct = 0;
    }
  }
  if (!is_correct) {
    printf("n/a");
  } else if (printable_char != 0) {
    printf("%X", printable_char);
  }
}

void CharDecode(void) {
  int char_code = 0;
  char delim = 0;
  int is_correct = 1;
  while (delim != '\n' && is_correct) {
    if (2 != scanf("%2X%c", &char_code, &delim) ||
        (delim != ' ' && delim != '\n')) {
      is_correct = 0;
    } else {
      if (delim == ' ') {
        printf("%c ", char_code);
      } else {
        printf("%c", char_code);
      }
    }
  }
  if (!is_correct) {
    printf("n/a");
  }
}
