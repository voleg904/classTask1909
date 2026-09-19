#include <iostream>
#include <pthread.h>
#include <random>

double area(double r, size_t threads, size_t tests);
size_t calc(double r, size_t tests, size_t seed)
{
  std::mt19937_64 g(seed);
  std::uniform_real_distribution<double> d(0.0, r * 2,0);
  size_t res = 0;
  for (size_t i = 0; i < tests; ++i)
  {
    double x = d(gen);
    double y = d(gen);
    if (isInside(x, y, r))
    {
      res++;
    }
  }
  return res;
}
bool isInside(double x, double y, double r)
{
  return ((x - r) * (x - r) + (y - r) * (y - r)) <= (r * r);
}

int main()
{
  return 0;
}
