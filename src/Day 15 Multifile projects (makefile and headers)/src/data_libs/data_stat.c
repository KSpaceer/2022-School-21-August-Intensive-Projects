#include "data_stat.h"

double max(double *data, int n) {
  double max_value = data[0];
  for (int i = 0; i < n; i++) {
    if (data[i] > max_value) {
      max_value = data[i];
    }
  }
  return max_value;
}

double min(double *data, int n) {
  double min_value = data[0];
  for (int i = 0; i < n; i++) {
    if (data[i] < min_value) {
      min_value = data[i];
    }
  }
  return min_value;
}

double mean(double *data, int n) {
  double m = 0;
  for (int i = 0; i < n; i++) {
    m += data[i];
  }
  m /= n;
  return m;
}

double variance(double *data, int n) {
  double v = 0;
  double m = mean(data, n);
  for (int i = 0; i < n; i++) {
    v += (data[i] - m) * (data[i] - m);
  }
  v /= n;
  return v;
}
