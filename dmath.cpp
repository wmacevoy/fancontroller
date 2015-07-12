#include <Arduino.h>
#include <stdint.h>

#include "dmath.h"

double dmin(double a, double b)
{
  return a<b ? a : b;
}

double dmax(double a, double b)
{
  return b<a ? a : b;
}

double dabs(double x)
{
  return x >= 0 ? x : -x;
}

double dfloor(double x)
{
  int64_t y=x;
  if (x < 0 && x != y) --y;
  return y;
}

double dceil(double x)
{
  int64_t y=x;
  if (x > 0 && x != y) ++y;
  return y;
}

double dround(double x)
{
  return dfloor(x+0.5);
}

double dconstrain(double x, double a, double b)
{
  if (b < a) {
    return 0.5*(a+b);
  } else if (x < a) {
    return a;
  } else if (b < x) {
    return b;
  } else {
    return x;
  }
}

double dmap(double x, double x0, double x1, double y0, double y1)
{
  double c1=x-x0;
  double c0=x1-x;
  double c=c0+c1;
  c1=c1/c;
  c0=c0/c;
  return c0*y0+c1*y1;
}

double dconstrainmap(double x, double x0, double x1, double y0, double y1)
{
  double y;
  y = dmap(x,x0,x1,y0,y1);
  y = dconstrain(y,dmin(y0,y1),dmax(y0,y1));
  return y;
}
