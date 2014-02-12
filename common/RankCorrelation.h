// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxRANKCORRELATIONxxx
#define xxxRANKCORRELATIONxxx


/*
 * Purpose: To calculate Kendall's and other measures of 
 *          Rank correlation. Vector v1_ and v2_ holds the 
 *          values and r1_ and r2_ the different ranks. v1 and v2
 *          should be sorted so that index i in v1 and v2 corresponds 
 *          to same measurement.
 */

#include <vector>

/*
 * Auxiliary class
 */
class myPair {
public:
  myPair( const double& a, const double& b ) : a_( a ), b_( b ) {}
  double getFirst() const { return a_; } 
  double getSecond() const { return b_; } 
  
  friend bool operator< ( const myPair& a, const myPair& b )
  {
    return a.getFirst() < b.getFirst();
  }
  

private:
  double a_, b_;   
};

using namespace std;

class RankCorrelation {

public:
  /*
   * The public interface
   */
  RankCorrelation( const vector<double>&, const vector<double>& );  
  double getKendalls( const bool& = false );

  static void test();
  void print();

private:
  /*
   * Private functions
   */
  void setRanksAndTies( const vector<double>&, vector<double>&, vector<double>&, double& );
  double getSubsequentRanks();
  

  /*
   * private attributes
   */
  vector<double> v1_, v2_; // Values
  vector<double> r1_, r2_; // Ranks
  vector<double> t1_, t2_;    // Ties
  double sumt1_, sumt2_;
};

#endif
