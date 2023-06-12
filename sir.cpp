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
int sir::update_r(sir::SIR& old_sir, int new_s, int new_i, float gamma) {
  int new_r_1 = old_sir.R + (gamma * old_sir.I);
  int new_r_2 = std::round(old_sir.R + (gamma * old_sir.I));
  int n = old_sir.S+ old_sir.I + old_sir.R;
  if((new_r_1 + new_s + new_i ) == n){
    return new_r_1;
  } else {
    return new_r_2;
  }
}
bool sir::control_sir(sir::SIR& sir, int N) {

   return (sir.S + sir.I + sir.R == N);
}

void sir::print_sir(sir::SIR& old_sir) {
  std::cout << "Il numero di S (individui suscettibili) è: " << old_sir.S
            << '\n';
  std::cout << "Il numero di I (individui suscettibili) è: " << old_sir.I
            << '\n';
  std::cout << "Il numero di R (individui suscettibili) è: " << old_sir.R
            << '\n';
}
