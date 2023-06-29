#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "src/doctest.h"
#include "src/sir.hpp"
#include "src/epidemic.hpp"
#include "src/io.hpp"
#include "src/automaton.hpp"
#include <vector>

TEST_CASE("test della struct Sir e delle sue funzioni"){

}

TEST_CASE("test della presa dati"){
    
}

TEST_CASE("test della epidemia"){
    
}

TEST_CASE("test dell'ouput"){
    
}
TEST_CASE("test dell'automa"){
    SUBCASE("test changeStatePerson"){
        sir::Automaton automaton(9,10,0.3, 0.4, 1);
        auto map = automaton.getMap();
        CHECK(automaton.changeStatePerson(4, map) == 's');
        CHECK(automaton.changeStatePerson(2, map) == 'r');
    }
    SUBCASE("test evolve"){
        sir::Automaton automaton(9,10,0.3, 0.4, 1);
        automaton.evolve();
        auto map = automaton.getMap();
        CHECK(map[1] == 'i');
        CHECK(map[3] == 's');
        CHECK(map[4] == 'i');
    }
}