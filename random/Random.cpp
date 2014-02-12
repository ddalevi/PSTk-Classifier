
#include "Random.h"

#include <cmath>
#include <Util.h>

using namespace std;

static const double MPI = 4.0*atan( 1.0 );


rlu_random::rlu_random( long sd, long bitsize_ )
{
  _seed = sd;
  _bitsize = bitsize_;

  if( !this->CheckPrecission() ) 
    {
      *this = rlu_random( sd, _bitsize-8 );
      return;
    }
  
  this->InitVariables();
}



//*******************************
//The below funcitons are added
//for refactoring code /dd
//*******************************
bool rlu_random::CheckPrecission()
{
  long i;
  for ( _rmax = 1, i = 0; i < _bitsize; i++ )
    _rmax *= 2;
  _dmax = static_cast<double>( _rmax );
  if ( ( ( _rmax - 1 ) / _dmax >= 1 ) || ( ( _rmax - 1 ) / _dmax <=0 ) ) 
    { 
      if( _bitsize <= 24) 
	{
	  cerr << "# Machine precision too low for rlu_random number generator.\n"
	       << "# Program stopped" << endl;
	  exit( 1 );
	}      
      return false;
    }
  return true;
}


void rlu_random::InitVariables()
{
  int C1 = 30082;
  int C2 = 31329;
  int C3 = 177;
  int C4 = 178;
  int C5 = 179;
  int C6 = 169;

  long j = _seed / C1  % C2;
  long l = _seed%C1;
  long i = j / C3%C3 + 2;
  j = j%C3 + 2;
  long k = l / C6%C4 + 1;
  l = l%C6;
  long s, t;

  for( _i1 = 0 ; _i1 < 97 ; _i1++ ) 
    {
      s = 0;
      t = _rmax;
      for( _i2 = 0; _i2 < _bitsize; _i2++ ) 
	{
	  t /= 2;
	  long m = ( ( (i*j)%C5 )*k )%C5;
	  i = j; 
	  j = k; 
	  k = m;
	  l = ( 53*l+1 )%C6;
	  if( ( l*m )%64 >= 32 ) s += t;
	}
      _rr[_i1] = s;
    }

  _rr97 = 362436;
  _rr98 = 7654321;
  _rr99 = 16777213;
  for( i = 24; i < _bitsize; i++ ) 
    {
      _rr97 *= 2; 
      _rr98 *= 2; 
      _rr99 *= 2;
    }

  _count = 0;
  _i1 = 96; 
  _i2 = 32;

}


//*******************************
//End refactoring code /dd
//*******************************


double rlu_random::exponential(const double l)
{
  return -Util::safe_log(flat())/l;
}

double rlu_random::normal(void)
{
  return sqrt(-2*Util::safe_log(flat()))*cos(MyPI*flat());
}

double rlu_random::flat(void)
{
  long r = 0;

  do {
    if( ( r = _rr[_i1] - _rr[_i2] ) < 0 ) r += _rmax;
    _rr[_i1] = r;
    _i1 = (_i1 ? _i1-1 : 96);
    _i2 = (_i2 ? _i2-1 : 96);
    if( ( _rr97 -= _rr98 ) < 0 ) _rr97 += _rr99;
    if( (r -= _rr97 ) < 0 ) r+=_rmax;
  } while( !r );
  
  _count++;                        //BEWARE OF OVERFLOW!!

  return static_cast<double>( r ) / _dmax;
}



double rlu_random::gamma( const size_t n, const double lambda )
{
  double r = flat();
  for ( size_t i = 1; i < n; i++ )
    r *= flat();
  return -Util::safe_log(r) / lambda;
}



double rlu_random::gamma(double a)
{
  if( a < 1e-10 ) return exponential();
  size_t k = static_cast<size_t>( a+1. );
  double r, g;
  do {
    r = gamma( k );
    g = r + a - k;
  } while ( ( g < 1e-10) || 
	    ( flat() > exp( a*log(g/a)-k*log(r/k) ) ) );
  return g;
}



void rlu_random::gauss2d(double& x,double& y,double sigma)
{
  double r = sqrt(-2*Util::safe_log(flat()))*sigma;
  double v = 2*MPI*flat();
  x = r*sin(v);
  y = r*cos(v);
}



long rlu_random::randomize(const long sd)
{ 
  //This is a new way of getting the number of 
  //seconds passed today which is compatible 
  //with VC++ /Daniel
 
  _seed = sd;
  if( !_seed )
    {
      time_t rawtime;
      struct tm * timeinfo;
      time ( &rawtime );
      timeinfo = localtime ( &rawtime );
      long sec = timeinfo->tm_sec;
      long min = timeinfo->tm_min;
      long hour = timeinfo->tm_hour;
      _seed = sec + 60*min + 60*60*hour;
    }

  reset( _seed );
  return _seed;

	//OLD WAY
//	struct timeval tp;
//  _seed=sd;
//  if (!_seed) {
//    gettimeofday(&tp,0);
//    _seed=tp.tv_sec;
//  }
//  reset(_seed);

//  return _seed; 
}



// ostream& rlu_random::operator<<(ostream& out,const rlu_random& r)
// {
//   out << "# Status of rlu_random object. Order:\n"
//       << "# bitsize, seed, count, i1, i2, rr97, rr98, rr99, rr[0-96]\n"
//       << r.bitsize() << '\n' << r.seed() << '\n' << r.calls() << '\n'
//       << r._i1 << '\n' << r._i2 << '\n' << r._rr97 << '\n' << r._rr98 << '\n'
//       << r._rr99 << "\n\n";
//   for (size_t i=0; i<97; i++)
//     out << r._rr[i] << '\n';

//   return out;
// }



// istream& rlu_random::operator>>(istream& in,rlu_random& r)
// {
//   char dump[100],c;
//   long i;
//   do
//     in.get(c);
//   while (c=='\n');
//   in.get(dump,100,'\n'); 
//   if (strcmp(" Status of rlu_random object. Order:",dump)) {
//     cout << "Initiation from file failed. rlu_random object unchanged." << endl;
//     return in;
//   }
//   in.get(c);
//   in.get(dump,100,'\n'); 
//   if(strcmp("# bitsize, seed, count, i1, i2, rr97, rr98, rr99, rr[0-96]",dump)){
//     cout << "Initiation from file failed. rlu_random object unchanged." << endl;
//     return in;
//   }
//   in >> r._bitsize >> r._seed >> r._count >> r._i1 >> r._i2 >> r._rr97
//      >> r._rr98 >> r._rr99;
//   for (i=0; i<97; i++)
//     in >> r._rr[i];
//   for (r._rmax=1,i=0; i<r._bitsize; i++)
//     r._rmax*=2;
//   r._dmax=static_cast<double>(r._rmax);
//   return in;
// }


