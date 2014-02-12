// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

// Utility functions
#ifndef xxxSTATTABLExxx
#define xxxSTATTABLExxx


#include <vector>
#include <iostream>

using namespace std;

class StatisticalTables
{
public:
  /**
   * Function that returns the sig%-quantile of a Chi-square distribution  
   * \param r This is the number of degrees of freedom
   * \param sig The percentage of mass of the "right"-tail of the distribution
   * \return Chi( r, sig )
   */
  static double quantileChiSquare( const int& r, const double& sig );
};

#endif
