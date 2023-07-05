#include "automaton.hpp"

#include <cmath>
#include <stdexcept>

sir::Automaton::Automaton(int N, int T, double beta, double gamma,
                          double seed) {
  if (!(gamma >= 0 && gamma <= 1) || !(beta >= 0 && beta <= 1)) {
    throw std::invalid_argument(
        "gamma e beta invalidi, devo essere compresi tra 0 e 1");
  } else if (T <= 0 || T > 1000) {
    throw std::invalid_argument(
        "il numero di giorni è troppo piccolo o troppo grande");
  } else if (N <= 0 || N > 1000) {
    throw std::invalid_argument(
        "il numero di persone è troppo piccolo o troppo grande");
  }

  N_ = N;
  T_ = T;
  beta_ = beta;
  gamma_ = gamma;
  seed_ = seed;
  eng_.seed(seed_);
  size_ = std::round(std::sqrt(N_));
  if (size_ * size_ < N_) {
    size_ += 1;
  }
  this->setMap();
}
sir::Automaton::Automaton() {
  N_ = 1;
  T_ = 1;
  beta_ = 0.;
  gamma_ = 0.;
  seed_ = 0.;
  eng_.seed(seed_);
  size_ = 1;
  map_.push_back('s');
  state_.S = 1;
}

void sir::Automaton::setSeed(double seed) { seed_ = seed; }
void sir::Automaton::setBeta(double beta) {
  if (!(beta >= 0 && beta <= 1)) {
    throw std::invalid_argument(
        "beta invalido, deve essere compreso tra 0 e 1");
  }
  beta_ = beta;
}
void sir::Automaton::setGamma(double gamma) {
  if (!(gamma >= 0 && gamma <= 1)) {
    throw std::invalid_argument(
        "gamma invalido, deve essere compreso tra 0 e 1");
  }
  gamma_ = gamma;
}

void sir::Automaton::setT(int T) {
  if (T <= 0 || T > 1000) {
    throw std::invalid_argument(
        "il numero di giorni è troppo piccolo o troppo grande");
  }
  T_ = T;
}
void sir::Automaton::setN(int N) {
  if (N <= 0 || N > 1000) {
    throw std::invalid_argument(
        "il numero di persone è troppo piccolo o troppo grande");
  }
  N_ = N;
  size_ = std::round(std::sqrt(N_));
  if (size_ * size_ < N_) {
    size_ += 1;
  }
}
void sir::Automaton::setMap() {
  map_.clear();
  state_ = sir::SIR{0, 0, 0};
  int person;
  int count{0};
  int count_i{0};
  std::uniform_int_distribution<> rollPeople(1, 3);

  while (count < N_) {
    person = rollPeople(eng_);
    switch (person) {
      case 1:
        map_.push_back('s');
        state_.S += 1;
        count++;
        break;
      case 2:
        map_.push_back('i');
        count++;
        count_i++;
        state_.I += 1;
        break;
      case 3:
        map_.push_back('r');
        count++;
        state_.R += 1;
        break;
    }
  }

  if (count_i == 0 && N_ >= 3) {
    person = rollPeople(eng_);
    map_[(person * N_ / 3) - 1] = 'i';
  } else if (count_i == 0 && N_ < 3) {
    map_[0] = 'i';
  }
}

double sir::Automaton::getBeta() const { return beta_; }
double sir::Automaton::getGamma() const { return gamma_; }
int sir::Automaton::getT() const { return T_; }
int sir::Automaton::getN() const { return N_; }
double sir::Automaton::getSeed() const { return seed_; }
std::vector<char> sir::Automaton::getMap() const { return map_; }
int sir::Automaton::getSize() const { return size_; }
sir::SIR sir::Automaton::getState() const { return state_; }

char sir::Automaton::changeStatePerson(int index, std::vector<char>& map) {
  std::uniform_real_distribution<> rollProbability(1., 3.5);
  double prob;

  if (map[index] == 's') {
    int countI{0};
    if (index % size_ != 0 && map[index - 1] == 'i') {
      countI += 1;
    }
    if (index + 1 < N_ && (index + 1) % size_ != 0 && map[index + 1] == 'i') {
      countI += 1;
    }
    if (index + size_ < N_ && map[index + size_] == 'i') {
      countI += 1;
    }
    if (index - size_ > 0 && map[index - size_] == 'i') {
      countI += 1;
    }

    prob = countI * beta_ * rollProbability(eng_);

    if (prob > 0.7) {
      state_.I += 1;
      return 'i';
    } else {
      state_.S += 1;
      return 's';
    }
  } else if (map[index] == 'i') {
    prob = gamma_ * rollProbability(eng_);
    if (prob > 0.6) {
      state_.R += 1;
      return 'r';
    } else {
      state_.I += 1;
      return 'i';
    }
  } else {
    state_.R += 1;
    return 'r';
  }
}

void sir::Automaton::evolve() {
  std::vector<char> oldMap(map_);
  state_ = sir::SIR{0, 0, 0};
  for (int count = 0; count < N_; count++) {
    map_[count] = changeStatePerson(count, oldMap);
  }
  if ((state_.S + state_.I + state_.R) != N_) {
    throw std::runtime_error("errore nella simulazione dell'automaton");
  }
}