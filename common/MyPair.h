// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxMYPAIRxxx
#define xxxMYPAIRxxx


/**
 * Template class for holding pairs of data
 */
template<class T, class S>
class MyPair
{
public:
  MyPair( T a, S b ) : a_( a ), b_( b ) {}
  bool operator< ( const MyPair<T,S>& o ) const { return o.b_ > b_; } 
  T getA() const { return a_; }
  S getB() const { return b_; }

private:
  T a_;
  S b_;
};


#endif
