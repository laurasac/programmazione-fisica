#ifndef SIR_HPP
#define SIR_HPP
namespace sir {
struct SIR {
  int S;
  int I;
  int R;
};

int updateS(SIR& oldSir, double beta, int N);
int updateI(SIR& oldSir, double beta, double gamma, int N);
int updateR(int newS, int newI, int N);
bool controlSIR(SIR& sir);
}  // namespace sir
#endif