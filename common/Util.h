// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

// Utility functions
#ifndef xxxUTILxxx
#define xxxUTILxxx


#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>

using namespace std;

class Util 
{
public:
  static string ToString( const int& t, bool in_hex = false );
  static string ToString( const double& t, bool in_hex = false );

  static double safe_exp(const double x)
  {
    return ( x < -50 ? 0 : exp(x) );
  }

  static double safe_log(const double x)
  {
    return log( x < 1e-10 ? 1e-10 : x );
  }

  
  //  std::string TimeAndDate2String();

  /*
   * return reverse complement of DNA string
   **/
  static std::string reverseComplement( const std::string& s );

  static std::string TimeAndDate2String();

};

#endif
