#include <stdexcept>
#include "epidemic.hpp"
#include "io.hpp"
#include "graph.hpp"


int main(int argc, char *argv[]) {
  try{
    sir::Epidemic epidemic;
    sir::input(argc, argv, epidemic);
    epidemic.evolve();
    sir::outputTable(epidemic);
    sir::render_window(1000, 1000, 40, epidemic);
  } catch(std::invalid_argument& e){
    throw e;
  }
   catch(std::runtime_error& e){
    throw e;
  }
}
