// direi di definire una struct che contiene i dati per ogni giorno, e poi
// implementare separatamente le funzioni
namespace sir {
struct SIR {
  int S;
  int I;
  int R;
};

// vediamo se passare l'intera struct o solo i valori che ci servono, e poi se
// passarla come reference, valore ecc

int update_s(SIR old_sir, float beta, int N);
int update_i(SIR old_sir, float beta, float gamma, int N);
int update_r(SIR old_sir, float gamma, int N);
int control_sir(SIR old_sir, float gamma, int N); // potremmo anche fare tutte queste cose in unica funzione in realtà
void print_sir(); // per stampare i dati
}  // namespace sir


