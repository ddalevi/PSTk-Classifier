#include <vector>
#include <algorithm>
#include <iostream>
#include "RandomDistribution.h"
#include "RandomSingleton.h"

using namespace std;

template<class U, class V>
class myPair
{
public:
  U first;
  V second;
  myPair( U f, V s ) : first( f ), second( s ) {}
  bool operator< (const myPair<U,V>& a ) const 
    { return second < a.second; }
};



RandomDistribution::RandomDistribution( const vector<T>& x_value, const vector<T>& y_frequency )
{
  this->InitRandomSingleton(); //will init random_
  this->CreateCumulativeDistribution( y_frequency );
  this->SetDistribution( x_value );
  this->SetIndexMapping();
}

//*******************************
//The below funcitons are added
//for refactoring code /dd
//*******************************


void RandomDistribution::InitRandomSingleton()
{
  random_ = RandomSingleton::instance();
  random_->randomize();
}

void RandomDistribution::SetIndexMapping()
  //Creates a mapping so that a random number between 0 and 1
  //multiplied with precision yields a number that will be
  //mapped onto the "dist-vector" with weights according to
  //cumdist_
{
  indexmapping_.clear();
  //size_t N = cumdist_.size();
  T steplength =  ( 1.0 - cumdist_[0] ) / static_cast<T>( PRECISION );
  //  cout << steplength << " " << N << " " << cumdist_.size() << "\n";
  size_t counter = 0;
  
  size_t i = 0, j = 0;
  for( /****/ ; i < PRECISION; ++i, ++j )
    {
      while( (i++)*steplength < cumdist_[ j ] ) 
	{ 
	  indexmapping_.push_back( counter );
	  //if( i%10 == 0 ) cout << i << " " << counter << " " << indexmapping_.size()<< " " << cumdist_[ cumdist_.size() -1 ] << endl;
	}
      ++counter;
    }
  
}


void RandomDistribution::CreateCumulativeDistribution( const vector<T> y )
  //Creates the cumulative distribution of y
{
  cumdist_.clear();
  
  vector<T> temp = y;
  this->Normalize( temp );


  T sum = static_cast<T>( 0.0 );

  for( size_t i = 0; i < temp.size(); ++i )
    {
      sum += temp[i];
      cumdist_.push_back( sum );
      //cout << sum << endl;
    }
}


void RandomDistribution::Normalize( vector<T>& y )
{
  T sum = static_cast<T>( 0.0 );
  for( size_t i = 0; i < y.size(); ++i )
    {
      sum += y[i];
    }
  for( size_t i = 0; i < y.size(); ++i )
    {
      y[i] /= sum;
    }
}


void RandomDistribution::SetDistribution( const vector<T> x )
  //Creates the value vector
{
  dist_.clear();
  dist_ = x;
}

//*******************************
//End refactoring code /dd
//*******************************
