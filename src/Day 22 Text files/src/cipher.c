#include "cipher_operations.h"

int main(void) {
  int state = RUNNING;
  int mode = 0;
  char filename[MAXPATH] = {0};
  char dirname[] = "./ai_modules";
  FILE *log_file = NULL;
  #ifdef LOGGER
  log_file = log_init("logging.txt");
  logcat(log_file, "Starting a new session", info);
  #endif
  while (OFF != state) {
    state = mode_setting(&mode, log_file);
    if (RUNNING == state) {
      state = operating(mode, filename, dirname, log_file);
    }
    if (ERROR == state) {
      printf("n/a\n");
    }
  }
  #ifdef LOGGER
  logcat(log_file, "Ending the session", info);
  log_close(log_file);
  #endif
  return 0;
}
