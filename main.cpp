#include <stdexcept>
#include "src/epidemic.hpp"
#include "src/io.hpp"
#include "src/graph.hpp"
#include "src/automaton.hpp"



int main(int argc, char *argv[]) {
  try{
    int mode;
    sir::Epidemic epidemic;
    sir::Automaton automaton;
    mode = sir::input(argc, argv, epidemic, automaton);
    if(mode == 1 ){
      epidemic.evolve();
      sir::outputTable(epidemic);
      sir::renderWindow(1000, 1000, 40, epidemic);
    } else if (mode == 2){
      sir::renderWindow(1000,1000,50, automaton);
    }
    
  } catch(const std::invalid_argument& e){
    throw e;
  }
   catch(const std::runtime_error& e){
    throw e;
  }
}
