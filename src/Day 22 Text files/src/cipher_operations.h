#ifndef SRC_CIPHER_OPERATIONS_H_
#define SRC_CIPHER_OPERATIONS_H_
#include "cipher_definitions.h"
#include "cipher_input.h"
#include "des.h"
#include "logger.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode_setting(int *mode, FILE *log_file);
int operating(int mode, char *filename, char *dirname, FILE *log_file);
void read_file(int *state, char *filename, FILE *log_file);
void append_to_file(int *state, char *filename, FILE *log_file);
int append_new_string(char **buf, size_t cur_size, size_t max_size,
                      char *stdin_buf, size_t stdin_cur_size, int *state,
                      FILE *log_file);
void caesar_cipher(int *state, char *dirname, FILE *log_file);
void file_caesar_cipher(int *state, char *filename, FILE *log_file);
void wipe_file(int *state, char *filename);
int define_file_type(char *filename);
void des_cipher(int *state, char *dirname, FILE *log_file);
void file_des_cipher(int *state, char *filename, FILE *log_file);
void block_alignment(char **buf, size_t *cur_size_ptr, size_t *max_size_ptr,
                     int *state, FILE *log_file);

#endif  // SRC_CIPHER_OPERATIONS_H_
