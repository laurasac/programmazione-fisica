#include "io.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

int sir::inputCin(sir::Epidemic& epidemic, sir::Automaton& automaton) {
  int mode;
  std::cout << "Simulatore di una epidemia. Si "
               "richiede di scegliere la modalità di evoluzione: \n1 Modello "
               "SIR\n2 Automa Cellulare"
            << "\n";
  std::cin >> mode;
  try {
    while (true) {
      if (mode == 1) {
        double gamma;
        double beta;
        sir::SIR state{0, 0, 0};
        int T;
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
        epidemic.setBeta(beta);
        epidemic.setGamma(gamma);
        epidemic.setT(T);
        return mode;
      } else if (mode == 2) {
        double gamma;
        double beta;
        double seed;
        int T;
        int N;
        std::cout
            << "\n"
            << "N, ovvero il numero di persone che costituiscono l'automaton ";
        std::cin >> N;
        std::cout << "\n"
                  << "T, il numero di giorni della simulazione: ";
        std::cin >> T;
        std::cout << "\n"
                  << "seed della simulazione: ";
        std::cin >> seed;
        std::cout << "\n"
                  << "beta, probabilità di contagio: ";
        std::cin >> beta;
        std::cout << "\n"
                  << "gamma, probabilità di morte o guarigione: ";
        std::cin >> gamma;

        automaton.setT(T);
        automaton.setN(N);
        automaton.setBeta(beta);
        automaton.setGamma(gamma);
        automaton.setSeed(seed);
        automaton.setMap();
        return mode;
      } else {
        std::cout << "Modalità non conosciuta, reinseire\n";
        std::cin >> mode;
      }
    }
  } catch (const std::invalid_argument& e) {
    throw e;
  }
}

int sir::inputFile(std::string filename, sir::Epidemic& epidemic,
                   sir::Automaton& automaton) {
  try {
    std::ifstream file{filename};
    if (file.fail()) {
      throw std::runtime_error(
          "il file non è stato trovato o  non è possibile aprirlo");
    }
    std::string row;
    std::getline(file, row, '\n');
    int mode{std::stoi(row)};
    if (mode == 1) {
      sir::SIR state{0, 0, 0};
      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }
      std::getline(file, row, '\n');
      state.S = std::stoi(row);

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }

      std::getline(file, row, '\n');
      state.I = std::stoi(row);

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }

      std::getline(file, row, '\n');
      state.R = std::stoi(row);
      epidemic.setFirstState(state);

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }

      std::getline(file, row, '\n');
      epidemic.setT(std::stoi(row));

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }

      std::getline(file, row, '\n');
      epidemic.setBeta(std::stod(row));

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }

      std::getline(file, row, '\n');
      epidemic.setGamma(std::stod(row));

    } else if (mode == 2) {
      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }
      std::getline(file, row, '\n');
      automaton.setN(std::stoi(row));

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }
      std::getline(file, row, '\n');
      automaton.setT(std::stoi(row));

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }
      std::getline(file, row, '\n');
      automaton.setSeed(std::stod(row));

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }
      std::getline(file, row, '\n');
      automaton.setBeta(std::stod(row));

      if (file.eof()) {
        throw std::invalid_argument("numero di dati troppo piccolo");
      }
      std::getline(file, row, '\n');
      automaton.setGamma(std::stod(row));
      automaton.setMap();
    } else {
      throw std::runtime_error("modalità di simulazione sconosciuta");
    }
    return mode;
  } catch (const std::invalid_argument& e) {
    throw e;
  } catch (const std::runtime_error& e) {
    throw e;
  }
}

int sir::inputCommand(int argc, char* argv[], sir::Epidemic& epidemic,
                      sir::Automaton& automaton) {
  try {
    if (!(std::strcmp(argv[2], "-mode=1")) && argc == 9) {
      epidemic.setFirstState(
          sir::SIR{std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5])});
      epidemic.setT(std::stoi(argv[6]));
      epidemic.setBeta(std::stod(argv[7]));
      epidemic.setGamma(std::stod(argv[8]));
      return 1;

    } else if (!(std::strcmp(argv[2], "-mode=2")) && argc == 8) {
      automaton.setN(std::stoi(argv[3]));
      automaton.setT(std::stoi(argv[4]));
      automaton.setSeed(std::stod(argv[5]));
      automaton.setBeta(std::stod(argv[6]));
      automaton.setGamma(std::stod(argv[7]));
      automaton.setMap();
      return 2;

    } else {
      throw std::runtime_error(
          "modalità di simulazione sconosciuta o numero di dati per "
          "l'iniziallizzazione errato");
    }
  } catch (const std::invalid_argument& e) {
    throw e;
  } catch (const std::runtime_error& e) {
    throw e;
  }
}

int sir::input(int argc, char* argv[], sir::Epidemic& epidemic,
               sir::Automaton& automaton) {
  try {
    if (argc == 1) {
      return sir::inputCin(epidemic, automaton);
    } else if (std::string(argv[1]) == "-f" && argc == 3) {
      return sir::inputFile(argv[2], epidemic, automaton);
    } else if (std::string(argv[1]) == "-c") {
      return sir::inputCommand(argc, argv, epidemic, automaton);
    } else {
      throw std::runtime_error("inizializzazione errata");
    }

  } catch (const std::invalid_argument& e) {
    throw e;
  } catch (const std::runtime_error& e) {
    throw e;
  }
}

void sir::outputTable(sir::Epidemic& epidemic) {
  std::vector<sir::SIR> state{epidemic.getState()};
  std::cout << "  T  |  S  |  I  |  R  "
            << "\n";
  std::cout << "-----------------------\n";
  for (unsigned long i = 0; i < state.size(); i++) {
    std::cout << "  " << i << "  |  " << state[i].S << "  |"
              << "  " << state[i].I << "  |  " << state[i].R << "  "
              << "\n";
    std::cout << "-----------------------\n";
  }
}