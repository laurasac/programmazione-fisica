#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP
#include <vector>

#include "sir.hpp"

namespace sir {
class Epidemic {
  std::vector<sir::SIR> state_;
  double beta_;
  double gamma_;
  int T_;
  int N_;

 public:
  Epidemic(sir::SIR firstState, double beta, double gamma, int T);
  Epidemic();

  void setFirstState(sir::SIR firstState);
  void setBeta(double beta);
  void setGamma(double gamma);
  void setT(int T);

  std::vector<sir::SIR> getState() const;
  double getBeta() const;
  double getGamma() const;
  int getT() const;
  int getN() const;

  void evolve();
};
}  // namespace sir
#endif
