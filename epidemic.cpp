#include "epidemic.hpp"

#include <stdexcept>

sir::Epidemic::Epidemic(sir::SIR firstState, double beta, double gamma, int T) {
  if (!(gamma >= 0 && gamma <= 1) || !(beta >= 0 && beta <= 1)) {
    throw std::invalid_argument(
        "gamma e beta invalidi, devo essere compresi tra 0 e 1");
  }
  state_.push_back(firstState);
  beta_ = beta;
  gamma_ = gamma;
  T_ = T;
  N_ = firstState.S + firstState.I + firstState.R;
};
sir::Epidemic::Epidemic() {
  state_.push_back(sir::SIR{0, 0, 0});
  beta_ = 0.;
  gamma_ = 1.;
  T_ = 0;
  N_ = 0;
};

void sir::Epidemic::setFirstState(sir::SIR firstState) {
  state_[0] = firstState;
  N_ = firstState.S + firstState.I + firstState.R;
};
void sir::Epidemic::setBetaGamma(double beta, double gamma) {
  if (!(gamma >= 0 && gamma <= 1) || !(beta >= 0 && beta <= 1)) {
    throw std::invalid_argument(
        "gamma e beta invalidi, devo essere compresi tra 0 e 1");
  }
  beta_ = beta;
  gamma_ = gamma;
};
void sir::Epidemic::setT(int T) { T_ = T; };

std::vector<sir::SIR> sir::Epidemic::getState() const { return state_; }
int sir::Epidemic::getT() const { return T_; }