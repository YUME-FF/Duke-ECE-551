#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  for (int i = 0; i < working.months + retired.months; i++) {
    int age = (startAge + i) / 12;
    int month = startAge + i - age * 12;
    if (i < working.months) {
      printf("Age %3d month %2d you have $%.2lf\n", age, month, initial);
      initial += working.contribution + initial * working.rate_of_return / 12;
    }
    else {
      printf("Age %3d month %2d you have $%.2lf\n", age, month, initial);
      initial += retired.contribution + initial * retired.rate_of_return / 12;
    }
  }
}

int main(void) {
  retire_info working;
  retire_info retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  retirement(327, 21345, working, retired);
  return 0;
}
