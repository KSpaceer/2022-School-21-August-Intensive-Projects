#include "../data_libs/data_io.h"
#include "data_process.h"

int main(void) {
  double *data = NULL;
  int n = 0;

  // Don`t forget to allocate memory !

  int error = input(&data, &n);

  if (!error && normalization(data, n))
    output(data, n);
  else
    printf("ERROR");
  free(data);
  return 0;
}
