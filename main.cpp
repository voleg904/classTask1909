#include <iostream>
#include <pthread.h>

double area(double r, size_t threads, size_t tests);
size_t calc(double r, size_t tests, size_t seed);
bool isInside(double x, double y, double r)
{
  return ((x - r) * (x - r) + (y - r) * (y - r)) <= (r * r);
}

int main()
{
  return 0;
}
