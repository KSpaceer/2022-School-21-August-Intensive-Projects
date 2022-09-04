#include "date_processing.h"

int validate_door_data(doorstate door) {
  int date_result = door.year >= 0 && door.month > 0 && door.month < 13 &&
                    day_result(door.day, door.month, door.year);
  int hour_result = door.hour >= 0 && door.hour <= 23;
  int min_sec_result = door.minute >= 0 && door.minute <= 59 &&
                       door.second >= 0 && door.second <= 59;
  int status_result = door.status == 0 || door.status == 1;
  return date_result && hour_result && min_sec_result && status_result;
}

int day_result(int day, int month, int year) {
  int result = 0;
  int month31 = 1 == month || 3 == month || 5 == month || 7 == month ||
                8 == month || 10 == month || 12 == month;
  int february = 2 == month;
  if (february && day > 0 && ((is_leap(year) && day == 29) || day <= 28)) {
    result = 1;
  } else if (month31 && day > 0 && day <= 31) {
    result = 1;
  } else if (day <= 30) {
    result = 1;
  }
  return result;
}

int is_leap(int year) {
  return year % 4 == 0 && ((year % 400 == 0) || (year % 100 != 0));
}
