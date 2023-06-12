#include <cmath>
#include <iostream>
#include <random>
#include <vector>

// vediamo se variare le condizioni per cui cambiano stato
char change_state(int index, std::vector<char>& state, int size, double beta,
                  double gamma, std::default_random_engine& eng) {
  int count_i{0};
  std::uniform_real_distribution<> roll_probability(
      1., 3.5);  // vediamo se rendere opzionali tali fattori

  if (index % size != 0 && state[index - 1] == 'i') {
    count_i += 1;
  }
  if (index + 1 < state.size() && (index + 1) % size != 0 &&
      state[index + 1] == 'i') {
    count_i += 1;
  }
  if (index + size < state.size() && state[index + size] == 'i') {
    count_i += 1;
  }
  if (index - size > 0 && state[index - size] == 'i') {
    count_i += 1;
  }

  double prob;

  if (state[index] == 's' && count_i != 0) {
    auto x = roll_probability(eng);
    // std::cout << x << "\n";
    prob = count_i * beta * x;
    if (prob > 0.2) {
      return 'i';
    } else {
      return 's';
    }
  } else {
    // vediamo cosa fare per le i
    auto x = roll_probability(eng);
    // std::cout << x << "\n";
    prob = gamma * x;
    if (prob > 0.2) {
      return 'r';
    } else {
      return 'i';
    }
  }
}

void print_map(std::vector<char>& state, int size) {
  for (int i = 0; i < state.size(); i++) {
    if (i % size == 0) {
      std::cout << "\n[" << state[i] << "]";
    } else {
      std::cout << "[" << state[i] << "]";
    }
  }
  std::cout << "\n";
}

int main() {
  int n;
  float seed;
  int t{10};
  double gamma{0.1};
  double beta{0.07};

  std::cout << "N: ";
  std::cin >> n;
  std::cout << "\nSeed: ";
  std::cin >> seed;

  std::default_random_engine eng;
  std::uniform_int_distribution<> roll_people(1, 3);

  std::vector<char> state;
  eng.seed(seed);

  int x;
  int count{0};
  int count_i{0};

  while (count < n) {
    x = roll_people(eng);
    switch (x) {
      case 1:
        state.push_back('s');
        count++;
        break;
      case 2:
        state.push_back('i');
        count++;
        count_i++;
        break;
      case 3:
        state.push_back('r');
        count++;
        break;
    }
  }

  if (count_i == 0) {
    x = roll_people(eng);
    state[(x * n / 3) - 1] = 'i';
  }

  int size;
  size = std::round(std::sqrt(n));
  if (size * size < n) {
    size += 1;
  }
  print_map(state, size);

  char change;
  std::vector<char> state_1;
  for (int i = 0; i < t; i++) {
    for (count = 0; count < state.size(); count++) {
      if (state[count] != 'r') {
        change = change_state(count, state, size, beta, gamma, eng);
        state_1.push_back(change);
      } else {
        state_1.push_back('r');
      }
    }
    state.swap(state_1);
    state_1.clear();
    print_map(state, size);
  }
}

// warning: comparison of integers of different signs: 'int' and
// 'std::vector<char>::size_type' (aka 'unsigned long')