#ifndef SRC_DATE_PROCESSING_H_
#define SRC_DATE_PROCESSING_H_
#include "doorstate_struct.h"

int validate_door_data(doorstate door);
int day_result(int day, int month, int year);
int is_leap(int year);

#endif  // SRC_DATE_PROCESSING_H_
