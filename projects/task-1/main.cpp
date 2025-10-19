#include <iostream>
#include <string>
#include <random>
#include <chrono>

double areaMonteCarlo(int r, int tries, int seed);

int main(int argc, char *argv[])
{
  int tries = std::stoi(argv[1]);
  int seed = 0;
  int radius = 0, threadsCnt = 0;
  std::chrono::steady_clock timer;
  while (!std::cin.eof())
  {
    std::cin >> radius >> threadsCnt;
    auto start = timer.now();
    double area = areaMonteCarlo(radius, tries, 0);
    auto end = timer.now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " " << area << "\n";
  }
}

double areaMonteCarlo(int r, int tries, int seed = 0)
{
  std::mt19937 coordGenerator(20);
  std::uniform_real_distribution< double > dist(0, r);
  size_t cntGood = 0;
  for (size_t i = 0; i < tries; i++)
  {
    double coordX = dist(coordGenerator), coordY = dist(coordGenerator);
    if ((coordX * coordX + coordY * coordY) <= r * r)
    {
      cntGood++;
    }
  }
  return static_cast< double >(cntGood) / (tries) * 4 * r * r;
}