#include "input_ouput.hpp"
#include "epidemic.hpp"
#include <stdexcept>

int main(int argc, char *argv[]) {
    try{
      sir::Epidemic epidemic;
      sir::input(argc, argv, epidemic);
      sir::outputTable(epidemic);
    } catch(std::invalid_argument& e){
      throw e;
    }
}