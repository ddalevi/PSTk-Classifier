// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxSEQUENCEGENERATORxxx
#define xxxSEQUENCEGENERATORxxx

 
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <new>
#include <memory>
#include <cassert>
#include <RandomSingleton.h>
#include "Alphabet.h"


/*
 * Class implementing a DNA sequence generator
 * under markov conditions
 */

class SequenceGenerator {

public:
  SequenceGenerator( const Alphabet*, const int& seed = 0 );

  static void setAlphabet( const Alphabet* a )
  {
    alphabet = a;
  } 

  void setRandomTransitions( const bool& = false );
  void setTransitions( const vector<double>& );
  string getSequence( const int&, const double& );
  string getMixture( const int&, const int& , 
		     const double& ,const double& );
  string completelyRandom( const int& );
  void printFasta( const int& );
  void setBase( const int& v ) { base_ = v; }
  void setGC( const double& v ) { gc_ = v; }
  double getGC() const { return gc_; }
  void setSubsetTransition( const int& );
  void setGCnormal( const double& mean, const double& std );
  void setEmpty( map<string, double>& , const int&, const vector<double>&, string, int&  );
  static void test();

private:
  static const Alphabet* alphabet; 
  auto_ptr<RandomSingleton> prand_;
  map<string, double> trans_;
  map<string, double> strans_;
  int base_;
  int sbase_;
  double gc_;
};

#endif
