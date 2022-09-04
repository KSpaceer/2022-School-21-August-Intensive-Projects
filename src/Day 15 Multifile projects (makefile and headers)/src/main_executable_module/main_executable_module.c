#if 0
#define USING_MACRO_IO
#include "../data_libs/data_io_macro.h"
#else
#include "../data_libs/data_io.h"
#define OUTPUT(ARR, SIZE, TYPE) output(ARR, SIZE)
#endif
#include "../data_libs/data_stat.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

int main(void) {
  double *data = NULL;
  int n = 0;
  int error = 0;

  printf("LOAD DATA...\n");
#ifdef USING_MACRO_IO
  INPUT(data, n, data[0]);
#else
  error = input(&data, &n);
#endif

  if (!error) {
    printf("RAW DATA:\n\t");
    OUTPUT(data, n, data[0]);

    printf("\nNORMALIZED DATA:\n\t");
    normalization(data, n);
    OUTPUT(data, n, data[0]);

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
    OUTPUT(data, n, data[0]);

    printf("\nFINAL DECISION:\n\t");
    if (make_decision(data, n)) {
      printf("YES");
    } else {
      printf("NO");
    }
  } else {
    printf("ERROR");
  }
  free(data);
  return 0;
}
