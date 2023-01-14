#include "circle.hpp"

#include <math.h>
#define PI 3.1415926

Circle::Circle(Point c, double r) : center(c), radius(r) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  const double distance = center.distanceFrom(otherCircle.center);
  if (distance >= radius + otherCircle.radius) {
    return 0.0;
  }
  if (distance <= std::abs(radius - otherCircle.radius)) {
    return PI * pow(fmin(radius, otherCircle.radius), 2);
  }

  double Ar2 = pow(radius, 2);
  double Br2 = pow(otherCircle.radius, 2);

  double a = acos((Ar2 - Br2 + pow(distance, 2)) / (2 * distance * radius));
  double b = acos((Br2 - Ar2 + pow(distance, 2)) / (2 * distance * otherCircle.radius));

  return Ar2 * a + Br2 * b - radius * distance * sin(a);
}
