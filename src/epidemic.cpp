#include "epidemic.hpp"
#include <stdexcept>

sir::Epidemic::Epidemic(sir::SIR firstState, double beta, double gamma, int T) {
  
  if (!(gamma >= 0 && gamma <= 1) || !(beta >= 0 && beta <= 1)) {
    throw std::invalid_argument(
        "gamma e beta invalidi, devo essere compresi tra 0 e 1");
  } else if (!sir::controlSIR(firstState)) {
    throw std::invalid_argument(
        " i valori del sir devono essere numeri naturali");
  } else if (T <= 0) {
    throw std::invalid_argument("il numero di giorni è un numero naturale");
  }

  state_.push_back(firstState);
  beta_ = beta;
  gamma_ = gamma;
  T_ = T;
  N_ = firstState.S + firstState.I + firstState.R;
}
sir::Epidemic::Epidemic() {
  state_.push_back(sir::SIR{1, 0, 0});
  beta_ = 0.;
  gamma_ = 0.;
  T_ = 1;
  N_ = 1;
}

void sir::Epidemic::setFirstState(sir::SIR firstState) {
  if (!sir::controlSIR(firstState)) {
    throw std::invalid_argument(
        " i valori del sir devono essere numeri naturali");
  }
  state_.clear();
  state_.push_back(firstState);
  N_ = firstState.S + firstState.I + firstState.R;
}
void sir::Epidemic::setBeta(double beta) {
  if (!(beta >= 0 && beta <= 1)) {
    throw std::invalid_argument(
        "beta invalido, deve essere compreso tra 0 e 1");
  }
  beta_ = beta;
}
void sir::Epidemic::setGamma(double gamma) {
  if (!(gamma >= 0 && gamma <= 1) ) {
    throw std::invalid_argument(
        "gamma invalido, deve essere compreso tra 0 e 1");
  }
  gamma_ = gamma;
}
void sir::Epidemic::setT(int T) {
  if (T <= 0) {
    throw std::invalid_argument("il numero di giorni è un numero naturale");
  }
  T_ = T;
}

std::vector<sir::SIR> sir::Epidemic::getState() const { return state_; }
int sir::Epidemic::getT() const { return T_; }
int sir::Epidemic::getN() const { return N_; }
double sir::Epidemic::getBeta() const { return beta_; }
double sir::Epidemic::getGamma() const { return gamma_; }

void sir::Epidemic::evolve() {
  for (int i = 0; i < T_; i++) {
    sir::SIR newSIR(0, 0, 0);
    newSIR.S = sir::updateS(state_[i], beta_, N_);
    newSIR.I = sir::updateI(state_[i], beta_, gamma_, N_);
    newSIR.R = sir::updateR(newSIR.S, newSIR.I, N_);
    state_.push_back(newSIR);
  }
}