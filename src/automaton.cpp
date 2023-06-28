#include "automaton.hpp"
#include <cmath>
#include <stdexcept>

sir::Automaton::Automaton(int N, int T, double beta, double gamma, double seed) {
  if (!(gamma >= 0 && gamma <= 1) || !(beta >= 0 && beta <= 1)) {
    throw std::invalid_argument(
        "gamma e beta invalidi, devo essere compresi tra 0 e 1");
  } else if (T <= 0) {
    throw std::invalid_argument("il numero di giorni è un numero naturale");
  } else if (N <= 0) {
    throw std::invalid_argument("il numero di persone è un numero naturale o è troppo piccolo");
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
  N_ = 0;
  T_ = 0;
  beta_ = 0.;
  gamma_ = 0.;
  seed_ = 0.;
  eng_.seed(seed_);
  size_ = 0;
}

void sir::Automaton::setSeed(double seed) { seed_ = seed; }
void sir::Automaton::setBeta(double beta) {
  if ( !(beta >= 0 && beta <= 1)) {
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
  if (T <= 0) {
    throw std::invalid_argument("il numero di giorni è un numero naturale");
  }
  T_ = T; 
}
void sir::Automaton::setN(int N) {
 if (N <=0) {
    throw std::invalid_argument("il numero di persone è un numero naturale o è troppo piccolo");
  }
  N_ = N;
  size_ = std::round(std::sqrt(N_));
  if (size_ * size_ < N_) {
    size_ += 1;
  }
}
void sir::Automaton::setMap() {
  map_.clear();
  state_ = sir::SIR(0, 0,0);
  int person;
  int count{0};
  int count_i{0};
  std::uniform_int_distribution<> roll_people(1, 3);

  while (count < N_) {
    person = roll_people(eng_);
    switch (person) {
      case 1:
        map_.push_back('s');
        state_.S+=1;
        count++;
        break;
      case 2:
        map_.push_back('i');
        count++;
        count_i++;
        state_.I+=1;
        break;
      case 3:
        map_.push_back('r');
        count++;
        state_.R +=1;
        break;
    }
  }

  if (count_i == 0) {
    person = roll_people(eng_);
    map_[(person * N_ / 3) - 1] = 'i';
  }
}

double sir::Automaton::getBeta() const { return beta_; }
double sir::Automaton::getGamma() const { return gamma_; }
int sir::Automaton::getT() const { return T_; }
int sir::Automaton::getN() const { return N_; }
double sir::Automaton::getSeed() const { return seed_; }
std::vector<char> sir::Automaton::getMap() const{ return map_;}
int sir::Automaton::getSize() const { return size_;}
sir::SIR sir::Automaton::getState() const{ return state_;}

char sir::Automaton::changeStatePerson(int index) {
  int count_i{0};
  std::uniform_real_distribution<> roll_probability(
      1., 3.5);  

  if (index % size_ != 0 && map_[index - 1] == 'i') {
    count_i += 1;
  }
  if (index + 1 < N_ && (index + 1) % size_ != 0 &&
      map_[index + 1] == 'i') {
    count_i += 1;
  }
  if (index + size_ < N_ && map_[index + size_] == 'i') {
    count_i += 1;
  }
  if (index - size_ > 0 && map_[index - size_] == 'i') {
    count_i += 1;
  }

  double prob;

  if (map_[index] == 's') {
    auto x = roll_probability(eng_);
    prob = count_i * beta_ * x;
    if (prob > 0.7) {
      state_.I+=1;
      return 'i';
    } else {
      state_.S+=1;
      return 's';
    }
  } else {
    auto x = roll_probability(eng_);
    prob = gamma_ * x;
    if (prob > 0.6) {
      state_.R+=1;
      return 'r';
    } else {
      state_.I +=1;
      return 'i';
      
    }
  }
}

void sir::Automaton::evolve() {
  std::vector<char> mapChange(map_);
  char change;
  state_ = sir::SIR(0,0,0);
  for (int count = 0; count < N_; count++) {
    if (mapChange[count] != 'r') {
      change = changeStatePerson(count);
      map_[count] = change;
    } else {
      map_[count] = 'r';
      state_.R+=1;
    }
  }
  if((state_.S+state_.I+state_.R) != N_){
    throw std::runtime_error("errore nella simulazione dell'automaton");
  }
}