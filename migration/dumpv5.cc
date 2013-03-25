#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>

#include <LHAPDF/LHAPDF.h>

const double MINLOGX = -8;
const double MINLOGQ = log10(10);
const double MAXLOGQ = log10(5000);
const double DX = 0.1;
const double DQ = 0.1;

int main(int argc, const char* argv[]) {

  if (argc < 3) {
    std::cerr << argv[0] << " <setname> <setmember>" << std::endl;
    return 1;
  }

  const char* setname = argv[1];
  const int member = atoi(argv[2]);
  LHAPDF::initPDFSetByName(setname);
  LHAPDF::initPDF(member);

  // Dump out points in (x,Q)
  int flavors[] = {-5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 21};
  for (int id = -5; id <= 5; ++id) {
    int flavor = flavors[id+5];

    std::stringstream filename;
    filename << "xf_v5_" << flavor << ".dat";
    std::ofstream output( filename.str().c_str() );

    // x sampling for fixed Q
    const double q = 500;
    for (double logX = MINLOGX; logX <= 0.0; logX += DX) {
      double x  = pow(10, logX);
      output << x << " " << q << " " << LHAPDF::xfx(x, q, id) << std::endl;
    }

    // // Q sampling for fixed x
    // const double x = 1e-3;
    // for (double logQ = MINLOGQ; logQ <= MAXLOGQ; logQ += DQ) {
    //   double q = pow(10, logQ);
    //   output << x << " " << q << " " << LHAPDF::xfx(x, q, id) << std::endl;
    // }

    // // (x,Q) 2D sampling
    // for (double logX = MINLOGX; logX <= 0.0; logX += DX) {
    //   for (double logQ = MINLOGQ; logQ <= MAXLOGQ; logQ += DQ) {
    //     const double x  = pow(10, logX);
    //     const double q = pow(10, logQ);
    //     output << x << " " << q << " " << LHAPDF::xfx(x, q, id) << std::endl;
    //   }
    // }

    output.close();
  }

  return 0;
}
