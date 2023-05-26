#ifndef INPUT_OUTPUT_HPP
#define INPUT_OUTPUT_HPP
#include <string>

#include "epidemic.hpp"
namespace sir {
void inputCin(sir::Epidemic& epidemic);
void inputFile(std::string filename, sir::Epidemic& epidemic);
void inputCommand(char* argv[], sir::Epidemic& epidemic);
void input(int argc, char* argv[], sir::Epidemic& epidemic);
void outputTable(sir::Epidemic& epidemic);
}  // namespace sir
#endif