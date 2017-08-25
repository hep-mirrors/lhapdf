// -*- C++ -*-
//
// This file is part of LHAPDF
// Copyright (C) 2012-2016 The LHAPDF collaboration (see AUTHORS for details)
//
#include "LHAPDF/Info.h"
#include "LHAPDF/PDFIndex.h"

#include "yaml-cpp/yaml.h"
#ifdef YAML_NAMESPACE
#define YAML YAML_NAMESPACE
#endif

namespace LHAPDF {


  void Info::load(const string& filepath) {
    // Complain if the path is empty
    if (filepath.empty()) throw ReadError("Empty PDF file name given to Info::load");

    // But complain if a non-empty path is provided, but it's invalid
    if (!file_exists(filepath)) throw ReadError("PDF data file '" + filepath + "' not found");

    // Read the YAML part of the file into the metadata map
    try {
      // Do the parsing "manually" up to the first doc delimiter
      std::ifstream file(filepath.c_str());

      #if YAMLCPP_API == 3

      YAML::Node doc;
      YAML::Parser parser(file);
      parser.GetNextDocument(doc);
      for (YAML::Iterator it = doc.begin(); it != doc.end(); ++it) {
        string key, val;
        it.first() >> key;
        YAML::Emitter em;
        em << it.second();
        val = em.c_str();
        _metadict[key] = val;
      }

      #elif YAMLCPP_API == 5

      string docstr, line;
      while (getline(file, line)) {
        if (line == "---") break;
        docstr += line + "\n";
      }
      YAML::Node doc = YAML::Load(docstr);
      for (YAML::const_iterator it = doc.begin(); it != doc.end(); ++it) {
        const string key = it->first.as<string>();
        YAML::Emitter em;
        em << it->second();
        const string val = em.c_str();
        _metadict[key] = val;
      }

      #endif
    } catch (const YAML::ParserException& ex) {
      throw ReadError("YAML parse error in " + filepath + " :" + ex.what());
    } catch (const LHAPDF::Exception& ex) {
      throw;
    } catch (const std::exception& ex) {
      throw ReadError("Trouble when reading " + filepath + " :" + ex.what());
    }

  }



  // /// @todo Only support loading via PDF set name and member ID, not explicit paths
  // /// @todo Replace the loading of the set metadata into the member info with set-level Info singletons
  // void Info::loadFull(const string& mempath) { //< @todo Need a better method name!
  //   // Extract the set name from the member data file path
  //   const string memberdata = findFile(mempath);
  //   if (memberdata.empty() || !file_exists(memberdata)) throw ReadError("Could not find PDF data file '" + mempath + "'");
  //   const string memname = basename(memberdata); //< Can use this to alternatively work out the set name...
  //   const string setdir = dirname(memberdata);
  //   const string setname = basename(setdir);
  //   path setinfo = findpdfsetinfopath(setname);
  //   // Load the set info
  //   if (file_exists(setinfo)) load(setinfo);
  //   // Load the member info (possibly overriding the set-level metadata)
  //   load(memberdata);
  // }


}
