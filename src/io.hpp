#ifndef INPUT_OUTPUT_HPP
#define INPUT_OUTPUT_HPP
#include <string>

#include "automaton.hpp"
#include "epidemic.hpp"

namespace sir {
int inputCin(sir::Epidemic& epidemic, sir::Automaton& automaton);
int inputFile(std::string filename, sir::Epidemic& epidemic,
              sir::Automaton& automaton);
int inputCommand(int argc, char* argv[], sir::Epidemic& epidemic,
                 sir::Automaton& automaton);
int input(int argc, char* argv[], sir::Epidemic& epidemic,
          sir::Automaton& automaton);
void outputTable(sir::Epidemic& epidemic);
}  // namespace sir
#endif
