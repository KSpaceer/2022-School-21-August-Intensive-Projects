#include "cipher_input.h"

char *expand_buf(char *buf, size_t *max_size, int *state, FILE *log_file) {
  char *tmp_buf = NULL;
  if (0 == *max_size) {
#ifdef LOGGER
    logcat(log_file, "Setting buffer size to 256", trace);
#else
    (void)log_file;
#endif
    *max_size = 256;
  } else {
#ifdef LOGGER
    logcat(log_file, "Increasing buffer size 1.6 times", trace);
#else
    log_file = NULL;
#endif
    *max_size = (size_t)((double)*max_size * 1.6);
  }
#ifdef LOGGER
  logcat(log_file, "Allocating memory", trace);
#else
  log_file = NULL;
#endif
  tmp_buf = realloc(buf, *max_size * sizeof(char));
  if (NULL == tmp_buf) {
#ifdef LOGGER
    logcat(log_file, "Failed to allocate memory", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  } else {
    buf = tmp_buf;
  }
  return buf;
}

int get_string(char **buf, size_t *cur_size_ptr, size_t *max_size_ptr,
               int *state, FILE *log_file) {
  size_t cur_size = 0;
  size_t max_size = 0;
#ifdef LOGGER
  logcat(log_file, "Getting string from stdin", trace);
#else
  log_file = NULL;
#endif
  do {
    if (cur_size == max_size) {
      *buf = expand_buf(*buf, &max_size, state, log_file);
    }
    if (RUNNING == *state) {
      (*buf)[cur_size++] = getchar();
    }
  } while ((*buf)[cur_size - 1] != '\n' && RUNNING == *state);
  if (RUNNING == *state) {
    (*buf)[cur_size - 1] = '\0';
  }
  if (NULL != cur_size_ptr && NULL != max_size_ptr) {
    *cur_size_ptr = cur_size;
    *max_size_ptr = max_size;
  }
  return *state;
}

int get_file_string(char **buf, size_t *cur_size_ptr, size_t *max_size_ptr,
                    int *state, FILE *file, FILE *log_file) {
  size_t cur_size = 0;
  size_t max_size = 0;
  char cur_sym = 0;
#ifdef LOGGER
  logcat(log_file, "Getting string from file", trace);
#else
  log_file = NULL;
#endif
  while ((cur_sym = fgetc(file)) != EOF && RUNNING == *state) {
    if (cur_size == max_size) {
      *buf = expand_buf(*buf, &max_size, state, log_file);
    }
    if (RUNNING == *state) {
      (*buf)[cur_size++] = cur_sym;
    }
  }
  if (cur_size && RUNNING == *state) {
    (*buf)[cur_size] = '\0';
  }
  if (NULL != cur_size_ptr && NULL != max_size_ptr) {
    *cur_size_ptr = cur_size;
    *max_size_ptr = max_size;
  }
  return *state;
}

void clean_stdin(void) {
  while (getchar() != '\n') {
  }
}
