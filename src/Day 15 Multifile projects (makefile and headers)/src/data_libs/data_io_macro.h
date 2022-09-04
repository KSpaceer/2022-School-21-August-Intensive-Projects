#ifndef SRC_DATA_LIBS_DATA_IO_MACRO_H_
#define SRC_DATA_LIBS_DATA_IO_MACRO_H_
#include <stdio.h>
#include <stdlib.h>

#define INPUTSPEC(TYPE) _Generic((TYPE), int: "%d", \
  char: "%c", \
  double: "%lf", \
  float: "%f")

#define SPACEOUTPUTSPEC(TYPE) (_Generic((TYPE), int: "%d ", \
  char: "%c ", \
  double: "%.2lf ", \
  float: "%.2f "))

#define OUTPUTSPEC(TYPE) (_Generic((TYPE), int: "%d", \
  char: "%c", \
  double: "%.2lf", \
  float: "%.2f"))

#define INPUT(ARR, SIZE, TYPE) ({if (1 != scanf("%d", &(SIZE)) || (SIZE) <= 0) { \
    error = 1; \
  } else { \
    (ARR) = malloc((SIZE) * sizeof((TYPE))); \
    if (NULL == (ARR)) { \
      error = 1; \
    } \
    for (int i = 0; i < (SIZE) && !error; i++) { \
      if (1 != scanf(INPUTSPEC((TYPE)), ARR + i)) { \
        error = 1; \
      } \
    } \
  }})

#define OUTPUT(ARR, SIZE, TYPE) ({for (int i = 0; i < (SIZE) - 1; i++) { \
    printf(SPACEOUTPUTSPEC((TYPE)), (ARR)[i]); \
  } \
  printf(OUTPUTSPEC((TYPE)), (ARR)[SIZE - 1]);})

#endif  // SRC_DATA_LIBS_DATA_IO_MACRO_H_
