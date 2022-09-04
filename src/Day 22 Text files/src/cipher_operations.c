#include "cipher_operations.h"

int mode_setting(int *mode, FILE *log_file) {
  int state = 0;
#ifdef LOGGER
  logcat(log_file, "Choosing mode", trace);
#else
  (void)log_file;
#endif
  if (1 != scanf("%d", mode) || (!(*mode >= 1 && *mode <= 4) && *mode != -1)) {
#ifdef LOGGER
    logcat(log_file, "Wrong input for mode", error);
#else
    log_file = NULL;
#endif
    state = ERROR;
  }
  clean_stdin();
  return state;
}

int operating(int mode, char *filename, char *dirname, FILE *log_file) {
  int state = RUNNING;
  if (READING == mode) {
    read_file(&state, filename, log_file);
  } else if (APPENDING == mode) {
    append_to_file(&state, filename, log_file);
  } else if (CAESAR == mode) {
    caesar_cipher(&state, dirname, log_file);
  } else if (DES == mode) {
    des_cipher(&state, dirname, log_file);
  } else if (CLOSING == mode) {
#ifdef LOGGER
    logcat(log_file, "Turning off the program", info);
#else
    log_file = NULL;
#endif
    state = OFF;
  }
  return state;
}

void read_file(int *state, char *filename, FILE *log_file) {
  FILE *file = NULL;
  char *buf = NULL;
#ifdef LOGGER
  logcat(log_file, "Opening a file for read", trace);
#endif
  if (RUNNING != *state || 1 != scanf("%255s", filename) ||
      NULL == (file = fopen(filename, "r"))) {
#ifdef LOGGER
    logcat(log_file, "An error occured while opening a file", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  } else {
    get_file_string(&buf, NULL, NULL, state, file, log_file);
  }
  clean_stdin();
  if (RUNNING == *state && !fclose(file) && NULL != buf) {
#ifdef LOGGER
    logcat(log_file, "Outputing the content of file", trace);
#else
    log_file = NULL;
#endif
    printf("%s\n", buf);
  } else {
#ifdef LOGGER
    logcat(log_file, "An error occured while ending reading", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  }
#ifdef LOGGER
  logcat(log_file, "Freeing buf memory", trace);
#else
  log_file = NULL;
#endif
  free(buf);
}

void append_to_file(int *state, char *filename, FILE *log_file) {
  char *buf = NULL;
  char *stdin_buf = NULL;
  size_t cur_size = 0;
  size_t max_size = 0;
  size_t stdin_cur_size = 0;
  size_t stdin_max_size = 0;
  FILE *file = NULL;
#ifdef LOGGER
  logcat(log_file, "Starting appending to a file", trace);
#else
  log_file = NULL;
#endif
  if (RUNNING != *state ||
      RUNNING != get_string(&stdin_buf, &stdin_cur_size, &stdin_max_size, state,
                            log_file) ||
      NULL == (file = fopen(filename, "r"))) {
#ifdef LOGGER
    logcat(log_file,
           "An error occured while getting a string or opening a file", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  } else {
    get_file_string(&buf, &cur_size, &max_size, state, file, log_file);
    append_new_string(&buf, cur_size, max_size, stdin_buf, stdin_cur_size,
                      state, log_file);
  }
  if (fclose(file) || *state != RUNNING ||
      NULL == (file = fopen(filename, "w"))) {
#ifdef LOGGER
    logcat(log_file, "An error occured while reopening a file", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  } else {
#ifdef LOGGER
    logcat(log_file, "Outputing the content of updated file", trace);
#else
    log_file = NULL;
#endif
    fputs(buf, file);
    puts(buf);
  }
#ifdef LOGGER
  logcat(log_file, "Freeing buffers\' memory", trace);
#else
  log_file = NULL;
#endif
  fclose(file);
  free(stdin_buf);
  free(buf);
}

int append_new_string(char **buf, size_t cur_size, size_t max_size,
                      char *stdin_buf, size_t stdin_cur_size, int *state,
                      FILE *log_file) {
  while (RUNNING == *state && cur_size + stdin_cur_size > max_size) {
#ifdef LOGGER
    logcat(log_file, "Reallocating memory for the concatenated string", trace);
#else
    log_file = NULL;
#endif
    *buf = expand_buf(*buf, &max_size, state, log_file);
  }
  if (RUNNING == *state) {
#ifdef LOGGER
    logcat(log_file, "Concatenating strings", trace);
#else
    log_file = NULL;
#endif
    strcat(*buf, stdin_buf);
  }
  return *state;
}

void caesar_cipher(int *state, char *dirname, FILE *log_file) {
  DIR *directory = NULL;
  struct dirent *dir = NULL;
  char relpath[512] = {0};
#ifdef LOGGER
  logcat(log_file, "Applying Caesar cipher to files", trace);
#else
  log_file = NULL;
#endif
  if (RUNNING == *state && NULL != (directory = opendir(dirname))) {
    while ((dir = readdir(directory)) != NULL) {
      strcpy(relpath, dirname);
      strcat(relpath, "/");
      strcat(relpath, dir->d_name);
      printf("Current file: %s\n", relpath);
      int filetype = define_file_type(dir->d_name);
      if (CODEFILE == filetype) {
#ifdef LOGGER
        logcat(log_file, "Applying Caesar cipher to a .c file", trace);
#else
        log_file = NULL;
#endif
        printf("Insert desirable shift: ");
        file_caesar_cipher(state, relpath, log_file);
      } else if (HEADERFILE == filetype) {
#ifdef LOGGER
        logcat(log_file, "Wiping the data of a .h file", trace);
#else
        log_file = NULL;
#endif
        wipe_file(state, relpath);
      }
    }
#ifdef LOGGER
    logcat(log_file, "Closing a directory", trace);
#else
    log_file = NULL;
#endif
    closedir(directory);
  } else {
#ifdef LOGGER
    logcat(log_file, "An error occured while opening a directory", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  }
}

void des_cipher(int *state, char *dirname, FILE *log_file) {
  DIR *directory = NULL;
  struct dirent *dir = NULL;
  char relpath[512] = {0};
#ifdef LOGGER
  logcat(log_file, "Applying DES cipher to files", trace);
#else
  log_file = NULL;
#endif
  if (RUNNING == *state && NULL != (directory = opendir(dirname))) {
    while ((dir = readdir(directory)) != NULL) {
      strcpy(relpath, dirname);
      strcat(relpath, "/");
      strcat(relpath, dir->d_name);
      int filetype = define_file_type(dir->d_name);
      if (CODEFILE == filetype) {
#ifdef LOGGER
        logcat(log_file, "Applying DES to a .c file", trace);
#else
        log_file = NULL;
#endif
        file_des_cipher(state, relpath, log_file);
      } else if (HEADERFILE == filetype) {
#ifdef LOGGER
        logcat(log_file, "Wiping the data of a .h file", trace);
#else
        log_file = NULL;
#endif
        wipe_file(state, relpath);
      }
    }
#ifdef LOGGER
    logcat(log_file, "Closing a directory", trace);
#else
    log_file = NULL;
#endif
    closedir(directory);
  } else {
#ifdef LOGGER
    logcat(log_file, "An error occured while opening a directory", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  }
}

void file_caesar_cipher(int *state, char *filename, FILE *log_file) {
  char *buf = NULL;
  size_t cur_size = 0;
  size_t max_size = 0;
  FILE *file = NULL;
  int shift = 0;
  if (RUNNING != *state || NULL == (file = fopen(filename, "r")) ||
      RUNNING !=
          get_file_string(&buf, &cur_size, &max_size, state, file, log_file) ||
      1 != scanf("%d", &shift)) {
#ifdef LOGGER
    logcat(log_file, "An error occured while opening a file", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  } else {
#ifdef LOGGER
    logcat(log_file, "Starting Caesar ciphering", trace);
#else
    log_file = NULL;
#endif
    char *bufptr = buf;
    while (cur_size && *bufptr) {
      *bufptr = (*bufptr + shift) % 255;
      bufptr++;
    }
    if (fclose(file) || NULL == (file = fopen(filename, "w"))) {
#ifdef LOGGER
      logcat(log_file, "An error occured while reopening a file", error);
#else
      log_file = NULL;
#endif
      *state = ERROR;
    } else {
#ifdef LOGGER
      logcat(log_file, "Putting ciphered data to a file", trace);
#else
      log_file = NULL;
#endif
      fputs(buf, file);
    }
#ifdef LOGGER
    logcat(log_file, "Closing a file", trace);
#else
    log_file = NULL;
#endif
    fclose(file);
  }
#ifdef LOGGER
  logcat(log_file, "Freeing buf memory", trace);
#else
  log_file = NULL;
#endif
  clean_stdin();
  free(buf);
}

void file_des_cipher(int *state, char *filename, FILE *log_file) {
  char *buf = NULL;
  size_t cur_size = 0;
  size_t max_size = 0;
  FILE *file = NULL;
  if (RUNNING != *state || NULL == (file = fopen(filename, "r")) ||
      RUNNING !=
          get_file_string(&buf, &cur_size, &max_size, state, file, log_file)) {
#ifdef LOGGER
    logcat(log_file, "An error occured while opening a file", error);
#else
    log_file = NULL;
#endif
    *state = ERROR;
  } else {
#ifdef LOGGER
    logcat(log_file, "Starting DES ciphering", trace);
#else
    log_file = NULL;
#endif
    block_alignment(&buf, &cur_size, &max_size, state, log_file);
    size_t shift = 0;
    long key = *(long *)buf;
    while (shift != cur_size) {
      block_cipher(buf, shift, key);
      shift += 8;
    }
    if (fclose(file) || NULL == (file = fopen(filename, "w"))) {
#ifdef LOGGER
      logcat(log_file, "An error occured while reopening a file", error);
#endif
      *state = ERROR;
    } else {
#ifdef LOGGER
      logcat(log_file, "Putting ciphered data to a file", trace);
#endif
      fputs(buf, file);
    }
#ifdef LOGGER
    logcat(log_file, "Closing a file", trace);
#endif
    fclose(file);
  }
#ifdef LOGGER
  logcat(log_file, "Freeing buf memory", trace);
#endif
  free(buf);
}

void block_alignment(char **buf, size_t *cur_size_ptr, size_t *max_size_ptr,
                     int *state, FILE *log_file) {
  if (0 != *cur_size_ptr % 8) {
    *cur_size_ptr = *cur_size_ptr + 8 - *cur_size_ptr % 8;
  }
  if (*cur_size_ptr >= *max_size_ptr) {
    *buf = expand_buf(*buf, max_size_ptr, state, log_file);
  }
}

void wipe_file(int *state, char *filename) {
  FILE *file = NULL;
  if (NULL == (file = fopen(filename, "w"))) {
    *state = ERROR;
  }
  fclose(file);
}

int define_file_type(char *filename) {
  size_t i = 0;
  int type = 0;
  while (filename[i]) {
    i++;
  }
  if (i >= 3 && '.' == filename[i - 2]) {
    if ('c' == filename[i - 1]) {
      type = CODEFILE;
    } else if ('h' == filename[i - 1]) {
      type = HEADERFILE;
    }
  }
  return type;
}
