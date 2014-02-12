#ifndef cpp_tools_randomdistribution_h
#define cpp_tools_randomdistribution_h
#include <assert.h>

#include <vector>
#include "RandomSingleton.h"

using namespace std;


typedef double T;

class RandomDistribution
{
public:
  
  RandomDistribution( const vector<T>&, const vector<T>& );
  inline T value(void) const;
  inline T value(T) const;

  static const size_t PRECISION = 10000000;

  long Rndmize(const long sd=0)
  {
    long seed = random_->randomize( sd );
    return seed;
  }
  

private:
  void InitRandomSingleton();
  void CreateCumulativeDistribution( const vector<T> );
  void Normalize( vector<T>& );
  void SetDistribution( const vector<T> );
  void SetIndexMapping();

  RandomSingleton* random_;
  vector<T> cumdist_;
  vector<T> dist_;
  vector<size_t> indexmapping_;
};


  inline T RandomDistribution::value( void ) const
  {
    return value( random_->flat() );
  }

  inline T RandomDistribution::value( T d ) const
  {
    assert( indexmapping_.size() > 1 );
    d = d*PRECISION;
    //  cout << static_cast<size_t>( d ) << endl;
    size_t idx1 = static_cast<size_t>( d );
    if( idx1 < indexmapping_.size() )
      {
	size_t idx2 = indexmapping_[ idx1 ];
	return dist_[ idx2 ];
      }
    else
      {
	return value( random_->flat() );
      }
  }


#endif
