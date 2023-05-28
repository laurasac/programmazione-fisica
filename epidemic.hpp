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
  void setBetaGamma(double beta, double gamma);
  void setT(int T);
  void evolve();
  std::vector<sir::SIR> getState() const;
  double getBeta() const;
  double getGamma() const;
  int getT() const;
  int getN() const;
};
}  // namespace sir
#endif
// fai qui i controlli su gamma e beta quando