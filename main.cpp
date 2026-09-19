#include <iostream>
#include <pthread.h>
#include <random>
#include <cstring>
#include <vector>

bool isInside(double x, double y, double r)
{
  return ((x - r) * (x - r) + (y - r) * (y - r)) <= (r * r);
}

size_t calc(double r, size_t tests, size_t seed)
{
  std::mt19937_64 g(seed);
  std::uniform_real_distribution<double> d(0.0, r * 2.0);
  size_t res = 0;
  for (size_t i = 0; i < tests; ++i)
  {
    double x = d(g);
    double y = d(g);
    if (isInside(x, y, r))
    {
      res++;
    }
  }
  return res;
}

struct Data
{
  double r;
  size_t tests;
  size_t seed;
};

double area(double r, size_t threads, size_t tests)
{
  std::vector<pthread_t> threadVec(threads);
  size_t blockSize = tests / threads;
  size_t remainingBlock = tests % threads;
  std::random_device rd;
  std::vector<Data> dataVec(threads);

  for (size_t i = 0; i < threads; ++i)
  {
    dataVec[i].r = r;
    dataVec[i].tests = blockSize;
    dataVec[i].seed = rd();
    int err = pthread_create(&threadVec[i], nullptr, reinterpret_cast<void*(*)(void*)>(calc), &dataVec[i]);
    if (err)
    {
      std::cerr << strerror(err) << "\n";
    }
  } 
  size_t res = 0;
  for (size_t i = 0; i < threads; ++i)
  {
    void* result = nullptr;
    int err = pthread_join(threadVec[i], &result);
    if (err)
    {
      std::cerr << strerror(err) << "\n";
    }
    res += reinterpret_cast<size_t>(result);
  }
  return (static_cast<double>(res)/tests)*(4.0*r*r);
}

int main()
{
  std::cout << area(5.0, 8, 1000000);
  return 0;
}
