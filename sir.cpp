#include "sir.hpp"
#include <iostream>

update_s(SIR old_sir, float beta, int N){
   int new_s=old_sir.S-(beta*old_sir.S*old_sir.I/N);
   old_sir.S==new_s;
   return old_sir.S;
};
update_i(SIR old_sir, float beta, float gamma, int N){
    int new_i.I=old_sir.I+(beta*old_sir.I*old_sir.I/N)-(gamma*old_sir.I);
    old_sir.I==new_i;
    return old_sir.I;
};
update_r(SIR old_sir, float gamma, int N){
   int new_r=old_sir.R+(gamma*old_sir.I);
   old_sir.R==new_r;
   return old_sir.R;
}
control_sir(SIR old_sir, int N){
    if (!(old_sir.S + old_sir.I + old_sir.R == N)){
    throw std::invalid_argument("C'è stato un errore nella simulazione");
  }
}
print_sir(){
    std::cout<<"Il numero di S (individui suscettibili) è: "<<old_sir.S<<'\n';
    std::cout<<"Il numero di I (individui suscettibili) è: "<<old_sir.I<<'\n';
    std::cout<<"Il numero di R (individui suscettibili) è: "<<old_sir.R<<'\n';
    return 0;
}
