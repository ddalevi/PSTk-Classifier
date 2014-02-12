// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxALPHABETxxx
#define xxxALPHABETxxx



#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

/**
 * This class stores all information needed for repressenting an alphabet of characters,
 * \author Daniel Dalevi
 * \date 2005-05-30
 */
class Alphabet 
{
public:

  /**
   * The following alphabets are defined
   */
  enum ALPHABET {
    BINARY,   /**< { 0, 1 } */
    DNA,      /**< { A, C, G, T } */
    N_DNA,    /**< { A, C, G, T, N } */
    PROTEIN   /**< { A, B, C, D, E, F, G, H, I, K, L, M, N, P, Q, R, S, T, V, W, X, Y, Z } */
  };

  static const int MAX_CHECK = 50;

  Alphabet() 
  {
    l_ = "";
    name_ = "none";
    for( int i = 0; i < 1000; ++i )
      {
	myMap_.push_back( -1 );
      }
  }


  /**
   * checks wheter c belongs to alphabet
   * if true returns position in alphabet
   * else returns -1
   */
  int getIndex( const char& c ) const
  {
    return myMap_[ c ];
  }
  


  /**
   * Returns the corresponding letter of index i in 
   * the alphabet
   */
  char getChar( const int& i ) const
  {
    assert( i < l_.size() );
    return l_[i];
  }
  

  void setAlphabet( ALPHABET a )
  {
    switch( a )
      {
      case BINARY:
	{
	  name_ = "binary";
	  l_ = "01";
	  myMap_[ '0' ] = 0;
	  myMap_[ '1' ] = 1;	  
	  break;
	}
      case N_DNA:
	{
	  name_ =  "N_DNA";
	  l_ = "ACGTN";
	  string ll = "acgtn";
	  for( int i = 0; i < l_.size(); ++i )
	    {
	      myMap_[ l_[ i ] ] = i;
	    }
	  for( int i = 0; i < ll.size(); ++i )
	    {
	      myMap_[ ll[ i ] ] = i;
	    }
	  break;
	}
      case DNA:
	{
	  name_ =  "DNA";
	  l_ = "ACGT";
	  string ll = "acgt";
	  for( int i = 0; i < l_.size(); ++i )
	    {
	      myMap_[ l_[ i ] ] = i;
	    }
	  for( int i = 0; i < ll.size(); ++i )
	    {
	      myMap_[ ll[ i ] ] = i;
	    }
	  break;
	}
      case PROTEIN:
	{
	  name_ = "PROTEIN";
	  l_ = "ABCDEFGHIKLMNPQRSTVWXYZ.";  
	  for( int i = 0; i < l_.size(); ++i )
	    {
	      myMap_[ l_[ i ] ] = i;
	    }

	  /* Here X = unknown
	   * B = Aspartic acid or asparagine, 
	   * Z = Glutamic acid or glutamine, 
	   * "." = terminator 
	   */
	  break;
	}
      default:
	{
	  cerr << "No such alphabet!";
	  exit( 1 );
	}

      }
  } 

  bool testWord( const string& s ) const
  {
    bool integrity = true;
    for( int i = 0; i < s.size(); ++i )
      {
	if( getIndex( s[i] ) == -1 ) integrity = false;
	if( i > Alphabet::MAX_CHECK ) break;
      }
    return integrity;
  }

  string getName() const { return name_; }
  void setAlphabet( const string& name )
  {
    if( name == "BINARY" ) setAlphabet( BINARY );
    if( name == "DNA" ) setAlphabet( DNA );
    if( name == "PROTEIN" ) setAlphabet( PROTEIN );
  }

  size_t size() const { return l_.size(); }
  
  string toString() const { return l_; }
  

private:
  string l_;
  vector<int> myMap_;
  string name_;
};

#endif
