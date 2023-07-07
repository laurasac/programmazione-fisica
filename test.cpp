#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include <vector>

#include "src/automaton.hpp"
#include "src/doctest.h"
#include "src/epidemic.hpp"
#include "src/io.hpp"
#include "src/sir.hpp"
// vedi se testare il setmap
TEST_CASE("test della struct SIR e delle sue funzioni") {
  SUBCASE("test della funzione updateS") {
    sir::SIR oldSir{10, 20, 70};
    double beta{0.5};
    int N{100};

    int newS{sir::updateS(oldSir, beta, N)};
    CHECK(newS == 9);
  }

  SUBCASE("test della funzione updateI") {
    sir::SIR oldSir{10, 20, 70};
    double beta{0.5};
    double gamma{1};
    int N{100};

    int newI{sir::updateI(oldSir, beta, gamma, N)};
    CHECK(newI == 8);
  }

  SUBCASE("test della funzione updateR") {
    int newS{9};
    int newI{20};
    int N{100};
    int newR{sir::updateR(newS, newI, N)};
    CHECK(newR == 71);
  }

  SUBCASE("test della funzione controlSir pt.1") {
    sir::SIR nullSIR{0, 0, 0};
    bool result{sir::controlSIR(nullSIR)};
    CHECK(result == false);
  }

  SUBCASE("test della funzione controlSir pt.2") {
    sir::SIR nullSIR{-7, 0, 0};
    bool result{sir::controlSIR(nullSIR)};
    CHECK(result == false);
  }

  SUBCASE("test della funzione controlSir pt.3") {
    sir::SIR nullSIR{-7, 4, 3};
    bool result{sir::controlSIR(nullSIR)};
    CHECK(result == false);
  }
}

TEST_CASE("test dell'automa") {
  SUBCASE("test inizializzazione corretta con costruttore parametrizzato") {
    sir::Automaton automaton{9, 10, 0.8, 0.4, 1};
    CHECK(automaton.getN() == 9);
    CHECK(automaton.getT() == 10);
    CHECK(automaton.getBeta() == doctest::Approx(0.8));
    CHECK(automaton.getGamma() == doctest::Approx(0.4));
    CHECK(automaton.getSeed() == doctest::Approx(1.0));
    CHECK(automaton.getSize() == 3);
  }

  SUBCASE("test inizializzazione corretta con costruttore di default") {
    sir::Automaton automaton;
    automaton.setN(9);
    automaton.setT(10);
    automaton.setBeta(0.8);
    automaton.setGamma(0.4);
    automaton.setSeed(0.1);
    CHECK(automaton.getN() == 9);
    CHECK(automaton.getT() == 10);
    CHECK(automaton.getBeta() == doctest::Approx(0.8));
    CHECK(automaton.getGamma() == doctest::Approx(0.4));
    CHECK(automaton.getSeed() == doctest::Approx(0.1));
    CHECK(automaton.getSize() == 3);
  }

  SUBCASE("test invalid beta") {
    CHECK_THROWS_WITH_AS(
        sir::Automaton(9, 10, -0.3, 0.4, 1),
        "gamma e beta invalidi, devo essere compresi tra 0 e 1",
        std::invalid_argument);
    CHECK_THROWS_WITH_AS(
        sir::Automaton(9, 10, 2, 0.4, 1),
        "gamma e beta invalidi, devo essere compresi tra 0 e 1",
        std::invalid_argument);

    sir::Automaton automaton;

    CHECK_THROWS_WITH_AS(automaton.setBeta(-0.5),
                         "beta invalido, deve essere compreso tra 0 e 1",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(automaton.setBeta(2),
                         "beta invalido, deve essere compreso tra 0 e 1",
                         std::invalid_argument);
  }

  SUBCASE("test invalid gamma") {
    CHECK_THROWS_WITH_AS(
        sir::Automaton(9, 10, 0.3, -0.4, 1),
        "gamma e beta invalidi, devo essere compresi tra 0 e 1",
        std::invalid_argument);
    CHECK_THROWS_WITH_AS(
        sir::Automaton(9, 10, 0.2, 4, 1),
        "gamma e beta invalidi, devo essere compresi tra 0 e 1",
        std::invalid_argument);

    sir::Automaton automaton;

    CHECK_THROWS_WITH_AS(automaton.setGamma(-0.5),
                         "gamma invalido, deve essere compreso tra 0 e 1",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(automaton.setGamma(2),
                         "gamma invalido, deve essere compreso tra 0 e 1",
                         std::invalid_argument);
  }

  SUBCASE("test invalid N") {
    CHECK_THROWS_WITH_AS(
        sir::Automaton(-8, 10, 0.3, 0.4, 1),
        "il numero di persone è troppo piccolo o troppo grande",
        std::invalid_argument);
    CHECK_THROWS_WITH_AS(
        sir::Automaton(100000, 10, 0.2, 0.4, 1),
        "il numero di persone è troppo piccolo o troppo grande",
        std::invalid_argument);

    sir::Automaton automaton;

    CHECK_THROWS_WITH_AS(
        automaton.setN(-5),
        "il numero di persone è troppo piccolo o troppo grande",
        std::invalid_argument);
    CHECK_THROWS_WITH_AS(
        automaton.setN(20000000),
        "il numero di persone è troppo piccolo o troppo grande",
        std::invalid_argument);
  }

  SUBCASE("test invalid T") {
    CHECK_THROWS_WITH_AS(sir::Automaton(9, 0, 0.3, 0.4, 1),
                         "il numero di giorni è troppo piccolo o troppo grande",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(sir::Automaton(10, 10000000, 0.2, 0.4, 1),
                         "il numero di giorni è troppo piccolo o troppo grande",
                         std::invalid_argument);

    sir::Automaton automaton;

    CHECK_THROWS_WITH_AS(automaton.setT(-5),
                         "il numero di giorni è troppo piccolo o troppo grande",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(automaton.setT(20000000),
                         "il numero di giorni è troppo piccolo o troppo grande",
                         std::invalid_argument);
  }

  SUBCASE("test changeStatePerson") {
    sir::Automaton automaton(9, 10, 0.3, 0.4, 1);
    auto map = automaton.getMap();
    CHECK(automaton.changeStatePerson(4, map) == 's');
    CHECK(automaton.changeStatePerson(2, map) == 'r');
  }

  SUBCASE("test evolve") {
    sir::Automaton automaton(9, 10, 0.3, 0.4, 1);
    automaton.evolve();
    auto map = automaton.getMap();
    CHECK(map[1] == 'i');
    CHECK(map[3] == 's');
    CHECK(map[4] == 'i');
  }
}

TEST_CASE("test dell'epidemia") {
  SUBCASE("test inizializzazione corretta con costruttore parametrizzato") {
    sir::Epidemic epidemic{sir::SIR{10, 9, 8}, 0.7, 0.4, 10};
    auto firstState{epidemic.getState()[0]};
    CHECK(epidemic.getN() == 27);
    CHECK(epidemic.getT() == 10);
    CHECK(epidemic.getBeta() == doctest::Approx(0.7));
    CHECK(epidemic.getGamma() == doctest::Approx(0.4));
    CHECK(firstState.S == 10);
    CHECK(firstState.I == 9);
    CHECK(firstState.R == 8);
  }

  SUBCASE("test inizializzazione corretta con costruttore di default") {
    sir::Epidemic epidemic;
    epidemic.setFirstState(sir::SIR{10, 9, 8});
    epidemic.setT(10);
    epidemic.setBeta(0.7);
    epidemic.setGamma(0.4);

    auto firstState{epidemic.getState()[0]};
    CHECK(epidemic.getN() == 27);
    CHECK(epidemic.getT() == 10);
    CHECK(epidemic.getBeta() == doctest::Approx(0.7));
    CHECK(epidemic.getGamma() == doctest::Approx(0.4));
    CHECK(firstState.S == 10);
    CHECK(firstState.I == 9);
    CHECK(firstState.R == 8);
  }

  SUBCASE("test invalid beta") {
    CHECK_THROWS_WITH_AS(
        sir::Epidemic(sir::SIR{100, 50, 30}, -0.3, 0.4, 10),
        "gamma e beta invalidi, devo essere compresi tra 0 e 1",
        std::invalid_argument);
    CHECK_THROWS_WITH_AS(
        sir::Epidemic(sir::SIR{100, 50, 30}, 2, 0.4, 10),
        "gamma e beta invalidi, devo essere compresi tra 0 e 1",
        std::invalid_argument);

    sir::Epidemic epidemic;

    CHECK_THROWS_WITH_AS(epidemic.setBeta(-0.5),
                         "beta invalido, deve essere compreso tra 0 e 1",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(epidemic.setBeta(2),
                         "beta invalido, deve essere compreso tra 0 e 1",
                         std::invalid_argument);
  }

  SUBCASE("test invalid gamma") {
    CHECK_THROWS_WITH_AS(
        sir::Epidemic(sir::SIR{100, 50, 30}, 0.3, -0.4, 10),
        "gamma e beta invalidi, devo essere compresi tra 0 e 1",
        std::invalid_argument);
    CHECK_THROWS_WITH_AS(
        sir::Epidemic(sir::SIR{100, 50, 30}, 0.3, 2, 10),
        "gamma e beta invalidi, devo essere compresi tra 0 e 1",
        std::invalid_argument);

    sir::Epidemic epidemic;

    CHECK_THROWS_WITH_AS(epidemic.setGamma(-0.3),
                         "gamma invalido, deve essere compreso tra 0 e 1",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(epidemic.setGamma(2),
                         "gamma invalido, deve essere compreso tra 0 e 1",
                         std::invalid_argument);
  }

  SUBCASE("test invalid T") {
    CHECK_THROWS_WITH_AS(sir::Epidemic(sir::SIR{100, 50, 30}, 0.3, 0.4, 0),
                         "il numero di giorni troppo piccolo o troppo grande",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(
        sir::Epidemic(sir::SIR{100, 50, 30}, 0.5, 0.4, 10000000),
        "il numero di giorni troppo piccolo o troppo grande",
        std::invalid_argument);

    sir::Epidemic epidemic;

    CHECK_THROWS_WITH_AS(epidemic.setT(-5),
                         "il numero di giorni troppo piccolo o troppo grande",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(epidemic.setT(39930293),
                         "il numero di giorni troppo piccolo o troppo grande",
                         std::invalid_argument);
  }

  SUBCASE("test invalid firstState") {
    CHECK_THROWS_WITH_AS(sir::Epidemic(sir::SIR{-100, 50, 30}, 0.3, 0.4, 4),
                         "i valori del sir devono essere numeri naturali",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(
        sir::Epidemic(sir::SIR{100, 838383874, 30}, 0.5, 0.4, 4),
        "il numero di persone per la simulazione è troppo alto",
        std::invalid_argument);

    sir::Epidemic epidemic;

    CHECK_THROWS_WITH_AS(epidemic.setFirstState(sir::SIR{0, 0, 0}),
                         "i valori del sir devono essere numeri naturali",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(epidemic.setFirstState(sir::SIR{-100, 50, 50}),
                         "i valori del sir devono essere numeri naturali",
                         std::invalid_argument);
  }

  SUBCASE("test evolve") {
    sir::Epidemic epidemic{sir::SIR{57, 23, 40}, 0.3, 0.4, 2};
    epidemic.evolve();        // 120
    auto state = epidemic.getState();
    CHECK(state[1].S == 54);  // 54
    CHECK(state[1].I == 18);  // 18
    CHECK(state[1].R == 48);  // 48
    CHECK(state[2].S == 52);  // 52
    CHECK(state[2].I == 14);  // 14
    CHECK(state[2].R == 54);  // 54
  }
}

TEST_CASE("test della presa dati IO |inputCommand") {
  SUBCASE("mode 1 valid arg") {
    int arg{9};
    std::vector<std::string> argv{"",   "",   "-mode=1", "100", "50",
                                  "25", "10", "0.3",     "0.4"};
    sir::Epidemic epidemic;
    sir::Automaton automaton;

    int result{sir::inputCommand(arg, argv, epidemic, automaton)};
    CHECK(result == 1);
    CHECK(epidemic.getT() == 10);
    CHECK(epidemic.getBeta() == doctest::Approx(0.3));
    CHECK(epidemic.getGamma() == doctest::Approx(0.4));

    auto firstState{epidemic.getState()[0]};

    CHECK(firstState.S == 100);
    CHECK(firstState.I == 50);
    CHECK(firstState.R == 25);
  }

  SUBCASE("mode 2 valid arg") {
    int arg{8};
    std::vector<std::string> argv{"",   "",  "-mode=2", "100",
                                  "10", "1", "0.5",     "0.7"};
    sir::Epidemic epidemic;
    sir::Automaton automaton;

    int result{sir::inputCommand(arg, argv, epidemic, automaton)};
    CHECK(result == 2);
    CHECK(automaton.getT() == 10);
    CHECK(automaton.getN() == 100);
    CHECK(automaton.getSeed() == doctest::Approx(1.0));
    CHECK(automaton.getBeta() == doctest::Approx(0.5));
    CHECK(automaton.getGamma() == doctest::Approx(0.7));

    auto state = automaton.getState();
    CHECK(state.S == 33);
    CHECK(state.I == 23);
    CHECK(state.R == 44);
  }

  SUBCASE("Test invalid command pt.1") {
    int arg{7};
    std::vector<std::string> argv{"", "", "-mode=2", "100", "10", "1", "0.5"};
    sir::Epidemic epidemic;
    sir::Automaton automaton;
    CHECK_THROWS_WITH_AS(sir::inputCommand(arg, argv, epidemic, automaton),
                         "modalità di simulazione sconosciuta o numero di dati "
                         "per l'iniziallizzazione errato",
                         std::runtime_error);
  }

  SUBCASE("Test invalid command pt.2") {
    int arg{8};
    std::vector<std::string> argv{"",   "",  "-mode=3", "100",
                                  "10", "1", "0.5",     "0.8"};
    sir::Epidemic epidemic;
    sir::Automaton automaton;
    CHECK_THROWS_WITH_AS(sir::inputCommand(arg, argv, epidemic, automaton),
                         "modalità di simulazione sconosciuta o numero di dati "
                         "per l'iniziallizzazione errato",
                         std::runtime_error);
  }
  // vedi se provarfe un invalid argumet
}
TEST_CASE("test della presa dati IO |inputFile") {
  SUBCASE("mode 1 valid arg") {
    std::string filename{"input_test_1.txt"};
    sir::Epidemic epidemic;
    sir::Automaton automaton;

    int mode{sir::inputFile(filename, epidemic, automaton)};
    CHECK(mode == 1);
    CHECK(epidemic.getT() == 10);
    CHECK(epidemic.getBeta() == doctest::Approx(0.5));
    CHECK(epidemic.getGamma() == doctest::Approx(0.7));

    auto firstState{epidemic.getState()[0]};

    CHECK(firstState.S == 30);
    CHECK(firstState.I == 30);
    CHECK(firstState.R == 60);
  }

  SUBCASE("mode 2 valid arg") {
    std::string filename = "input_test_2.txt";
    sir::Epidemic epidemic;
    sir::Automaton automaton;

    int mode{sir::inputFile(filename, epidemic, automaton)};
    CHECK(mode == 2);
    CHECK(automaton.getT() == 10);
    CHECK(automaton.getN() == 100);
    CHECK(automaton.getSeed() == doctest::Approx(1.0));
    CHECK(automaton.getBeta() == doctest::Approx(0.5));
    CHECK(automaton.getGamma() == doctest::Approx(0.7));

    auto state = automaton.getState();

    CHECK(state.S == 33);
    CHECK(state.I == 23);
    CHECK(state.R == 44);
  }

  SUBCASE("Test inputFile | missing data") {
    std::string filename = "input_test_3.txt";
    sir::Epidemic epidemic;
    sir::Automaton automaton;

    CHECK_THROWS_WITH_AS(sir::inputFile(filename, epidemic, automaton),
                         "numero di dati troppo piccolo",
                         std::invalid_argument);
  }

  SUBCASE("Test inputFile | missing file") {
    std::string filename = "invalidfile.txt";

    sir::Epidemic epidemic;
    sir::Automaton automaton;
    CHECK_THROWS_WITH_AS(
        sir::inputFile(filename, epidemic, automaton),
        "il file non è stato trovato o  non è possibile aprirlo",
        std::runtime_error);
  }

  SUBCASE("Test inputFile | mode undefined") {
    std::string filename = "input_test_4.txt";

    sir::Epidemic epidemic;
    sir::Automaton automaton;
    CHECK_THROWS_WITH_AS(sir::inputFile(filename, epidemic, automaton),
                         "modalità di simulazione sconosciuta",
                         std::runtime_error);
  }
}

// vedi se fare un invalid argument in inout file e vedi se stestare la funzione
// input