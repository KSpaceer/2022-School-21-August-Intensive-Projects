#ifndef SRC_CIPHER_INPUT_H_
#define SRC_CIPHER_INPUT_H_
#include "cipher_definitions.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>

char *expand_buf(char *buf, size_t *max_size, int *state, FILE *log_file);
int get_string(char **buf, size_t *cur_size_ptr, size_t *max_size_ptr,
               int *state, FILE *log_file);
int get_file_string(char **buf, size_t *cur_size_ptr, size_t *max_size_ptr,
                    int *state, FILE *file, FILE *log_file);
void clean_stdin(void);

#endif  // SRC_CIPHER_INPUT_H_
