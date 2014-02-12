// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "MyMath.h"
#include <cmath>
#include <iostream>
using namespace std;

int MyMath::numberOfSubsets( const int& N, const int& k )
{
  int res = 0;
  res = numberOfPermutations( N ) / ( numberOfPermutations( k )*numberOfPermutations( N - k ) );
  return res;
}


int MyMath::numberOfPermutations( const int& N )
{
  int res = 1;
  for( int i = 1; i <= N; ++i )
    {
      res *= i;
    }
  return res;
}


double MyMath::pBinomial( const double& p, const double& N, const double& k )
{
  double f = pow( 1.0 - p, N );
  for( double x = 1; x <= k; ++x )
    {
      f = f * ( p / ( 1 - p ) * ( N - x + 1 ) / x );
    }
  return f;
}


// Defined using log2(x)
double MyMath::entropy( const vector<double>& p )
{
  double res = 0;
  for( int i = 0; i < p.size(); ++i )
    {
      if( p[i] == 0 ) continue;
      res += -p[i]*log( p[i] ) / log( 2.0 );
    }
  return res;
}
 
