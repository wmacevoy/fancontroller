#include <Arduino.h>
#include <stdint.h>

#include "dmath.h"

// minimum
double dmin(double a, double b)
{
  return a<b?a:b;
}

// maximum
double dmax(double a, double b)
{
  return b<a?a:b;
}

// absolute value
double dabs(double x)
{
  return x >= 0 ? x : -x;
}

// floor: largest integer <= argument
double dfloor(double x)
{
  int64_t y=x;
  if (x < 0 && x != y) --y;
  return y;
}

// ceiling: smallest integer >= argument
double dceil(double x)
{
  int64_t y=x;
  if (x > 0 && x != y) ++y;
  return y;
}

// round: nearest integer, rounding up.
double dround(double x)
{
  return dfloor(x+0.5);
}

// constain: y=constrain(x,a,b) constrains x so a <= y <= b
double dconstrain(double x, double a, double b)
{
  if (x < a) {
    return a;
  } else if (b < x) {
    return b;
  } else {
    return x;
  }
}

// map: rescale x range so x0 maps to y0 and x1 maps to y1
double dmap(double x, double x0, double x1, double y0, double y1)
{
  double c1=x-x0;
  double c0=x1-x;
  return (c0*y0+c1*y1)/(c0+c1);
}

// map then constrain results to range of y0 and y1
double dconstrainmap(double x, double x0, double x1, double y0, double y1)
{
  double y;
  y = dmap(x,x0,x1,y0,y1);
  y = dconstrain(y,dmin(y0,y1),dmax(y0,y1));
  return y;
}
