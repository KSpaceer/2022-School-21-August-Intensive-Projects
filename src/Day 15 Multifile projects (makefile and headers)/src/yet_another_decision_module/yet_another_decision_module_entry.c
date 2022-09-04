#include "../data_libs/data_io.h"
#include "decision.h"

int main(void) {
  double *data = NULL;
  int n = 0;
  int error = input(&data, &n);

  if (!error) {
    if (make_decision(data, n))
      printf("YES");
    else
      printf("NO");
  } else {
    printf("ERROR");
  }
  free(data);
  return 0;
}
