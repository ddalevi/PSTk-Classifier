// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxMYMATHxxx
#define xxxMYMATHxxx


#include <vector>
using namespace std;

class MyMath
{
public:
  /**
   * N!
   * Fakulteten på svenska
   */
  static int numberOfPermutations( const int& N );

  /**
   * N över k 
   */
  static int numberOfSubsets( const int& N, const int& k );

  /**
   * Binomial distribution
   * \return probability
   */
  static double pBinomial( const double& p, const double& N, const double& k );

  /**
   * Entropy in log2 base
   * \params p vector<double> containing the probabilities
   * \return entropy
   */
  static double entropy( const vector<double>& );

};


#endif
