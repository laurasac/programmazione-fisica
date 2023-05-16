#include <fstream>
#include <iostream>

#include "epidemic.hpp"
#include "input_ouput.hpp"

void sir::inputCin(sir::Epidemic& epidemic) {
  float gamma{0.};
  float beta{0.};
  sir::SIR state{0, 0, 0};
  int T{0};
  // trova un modo per controllare se il dato preso è un double od un int
  std::cout << "Simulatore di una epidemia tramite il modello SIR. Si "
               "richiede si inserire i seguenti valoti"
            << "\n";
  std::cout << "\n"
            << "S, ovvero le persone che possono essere infettate: ";
  std::cin >> state.S;
  std::cout << "\n"
            << "I, ovvero le persone infette: ";
  std::cin >> state.I;
  std::cout << "\n"
            << "R, ovvero le persone guarite, decedute o in isolamento: ";
  std::cin >> state.R;
  std::cout << "\n"
            << "T, il numero di giorni della simulazione: ";
  std::cin >> T;
  std::cout << "\n"
            << "beta, probabilità di contagio: ";
  std::cin >> beta;
  std::cout << "\n"
            << "gamma, probabilità di morte o guarigione: ";
  std::cin >> gamma;
  epidemic.setFirstState(state);
  epidemic.setBetaGamma(beta, gamma);
  epidemic.setT(T);
};

void sir::inputFile(std::string filename, sir::Epidemic& epidemic) {
  float gamma{0.};
  float beta{0.};
  sir::SIR state{0, 0, 0};

  std::ifstream file{filename};
  std::string row;
  std::getline(file, row, '\n');
  state.S = std::stoi(row);
  std::getline(file, row, '\n');
  state.I = std::stoi(row);
  std::getline(file, row, '\n');
  state.R = std::stoi(row);  // trova un modo per splittare le stringe
  std::getline(file, row, '\n');
  epidemic.setT(std::stoi(row));
  std::getline(file, row, '\n');
  beta = std::stod(row);
  std::getline(file, row, '\n');
  gamma = std::stod(row);

  epidemic.setFirstState(state);
  epidemic.setBetaGamma(beta, gamma);
};
void sir::inputCommand(char* argv[], sir::Epidemic& epidemic) {
  epidemic.setFirstState(
      sir::SIR{std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4])});
  epidemic.setBetaGamma(std::stod(argv[6]), std::stod(argv[7]));
  epidemic.setT(
      std::stoi(argv[5]));  //// trova un modo per usare il finde con le liste
};
void sir::input(int argc, char* argv[], sir::Epidemic& epidemic) {
  try {
    if (argc == 1) {
      sir::inputCin(epidemic);
    } else if (std::string(argv[1]) == "-f") {
      sir::inputFile(argv[2], epidemic);
    } else if (std::string(argv[1]) == "-c") {
      sir::inputCommand(argv, epidemic);
    }
  } catch (std::invalid_argument& e) {
    throw e;
  }
};

void sir::outputTable(sir::Epidemic& epidemic) {
  std::vector<sir::SIR> state{epidemic.getState()};
  std::cout << "  T  |  S  |  I  |  R  "
            << "\n";
  std::cout << "-----------------------\n";
  for (int i = 0; i <= epidemic.getT(); i++) {
    std::cout << "  " << i << "  |  " << state[i].S << "  |"
              << "  " << state[i].I << "  |  " << state[i].R << "  "
              << "\n";
    std::cout << "-----------------------\n";
  }
}