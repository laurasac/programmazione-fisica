#ifndef SIR_HPP
#define SIR_HPP
namespace sir {
struct SIR {
  int S;
  int I;
  int R;
  SIR(int s, int i, int r);
};

int update_s(SIR& old_sir, float beta, int N);
int update_i(SIR& old_sir, float beta, float gamma, int N);
int update_r(SIR& old_sir,int new_s, int new_i, float gamma);
bool control_sir(SIR& sir, int N);
void print_sir(SIR& old_sir);
}  // namespace sir

#endif
