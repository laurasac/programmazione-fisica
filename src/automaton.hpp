#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP
#include <random>
#include <vector>

#include "sir.hpp"
namespace sir {
class Automaton {
  std::vector<char> map_;
  std::default_random_engine eng_;
  sir::SIR state_{0, 0, 0};
  int size_;
  int T_;
  int N_;
  double beta_;
  double gamma_;
  double seed_;

 public:
  Automaton(int N, int T, double beta, double gamma, double seed);
  Automaton();

  char changeStatePerson(int index, std::vector<char>& map);
  void evolve();

  void setSeed(double seed);
  void setBeta(double beta);
  void setGamma(double gamma);
  void setT(int T);
  void setN(int N);
  void setMap();

  double getBeta() const;
  double getGamma() const;
  int getT() const;
  int getN() const;
  int getSize() const;
  double getSeed() const;
  std::vector<char> getMap() const;
  sir::SIR getState() const;
};

}  // namespace sir
#endif
