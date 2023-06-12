#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "sir.hpp"
#include "epidemic.hpp"
#include "io.hpp"


TEST_CASE("test della struct Sir e delle sue funzioni"){
    SUBCASE("gamma = 0.3 beta = 0.6"){
        float gamma{0.3};
        float beta{0.6};
        sir::SIR state{5,4,2};
        int N{state.S+state.R+state.I};
        sir::SIR new_state{sir::update_s(state, beta, N), sir::update_i(state, beta, gamma,  N), sir::update_r(state, gamma)};
        CHECK( new_state.S == 4);
        CHECK( new_state.I == 4);
        CHECK( new_state.R == 3);
        CHECK(sir::control_sir(new_state, N) == true);
    }
    SUBCASE("gamma = 0.6 beta = 0.3"){
        float gamma{0.6};
        float beta{0.3};
        sir::SIR state{8,32,49};
        int N{state.S+state.R+state.I};
        sir::SIR new_state{sir::update_s(state, beta, N), sir::update_i(state, beta, gamma,  N), sir::update_r(state, gamma)};
        CHECK( new_state.S == 7);
        CHECK( new_state.I == 14);
        CHECK( new_state.R == 68);
        CHECK(sir::control_sir(new_state, N) == true);
    }
    SUBCASE("gamma = 1 beta = 0"){
        float gamma{1.};
        float beta{0.};
        sir::SIR state{8,32,49};
        int N{state.S+state.R+state.I};
        sir::SIR new_state{sir::update_s(state, beta, N), sir::update_i(state, beta, gamma,  N), sir::update_r(state, gamma)};
        CHECK( new_state.S == 8);
        CHECK( new_state.I == 0);
        CHECK( new_state.R == 81);
        CHECK(sir::control_sir(new_state, N) == true);
    }
    SUBCASE("gamma = 0 beta = 1"){
        float gamma{0.};
        float beta{1.};
        sir::SIR state{8,32,49};
        int N{state.S+state.R+state.I};
        sir::SIR new_state{sir::update_s(state, beta, N), sir::update_i(state, beta, gamma,  N), sir::update_r(state, gamma)};
        CHECK( new_state.S == 5);
        CHECK( new_state.I == 35);
        CHECK( new_state.R == 49);
        CHECK(sir::control_sir(new_state, N) == true);
    }
    SUBCASE("s = 0"){
        float gamma{0.3};
        float beta{0.4};
        sir::SIR state{0,32,49};
        int N{state.S+state.R+state.I};
        sir::SIR new_state{sir::update_s(state, beta, N), sir::update_i(state, beta, gamma,  N), sir::update_r(state, gamma)};
        CHECK( new_state.S == 0);
        CHECK( new_state.I == 22);
        CHECK( new_state.R == 59);
        CHECK(sir::control_sir(new_state, N) == true);
    }
    SUBCASE("i = 0"){
        float gamma{0.3};
        float beta{0.4};
        sir::SIR state{8,0,49};
        int N{state.S+state.R+state.I};
        sir::SIR new_state{sir::update_s(state, beta, N), sir::update_i(state, beta, gamma,  N), sir::update_r(state, gamma)};
        CHECK( new_state.S == 8);
        CHECK( new_state.I == 0);
        CHECK( new_state.R == 49);
        CHECK(sir::control_sir(new_state, N) == true);
    }
    SUBCASE("i = 0 s = 0"){
        float gamma{0.3};
        float beta{0.4};
        sir::SIR state{0,0,49};
        int N{state.S+state.R+state.I};
        sir::SIR new_state{sir::update_s(state, beta, N), sir::update_i(state, beta, gamma,  N), sir::update_r(state, gamma)};
        CHECK( new_state.S == 0);
        CHECK( new_state.I == 0);
        CHECK( new_state.R == 49);
        CHECK(sir::control_sir(new_state, N) == true);
    }
}

TEST_CASE("test della presa dati"){
    
}

TEST_CASE("test della epidemia"){
    
}

TEST_CASE("test dell'ouput"){
    
}
