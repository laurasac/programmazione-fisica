#include "sir.hpp"
#include <cmath>
#include <iostream>

sir::SIR::SIR(int s, int i, int r){
  S = s;
  I = i;
  R = r;
}

int sir::update_s(sir::SIR& old_sir, float beta, int N) {
  int new_s = std::round(old_sir.S - (beta * old_sir.S * old_sir.I / N));
  return new_s ;
}

int sir::update_i(sir::SIR& old_sir, float beta, float gamma, int N) {
  int new_i =
      std::round(old_sir.I + (beta * old_sir.S * old_sir.I / N) - (gamma * old_sir.I));
  return new_i;
};
int sir::update_r(sir::SIR& old_sir, float gamma) {
  int new_r = std::round(old_sir.R + (gamma * old_sir.I));
  return new_r;
}
bool sir::control_sir(sir::SIR& old_sir, int N) {
  /*if (!(old_sir.S + old_sir.I + old_sir.R == N)) {
    throw std::invalid_argument("C'è stato un errore nella simulazione");
  }*/
   return (old_sir.S + old_sir.I + old_sir.R == N);
}

void sir::print_sir(sir::SIR& old_sir) {
  std::cout << "Il numero di S (individui suscettibili) è: " << old_sir.S
            << '\n';
  std::cout << "Il numero di I (individui suscettibili) è: " << old_sir.I
            << '\n';
  std::cout << "Il numero di R (individui suscettibili) è: " << old_sir.R
            << '\n';
}
