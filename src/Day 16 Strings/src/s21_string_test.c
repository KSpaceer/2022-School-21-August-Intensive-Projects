#include "s21_string.h"

void s21_strlen_test(void);
void s21_strcmp_test(void);
void s21_strcpy_test(void);
void s21_strcat_test(void);
void s21_strchr_test(void);
void s21_strstr_test(void);
void s21_strtok_test(void);

int main(void) {
  #ifdef STRLEN
  s21_strlen_test();
  #elif defined STRCMP
  s21_strcmp_test();
  #elif defined STRCPY
  s21_strcpy_test();
  #elif defined STRCAT
  s21_strcat_test();
  #elif defined STRCHR
  s21_strchr_test();
  #elif defined STRSTR
  s21_strstr_test();
  #elif defined STRTOK
  s21_strtok_test();
  #endif
  return 0;
}

void s21_strlen_test(void) {
  char *testcases[] = {"Hello World!", "Hating bash scripts",
                       "                      ", "", "Hello \0 World"};
  size_t expected[] = {12, 19, 22, 0, 6};
  for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
    size_t result = s21_strlen(testcases[i]);
    printf("%s ", testcases[i]);
    printf("%zu ", result);
    printf("%s\n", result == expected[i] ? "SUCCESS" : "FAIL");
  }
}

void s21_strcmp_test(void) {
  char *testcases[][2] = {{"Hello World!", "Hello World!"},
                          {"Hello World!", "Hola Mundo!"},
                          {"Hello World!", "Hello World"},
                          {"", ""},
                          {"     ", "     "},
                          {"   ", "   "}};
  int expected[] = {0, -1, 1, 0, 0, 0};
  for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
    int result = s21_strcmp(testcases[i][0], testcases[i][1]);
    if (result) {
      result /= abs(result);
    }
    printf("%s %s ", testcases[i][0], testcases[i][1]);
    printf("%d ", result);
    printf("%s\n", result == expected[i] ? "SUCCESS" : "FAIL");
  }
}

void s21_strcpy_test(void) {
  char destination[20];
  char *testcases[] = {"Hello World!", "Hating bash scripts",
                       "                      ", "", "Hello \0 World"};
  int expected[] = {0, 0, 0, 0, 0};
  for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
    s21_strcpy(destination, testcases[i]);
    int result = s21_strcmp(destination, testcases[i]);
    printf("%s ", testcases[i]);
    printf("%s ", destination);
    printf("%s\n", result == expected[i] ? "SUCCESS" : "FAIL");
  }
}

void s21_strcat_test(void) {
  char destination[40];
  char *testcases[][2] = {{"Hello ", "World!"},
                          {"", "Hi"},
                          {"     a", "      "},
                          {"      \0b", "    a\0a"},
                          {"", ""}};
  char *concatenated[] = {"Hello World!", "Hi", "     a      ", "          a", ""};
  int expected[] = {0, 0, 0, 0, 0};
  for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
    s21_strcpy(destination, testcases[i][0]);
    s21_strcat(destination, testcases[i][1]);
    int result = s21_strcmp(destination, concatenated[i]);
    printf("%s %s ", testcases[i][0], testcases[i][1]);
    printf("%s ", destination);
    printf("%s\n", result == expected[i] ? "SUCCESS" : "FAIL");
  }
}

void s21_strchr_test(void) {
  char *testcases[] = {"Hello World!", "Hating bash scripts",
                       "                      ", "There is no first letter of English",
                       "", "aaaaaaaaaa"};
  char symbols[] = {'l', 'b', 'a', 'a', ' ', 'a'};
  char *expected[] = {testcases[0] + 2, testcases[1] + 7, NULL, NULL, NULL, testcases[5]};
  for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
    char *result = s21_strchr(testcases[i], symbols[i]);
    printf("%s %c ", testcases[i], symbols[i]);
    printf("%p ", result);
    printf("%s\n", result == expected[i] ? "SUCCESS" : "FAIL");
  }
}

void s21_strstr_test(void) {
  char *testcases[] = {"Hello World!", "Hating bash scripts",
                       "                      ", "I like felines",
                       "", "aaaAaaAaaAaa", "big", "aaaaaaa\0bbbbbbb"};
  char *substrings[] = {"Hello", "bash", "a", "cats", "", "Aaa", "bigger", "b"};
  char *expected[] = {testcases[0], testcases[1] + 7, NULL, NULL, testcases[4], testcases[5] + 3, NULL, NULL};
  for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
    char *result = s21_strstr(testcases[i], substrings[i]);
    printf("%s %s ", testcases[i], substrings[i]);
    printf("%p ", result);
    printf("%s\n", result == expected[i] ? "SUCCESS" : "FAIL");
  }
}

void s21_strtok_test(void) {
  char *testcases[] = {"Hello World!", "Hating bash scripts",
                       "                      ", "Ats@as@separators",
                       "There is no separator", "", "double//separator", "By comma,by the way,can I separate",
                       "Die, dog humanoid alien"};
  char *separators[] = {" ", " ", "a", "@", "^", "a", "/", " ,", " "};
  size_t expected[] = {2, 3, 1, 3, 1, 1, 3, 8, 4};
  for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
    char test_string[50];
    s21_strcpy(test_string, testcases[i]);
    printf("%s %s ", test_string, separators[i]);
    char *beginning = s21_strtok(test_string, separators[i]);
    printf("%s ", beginning);
    size_t words = 1;
    while ((beginning = s21_strtok(NULL, separators[i])) != NULL) {
      printf("%s ", beginning);
      words++;
    }
    printf("%s\n", words == expected[i] ? "SUCCESS" : "FAIL");
  }
}

