#include <stdexcept>
#include <vector>
#include "epidemic.hpp"
#include "io.hpp"

int main(int argc, char *argv[]) {
  try{
    sir::Epidemic epidemic;
    sir::input(argc, argv, epidemic);
    sir::outputTable(epidemic);
  } catch(std::invalid_argument& e){
    throw e;
  }
}
