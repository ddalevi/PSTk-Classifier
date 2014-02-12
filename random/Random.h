// $Id: Random.h,v 1.1.1.1 2006/01/25 12:46:40 daniel Exp $


#ifndef cpp_tools_random_h
#define cpp_tools_random_h

#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>

static const double MyPI = 4*atan( 1.0 );
/**
   Pseudo random number generator.

   This is an implementation of the pseudo random number generator
   used in the Jetset MC (written in fortran). This implementation is
   adopted from the C++ version written by Patrik Eden,
   Dept. Theoretical Physic, Lund University, Sweden. Real random
   number sequences are hard to create. The algorithm used here is
   described elsewhere (in the Jetset MC, no reference yet), and is
   believed to have a long periodicity.

   This class support a number of differently distributed random
   numbers, saving and restoring its state to/from disk, and some
   manipulations on a rlu_random object's state.

   The random numbers returned from the member functions are always
   real numbers between 0 and 1 unless stated otherwise (is 0 and/or 1
   included?).

   The bit length of the generator can be changed, but its maximum is
   limited to the bit size of the CPU. This probably means that this
   random number generator is not safe for doing securiy software.

   This random number generator can be used in a thread safe way.

   @see RandomSingleton for creation of a single random number
   generator object in a program.

   @see There are a C front end available for this class. The front
   end is described elsewhere.

   @version $Revision: 1.1.1.1 $ $Date: 2006/01/25 12:46:40 $ */

class rlu_random
{
public:
  /**
     Construct a rlu_random object. The first argument is the seed to
     use, and the second argument defines the preferred bit size for
     the random number generator. The bit size cannot exceed the bit
     size supported by the CPU. */
#ifdef __i386__
  // bit size should be read somewhere in the machine
  rlu_random(long sd=19780503,long bitsize_=24);
#else
  rlu_random(long sd=19780503,long bitsize_=48);
#endif

  //Functions added for refactoring code
  bool CheckPrecission();
  void InitVariables();

  /**
     Return the bit size of the object. */
  inline long	bitsize(void)					const;

  /**
     Return the number of calls to the flat() member function (total of
     internal and external calls). */
  inline long	calls(void)					const;

  /**
     Write the state of the object to a file 'rlu_random.dat'. */
  inline void	dump(void)					const;
  
  /**
     Returns an exponentially distributed random number. The numbers
     will be distributed according to the continuous probability
     distribution \f$f(x) = \lambda \exp{-\lambda x}\f$, expectation
     value \f$\mu = \lambda^{-1}\f$, and variance \f$\sigma^2 =
     \lambda^{-2}\f$ */
  inline double exponential(const double lambda=1);

  /**
     Check whether the argument is (randomly) accepted using
     exponentially distributed random numbers.

     \e Note, this functions assume that the arguments are valid, no
     checks are done.

     @see exponential */
  inline bool exponential_accept(const double, const double lambda=1);

  /**
     Return a uniformly distributed random number. The numbers will be
     distributed according to the continuous probability distribution
     \f$f(x)=1/(b-a), \, a \leq x \leq b \f$, expectation value \f$\mu
     = (a+b)/2 \f$, and variance \f$\sigma^2 = (b-a)^2/12\f$. Here
     \f$a=0, \, b=1 \rightarrow \mu=1/2, \, \sigma^2=1/12\f$.

     Are 0 and/or 1 included in the possible return values? */
  double	flat(void);

  /**
     Check whether the argument is (randomly) accepted using uniformly
     distributed random numbers.

     \e Note, this functions assume that the arguments are valid, no
     checks are done.

     @see flat */
  inline bool flat_accept(const double);

  /**
     This is an generalation of the gamma probability distribution for
     integer \a n to non-integer \a n.

     Returns a gamma distributed random number. The numbers will be
     distributed according to the continuous probability distribution
     \f$f(x)=\lambda^n/\Gamma(n) \cdot x^{n-1} \exp{-\lambda x} \f$,
     expectation value \f$\mu=n/\lambda\f$, variance
     \f$\sigma^2=n/\lambda^2\f$. Here \f$\lambda=1\f$.

     Are the statements in above paragraph true?

     @see gamma(const u_int n=1,const double lambda=1) for integer \a
     n. */
  double gamma(const double n);

  /**
     Returns a gamma distributed random number. The numbers will be
     distributed according to the continuous probability distribution
     \f$f(x)=\lambda^n/\Gamma(n) \cdot x^{n-1} \exp{-\lambda x} \f$,
     expectation value \f$\mu=n/\lambda\f$, variance
     \f$\sigma^2=n/\lambda^2\f$.

     @see gamma(const double n) for non-integer \a n */
  double gamma(const size_t n=1,const double lambda=1);

  /**
     Return a random number distributed according to the Gauss
     (general normal) distribution with width \a sigma and expectation
     value \a mu. If \a sigma and \mu are not supplied this is the
     same as a call to normal(). The numbers will be distributed
     according to the continuous probabiliy distribution
     \f$f(x)=\varphi([x-\mu]/\sigma)/\sigma\f$, where \f$\varphi\f$ is
     the normed normal distribution, normal(). Expectation value
     \f$\mu\f$ and variance \f$\sigma^2\f$.

     @see normal */
  inline double gauss1d(const double sigma=1,const double mu=0);

  /**
     Return two random numbers distributed according to a two
     dimensional Gauss distribution. More documentation here please.*/
  void		gauss2d(double& x,double& y,double sigma=1);

  /**
     Return a normal distributed random number. The numbers will be
     distributed according to the continuous probabiliy distribution
     \f$\varphi(x)=1/\sqrt{2\pi} \cdot \exp{-x^2/2}\f$, expectation
     value \f$\mu=0\f$, and variance \f$\sigma^2=1\f$.

     @see gauss1d */
  double normal(void);

  /**
     Reset the object, and re-initialize it using the seed \a sd. If
     no argument is given, or if it is equal to 0, the seed is taken
     from the time of the day (read the source). */
  long randomize(const long sd=0);

  /**
     Restore a rlu_random object state from file 'rlu_random.dat'. */
  inline void restore(void);

  /**
     Reset the object. The object is reset to its initial state if \a
     sd is 0, otherwise it is reset to a state with a seed equal to \a
     sd.  */
  inline void reset(const long sd=0);

  /**
     Returns the objects seed. */
  inline long seed(void) const;

  /**
     Returns a uniformly distributed random unsigned integer between 0
     and \a k - 1 (or \a k, depends on flat(), check this). */
  inline size_t operator() (const size_t k);

  /**
     Writes the state of the object to the stream specified by the
     caller. */
  friend std::ostream& operator<<(std::ostream&,const rlu_random&);

  /**
     Reads the state of the object from the stream specified by the
     caller. */
  friend std::istream& operator>>(std::istream&,rlu_random&);
  //inline double rlu_random::normal(void);


private:
  double	_dmax;
  long		_bitsize, _rmax, _seed, _count, _i1, _i2;
  long		_rr[97], _rr97, _rr98, _rr99;
};


inline long rlu_random::bitsize(void) const
{
  return _bitsize;
}

inline long rlu_random::calls(void) const
{
  return _count;
}
  
inline void rlu_random::dump(void) const
{
  std::ofstream out("rlu_random.dat");
  out << *this;
}

double exponential(const double l);

inline bool rlu_random::exponential_accept(const double x, const double lambda)
{
  return static_cast<bool>(lambda*exp(-x*lambda)>flat());
}

inline bool rlu_random::flat_accept(const double p)
{
  return p>flat();
}

inline double rlu_random::gauss1d(const double sigma,const double mu)
{
  return normal()*sigma+mu;
}


inline void rlu_random::reset(const long sd)
{
  *this=rlu_random(sd ? sd : _seed);
}

inline void rlu_random::restore(void)
{
  std::ifstream in("rlu_random.dat");
  in >> *this;
}

inline long rlu_random::seed(void) const
{
  return _seed;
}

inline size_t rlu_random::operator() (const size_t k)
{
  return static_cast<size_t>(k*flat());
}
#endif
