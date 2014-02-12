// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "RankCorrelation.h"

#include <cassert>
#include <algorithm>
#include <numeric>  // For use of accumulate
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;


RankCorrelation::RankCorrelation( const vector<double>& v1, const vector<double>& v2 )
{
  assert( v1.size() == v2.size() );
  v1_ = v1;
  v2_ = v2;
  sumt1_ = sumt2_ = 0;
  
  t1_ = t2_ = vector<double>( v1.size(), 0 );
  r1_ = r2_ = vector<double>( v1.size(), 0 );
  setRanksAndTies( v1, r1_, t1_, sumt1_ );
  setRanksAndTies( v2, r2_, t2_, sumt2_ );
  print();
}
  



/*
 * The algorithm for computing the rank-coefficients. 
 * Current implementation is a disgrace to any one
 * aiminig for efficiency ... SHOULD BE FIXED!
 */
void RankCorrelation::setRanksAndTies( const vector<double>& v, vector<double>& r, vector<double>& t, double& sumt )
{
  double last_min_val = -1;
  double rankcounter = 1;
  double MAX = *max_element( v.begin(), v.end() ) + 1.0;

  for( int i = 0; i < (int) v.size(); ++i )
    {
      /*
       * Find the min value that is larger than last_min_val
       */
      double min_val = MAX;
      double n = 0;
      double tienum = 0;
      for( size_t j = 0; j < v.size(); ++j )
	{
	  double val = v[ j ];
	  if( val <= min_val && val > last_min_val ) 
	    {
	      if( val == min_val ) { ++n; ++sumt; }
	      else n = 1;
	      min_val = val;
	    }	
	}
      last_min_val = min_val;

      double assign_rank = rankcounter + ( n - 1 ) / 2;       
      rankcounter += n;

      for( size_t j = 0; j < v.size(); ++j )
	{
	  if( v[ j ] == min_val )
	    {
	      r[ j ] = assign_rank;
	      if( n > 1 ) t[ j ] = assign_rank;
	    }
	}
    }  
}


/*
 * Returns Kendall's tau coefficient
 */
double RankCorrelation::getKendalls( const bool& normappr )
{
  double n = static_cast<double>( r2_.size() );
  double C = getSubsequentRanks();
  double N = 4*C-n*( n - 1 );
  double tau = N / ( sqrt( ( n*( n - 1 ) - sumt1_ )*( n*( n - 1 ) -sumt2_)  ) );
  cout << "sum(t1) = " << sumt1_ << ", sumt(t2) = " << sumt2_ << endl;
  cout << " C = " << C << endl;
  cout << " n = " << n << endl;
  cout << " N = " << N << endl;
  cout << "|tau| = " << abs( tau ) << endl; 
  cout << "|to_normal( tau )| = " << abs( tau / sqrt( 2*(2*n+5)/(9*n*(n-1)) ) ) << endl;  
  if( normappr ) 
    {
      return tau / sqrt( 2*(2*n+5)/(9*n*(n-1)) );
    }
  return tau;
}


double RankCorrelation::getSubsequentRanks()
{
  //print();

  vector<myPair> ranks;
  
  for( size_t i = 0; i < r1_.size(); ++i )
  {
    ranks.push_back( myPair( r1_[i], r2_[i] ) );
  }
  sort( ranks.begin(), ranks.end() );

  double N = 0;
  for( size_t i = 0; i < ranks.size(); ++i ) 
    {
      double rank2 = ranks[ i ].getSecond();
      double C = 0;
      for( size_t j = i; j < ranks.size(); ++j ) 
	{
	  double val = ranks[ j ].getSecond();
	  if( val > rank2 ) ++C;
	  else if( rank2 == val ) 
	    {
	      int myorder = 0;
	      int numties = 0;
	      double identifier = t2_[j];
	      if( identifier != rank2 ) continue;
	      for( size_t k = 0; k < t2_.size(); ++k )
		{
		  if( identifier == t2_[k] )
		    {
		      if( k > i ) ++myorder;
		      ++numties;
		    }
		}
	      double term = ( static_cast<double>( numties - myorder - 1 ) ) / static_cast<double>( numties );
	      C += term;
	    }
	}
      cout << ranks[i].getFirst() << " " << ranks[i].getSecond() << " " << C << endl; 
      N += C;
    }
  return N;
}


void RankCorrelation::print()
{
  for( size_t i = 0; i < v1_.size(); ++i )
    {
      cout << v1_[ i ] << "\t"  
	   << r1_[ i ] << "\t"
	   << t1_[ i ] << "\t"
	   << v2_[ i ] << "\t"
	   << r2_[ i ] << "\t"
	   << t2_[ i ] << endl;
    }
}


void RankCorrelation::test()
{
  vector<double> v1, v2;
  
  v1.push_back( 8.7  ); v2.push_back( 5.95 );
  v1.push_back( 8.5  ); v2.push_back( 5.65 );
  v1.push_back( 9.4  ); v2.push_back( 6.0  );
  v1.push_back( 10.0 ); v2.push_back( 5.7  );
  v1.push_back( 6.3  ); v2.push_back( 4.7  );
  v1.push_back( 7.8  ); v2.push_back( 5.53 );
  v1.push_back( 11.9 ); v2.push_back( 6.4  );
  v1.push_back( 6.5  ); v2.push_back( 4.18 );
  v1.push_back( 6.6  ); v2.push_back( 6.15 );
  v1.push_back( 10.6 ); v2.push_back( 5.93 );
  v1.push_back( 10.2 ); v2.push_back( 5.7  );
  v1.push_back( 7.2  ); v2.push_back( 5.68 );
  v1.push_back( 8.6  ); v2.push_back( 6.13 );
  v1.push_back( 11.1 ); v2.push_back( 6.30 );
  v1.push_back( 11.6 ); v2.push_back( 6.03 );
  
  RankCorrelation rRank( v1, v2 );

  //rRank.print();

  rRank.getKendalls();// << endl;
}
