#include <stdio.h>

#include "print_module.h"
#include "documentation_module.h"

int main(void) {
  #ifndef Q2_VARARGS
  print_log(print_char, Module_load_success_message);

  #else
  int *availability_mask = check_available_documentation_module(validate, Documents_count, Documents);

  // Output availability for each document....
  char *documents_names[] = {Documents};
  for (int i = 0; i < Documents_count; i++) {
    printf("[%-15s : %savailable]\n", documents_names[i], availability_mask[i] ? "" : "un");
  }
  free(availability_mask);
  #endif
  return 0;
}
