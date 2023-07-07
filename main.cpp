#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "src/automaton.hpp"
#include "src/epidemic.hpp"
#include "src/graph.hpp"
#include "src/io.hpp"

int main(int argc, char* argv[]) {
  try {
    int mode;
    sir::Epidemic epidemic;
    sir::Automaton automaton;
    std::vector<std::string> commands(argv, argv + argc);
    mode = sir::input(argc, commands, epidemic, automaton);
    if (mode == 1) {
      epidemic.evolve();
      sir::outputTable(epidemic);
      sir::renderWindow(1000, 1000, 40, epidemic);
    } else if (mode == 2) {
      sir::renderWindow(1000, 1000, 50, automaton);
    }

  } catch (const std::invalid_argument& e) {
    std::cout << "Errore: " << e.what();
  } catch (const std::runtime_error& e) {
    std::cout << "Errore: " << e.what();
  }
}
