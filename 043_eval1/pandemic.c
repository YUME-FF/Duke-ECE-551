#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  country_t ans;
  int i = 0;
  if (*line == '\n') {
    fprintf(stderr, "Lack of Country\n");
    exit(EXIT_FAILURE);
  }
  while (*line != ',') {
    //printf("%d\n", *line);
    ans.name[i] = *line;
    line++;
    i++;
    if (i > MAX_NAME_LEN - 1) {
      fprintf(stderr, "Country name(everythin before ,) is out of spacs\n");
      exit(EXIT_FAILURE);
    }
  }
  ans.name[i] = '\0';
  uint64_t population = 0;
  line++;
  if (*line == '\n' || *line == 0) {
    fprintf(stderr, "Lack of population\n");
    exit(EXIT_FAILURE);
  }
  while (*line == '\t' || *line == ' ') {
    line++;
  }
  if (*line == '+' || *line == '-') {
    line++;
  }
  if (*line > 57 || *line < 48) {
    fprintf(stderr, "The string in population is illegal");
    exit(EXIT_FAILURE);
  }
  while (*line <= 57 && *line >= 48) {
    if (population > population * 10) {
      fprintf(stderr, "Population is out of range");
      exit(EXIT_FAILURE);
    }
    population = population * 10 + *line - '0';
    line++;
  }

  if (*line != '\n') {
    if (*line != '\0') {
      fprintf(stderr, "The string in population: %s is non-numeric\n", line);
      // printf("population =%ld \n", population);
      exit(EXIT_FAILURE);
    }
  }
  ans.population = population;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //printf("%ld", n_days);
  if (n_days < 6) {
    //fprintf(stderr, "There are less 7 days'data to calculate\n");
    //printf("%ld", n_days);
    exit(EXIT_SUCCESS);
  }
  unsigned * p = data;
  uint64_t sum = 0;
  int nthDay = 0;  //the nth day we have add.
  for (size_t i = 0; i < n_days; i++) {
    if (p == NULL) {
      fprintf(stderr, "Lack of data\n");
      exit(EXIT_FAILURE);
    }
    if (sum > sum + *p) {
      fprintf(stderr, "The sum of daily cases is out of range\n");
      exit(EXIT_FAILURE);
    }
    sum += *p;
    p++;
    nthDay++;
    // printf("%ld %d\n", sum, nthDay);
    //when 7 days have been added, reset these value.
    if (nthDay == 7) {
      *avg = sum / 7.0;
      avg++;
      nthDay = 0;
      p -= 6;
      i -= 6;
      sum = 0;
    }
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  unsigned * p = data;
  double cases = 0;  //the cases until the ith day.
  for (size_t i = 0; i < n_days; i++) {
    if (p == NULL) {
      fprintf(stderr, "Lack of data\n");
      exit(EXIT_FAILURE);
    }
    cases += *p;
    p++;
    *cum = cases / pop * 100000;
    cum++;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  size_t maxi = 0, maxj = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      //printf("%ld %ld %u\n", maxi, maxj, data[i][j]);
      if (data[maxi][maxj] < data[i][j]) {
        maxi = i;
        maxj = j;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", countries[maxi].name, data[maxi][maxj]);
}
