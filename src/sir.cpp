#include "sir.hpp"

#include <cmath>

int sir::updateS(sir::SIR& oldSir, double beta, int N) {
  int newS = std::round(oldSir.S * std::exp(-beta * oldSir.I / N));
  return newS;
}

int sir::updateI(sir::SIR& oldSir, double beta, double gamma, int N) {
  int newI = std::round(oldSir.I * std::exp((beta * oldSir.S / N) - gamma));
  return newI;
}

int sir::updateR(int newS, int newI, int N) { return (N - newS - newI); }

bool sir::controlSIR(sir::SIR& sir) {
  if ((sir.S + sir.I + sir.R) == 0) {
    return false;
  } else if (sir.S >= 0 && sir.I >= 0 && sir.R >= 0) {
    return true;
  } else {
    return false;
  }
}
