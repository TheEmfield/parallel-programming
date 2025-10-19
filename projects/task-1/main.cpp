#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <numeric>
#include <chrono>

double areaMonteCarlo(int r, int tries, int threadsCnt, int seed);
void partialGoodCounter(int partSize, int r, int seed, size_t &res);

int main(int argc, char *argv[])
{
  int tries = std::stoi(argv[1]);
  int seed = 0;
  if (argc == 3)
  {
    seed = std::stoi(argv[2]);
  } 
  int radius = 0, threadsCnt = 0;
  std::chrono::steady_clock timer;
  while (!std::cin.eof())
  {
    std::cin >> radius >> threadsCnt;
    auto start = timer.now();
    double area = areaMonteCarlo(radius, tries, threadsCnt, 0);
    auto end = timer.now();
    std::cout << std::chrono::duration_cast< std::chrono::milliseconds >(end - start).count() << " " << area << "\n";
  }
}

double areaMonteCarlo(int r, int tries, int threadsCnt, int seed = 0)
{
  size_t partSize = tries / threadsCnt;
  std::vector< std::thread > ths;
  ths.reserve(threadsCnt);
  std::vector< size_t > countGood(threadsCnt, 0);
  for (size_t i = 0; i < threadsCnt; i++)
  {
    ths.emplace_back(partialGoodCounter, partSize, r, seed, std::ref(countGood[i]));
  }

  for (auto &t: ths)
  {
    t.join();
  }

  size_t cntGood = std::accumulate(countGood.begin(), countGood.end(), 0);
  return static_cast< double >(cntGood) / (tries) * 4 * r * r;
}

void partialGoodCounter(int partSize, int r, int seed, size_t &res)
{
  std::mt19937 coordGenerator(seed);
  std::uniform_real_distribution<double> dist(0, r);
  size_t cntGood = 0;
  for (size_t i = 0; i < partSize; i++)
  {
    double coordX = dist(coordGenerator), coordY = dist(coordGenerator);
    if ((coordX * coordX + coordY * coordY) <= r * r)
    {
      cntGood++;
    }
  }
  res = cntGood;
}