#include "epidemic.hpp"
#include <iostream>
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
  if(state_.empty()){
    state_.push_back(firstState);
  } else {
    state_[0] = firstState;
  }
  
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
int sir::Epidemic::getN() const { return N_; }

void sir::Epidemic::evolve(){
  for(int i=0; i< T_; i++){
    sir::SIR new_sir{0, 0, 0};
    new_sir.S = sir::update_s(state_[i],  beta_,  N_);
    new_sir.I = sir::update_i(state_[i],  beta_,  gamma_,  N_);
    new_sir.R = sir::update_r(state_[i],new_sir.S, new_sir.I, gamma_);
  
    /*bool sir::control_sir(sir::SIR state_[i], int N) {
    return (new_sir.S + new_sir.I + new_sir.R == N);*/
    //std::cout <<new_sir.S << " " << new_sir.I << " " << new_sir.R << "\n";
    if(sir::control_sir(new_sir,  N_) == true){
      state_.push_back(new_sir);
    }else {
      state_.push_back(state_[i]);
    }
  }
}