#include <stdio.h>
#include <time.h>

#include "print_module.h"

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char *message) {
  time_t cur_seconds = time(NULL);
  struct tm *cur_time = localtime(&cur_seconds);
  char *log = Log_prefix;
  while (*log) {
    print(*log);
    log++;
  }
  print(' ');
  print('0' + cur_time->tm_hour / 10);
  print('0' + cur_time->tm_hour % 10);
  print(':');
  print('0' + cur_time->tm_min / 10);
  print('0' + cur_time->tm_min % 10);
  print(':');
  print('0' + cur_time->tm_sec / 10);
  print('0' + cur_time->tm_sec % 10);
  print(' ');
  while (*message) {
    print(*message);
    message++;
  }
}
