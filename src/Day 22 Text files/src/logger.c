#include "logger.h"

FILE *log_init(char *filename) {
  FILE *log_file = fopen(filename, "a");
  return log_file;
}

int logcat(FILE *log_file, char *message, enum log_level level) {
  time_t cur_seconds = time(NULL);
  struct tm *cur_time = localtime(&cur_seconds);
  char level_inf[8];
  if (debug == level) {
    strcpy(level_inf, "DEBUG");
  } else if (trace == level) {
    strcpy(level_inf, "TRACE");
  } else if (info == level) {
    strcpy(level_inf, "INFO");
  } else if (warning == level) {
    strcpy(level_inf, "WARNING");
  } else {
    strcpy(level_inf, "ERROR");
  }
  int result = fprintf(log_file, "%s %s %s\n", level_inf, asctime(cur_time), message);
  fflush(log_file);
  return result == 3;
}

int log_close(FILE *log_file) {
  return fclose(log_file);
}
