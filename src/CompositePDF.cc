// -*- C++ -*-
//
// This file is part of LHAPDF
// Copyright (C) 2012-2016 The LHAPDF collaboration (see AUTHORS for details)
//
#include "LHAPDF/CompositePDF.h"
#include "LHAPDF/Factories.h"

using namespace std;

namespace LHAPDF {


  typedef pair<string, int> SetNameMem;

  CompositePDF::CompositePDF(const vector<SetNameMem>& setnames_members) {
    for (const SetNameMem& setname_member : setnames_members) {
      PDF* pdf = mkPDF(setname_member.first, setname_member.second);
      addConstituentPDF(pdf);
    }
  }


  CompositePDF::CompositePDF(const vector<int>& lhaids) {
    for (int lhapdfid : lhaids) {
      PDF* pdf = mkPDF(lhapdfid);
      addConstituentPDF(pdf);
    }
  }


}
