// Example program to test PDF grid format reading and interpolation

#include "LHAPDF/GridPDF.h"
#include <iostream>
#include <fstream>
using namespace LHAPDF;
using namespace std;

int main() {

  for (int i = 0; i <= 1; ++i) {
    const GridPDF pdf("EXAMPLEPDF", i);

    cout << "Verbosity = " << pdf.info().metadata("Verbosity") << endl;
    cout << "PdfDesc = " << pdf.info().metadata("PdfDesc") << endl;
    cout << "SetDesc = " << pdf.info().metadata("SetDesc") << endl;
    cout << "Flavors (str) = " << pdf.info().metadata("Flavors") << endl;
    vector<int> pids = pdf.info().metadata< vector<int> >("Flavors");
    cout << "Flavors (ints) = ";
    foreach (int f, pids) cout << f << " "; cout << endl;
    cout << "Flavors (vec<int>) = " << LHAPDF::to_str(pids) << endl;

    cout << "x0, Q0 = " << pdf.subgrid(21, 100).xf(0, 0) << endl;
    cout << "x1, Q0 = " << pdf.subgrid(21, 100).xf(1, 0) << endl;
    cout << "x0, Q1 = " << pdf.subgrid(21, 100).xf(0, 1) << endl;
    cout << "x1, Q1 = " << pdf.subgrid(21, 100).xf(1, 1) << endl;

    cout << pdf.xfxQ(21, 0.7, 10.0) << endl;
    cout << pdf.xfxQ2(21, 0.2, 126) << endl;
    foreach (int pid, pdf.flavors()) {
      cout << pid << " = " << pdf.xfxQ2(pid, 0.2, 124) << endl;
    }

    ofstream f("pdf.dat");
    for (double x = 0; x <= 1; x += 0.02) {
      for (double log10q2 = 1; log10q2 < 3; log10q2 += 0.05) {
        f << x << " " << log10q2 << " " << pdf.xfxQ2(21, x, pow(10, log10q2)) << endl;
      }
    }
    f.close();
    cout << endl;
  }

  return 0;
}