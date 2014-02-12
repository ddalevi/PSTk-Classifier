// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "Node.h"

#include <iostream>
#include <algo.h>
#include <Util.h>


using namespace std;
using namespace trees;

const Alphabet* Node::alphabet = NULL;
int Node::NUMBERNODES = 0;
int Node::DIMENSION = 0;


Node::Node() : 
  s_( "" ), 
  isLeaf_( true ), 
  isAdjusted_( false ),
  tmpData_( 0.0 ), 
  schedualToBeRemove_( false )
{    
  count_ = vector<double>( getAlphabetSize(), 0.0 );
  nextSymbolProb_ = vector<double>( getAlphabetSize(), 0.0 );
  nextSymbolCount_ = vector<double>( getAlphabetSize(), 0.0 );
  ++DIMENSION;
  for( size_t i = 0; i < alphabet->size(); ++i )
    {
      children_.push_back( NULL );
    } 
  ++NUMBERNODES;
}
 
Node::Node( const string& s ) :
  s_( s ),
  isLeaf_( true ),
  isAdjusted_( false ), 
  tmpData_( 0.0 ),
  schedualToBeRemove_( false )
{
  count_ = vector<double>( getAlphabetSize(), 0.0 );
  nextSymbolProb_ = vector<double>( getAlphabetSize(), 0.0 );
  nextSymbolCount_ = vector<double>( getAlphabetSize(), 0.0 );
  ++DIMENSION;
  for( size_t i = 0; i < alphabet->size(); ++i )
    {
      children_.push_back( NULL );
    } 
  ++NUMBERNODES;
}


Node::~Node()
{ 
  --NUMBERNODES;
  bool hadNullPointer = false;
  for( int i = 0; i < children_.size(); ++i )
    {
     if( children_[i] == NULL )  hadNullPointer = true;
    }
  if( hadNullPointer ) --DIMENSION;
}

void Node::setNode( Node* pn, const char& c )
{ 
  bool hadNullPointer = false, hasNullPointer = false;
  for( int i = 0; i < children_.size(); ++i )
    {
      if( children_[i] == NULL ) { hadNullPointer = true; break; }
    }

  
  int idx = alphabet->getIndex( c );
  if( idx == -1 ) 
    {
      cerr << "Letter: " << c << " is not defined!\n";
      return;
    }  
  if( pn != NULL ) 
    { 
      isLeaf_ = false;
    }
  children_[ idx ] = pn;

  for( int i = 0; i < children_.size(); ++i )
    {
      if( children_[i] == NULL ) { hasNullPointer = true; break; }
    }
  
  if( !hadNullPointer && hasNullPointer ) ++DIMENSION;
  if( hadNullPointer && !hasNullPointer ) --DIMENSION;
}


/**
 * \return the count of the next symbol following the string
 * of this node. 
 */
double Node::getTotalC() const
{
  double tot = 0;
  for( int i = 0; i < Node::getAlphabetSize(); ++i )     
    {
      tot += getNextSymbCount( i );
    }
  return tot;
}


/*
 * Assign node corresponding to substring s
 */
void Node::setNode( Node* pn, const int& idx )
{ 
  bool hadNullPointer = false, hasNullPointer = false;
  for( int i = 0; i < children_.size(); ++i )
    {
      if( children_[i] == NULL ) { hadNullPointer = true; break; }
    }

  if( pn != NULL ) 
    { 
      children_[ idx ] = pn;
    }
  else
    {
      children_[ idx ] = pn;
      checkIfLeaf();
    }

  for( int i = 0; i < children_.size(); ++i )
    {
      if( children_[i] == NULL ) { hasNullPointer = true; break; }
    }
  
  if( !hadNullPointer && hasNullPointer ) ++DIMENSION;
  if( hadNullPointer && !hasNullPointer ) --DIMENSION;
}

void Node::checkIfLeaf()
{
  for( size_t i = 0; i < children_.size(); ++i )
    {
      if( children_[i] != NULL ) 
	{
	  isLeaf_ = false;
	  return;
	}
    }
  isLeaf_ = true;
}


/*
 * returns node corresponding to letter c
 */
Node* Node::getNode( const char& c ) const 
{ 
  int idx = alphabet->getIndex( c );

  if( idx == -1 ) 
    {
      cerr << "Letter: " << c << " is not defined!\n";
      return NULL;
    }
  return children_[ idx ];
}


double Node::getC( const char& c, const bool& dummy )
{
  int idx = alphabet->getIndex( c );
	  
  if( idx == -1 ) 
    {
      cerr << "Letter: " << c << " is not defined!\n";
      return 0;
    }
  return getC( idx );
}


bool Node::integrity( const string& s )
{
  for( int i = 0; i < s.size(); ++i )
    {
      if( alphabet->getIndex( s[i] ) == -1 ) return false;
    }
  return true;
}

// double Node::getP( const char& c, const bool& dummy )
// {
//   int idx = alphabet->getIndex( c );
	  
//   if( idx == -1 ) 
//     {
//       cerr << "Letter: " << c << " is not defined!\n";
//       exit( 1 ); 
//     }
//   return getP( idx );
// }

void Node::increaseP( const char& c )
{
  int idx = alphabet->getIndex( c );

  if( idx == -1 ) 
    {
      cerr << "Letter: " << c << " is not defined!\n";
      return; 
    }
  ++count_[ idx ];
}

// /*
//  * adds data_ to string r
//  */
// void Node::addLetter( string& r ) const
// {
//   if( data_ != '\0' )  r += data_;
// }


void Node::print( const bool& isTmpData ) const
{
  if( !isTmpData )
    {
      cout << s_ << " [";
      double tot = getTotalC();
      for( size_t i = 0; i < count_.size(); ++i )
	{
	  if( tot != 0 ) cout << nextSymbolProb_[ i ] << " ";
	  else cout << 0 << " ";
	}
      cout << "] ";
      cout << "ISLEAF = " << isLeaf_ << endl;
    }
  else
    {
      cout << s_ << " " << tmpData_ << " [";
      double tot = getTotalC();
      for( size_t i = 0; i < count_.size(); ++i )
	{
	  if( tot != 0 ) cout << nextSymbolProb_[ i ] << " ";
	  else cout << 0 << " ";
	}
      cout << "] ";
      cout << "ISLEAF = " << isLeaf_ << endl;
    }
}


string Node::myToString( const double& t ) const 
{
  // Create a stream
  std::ostringstream oss; 
  // Insert value to stream
  oss << std::setprecision( 8 ) << t;
  // Return copy of string
  return oss.str();
}


// /*
//  * returns node corresponding to index i
//  */
Node* Node::getNode( const int& i ) const 
{ 
  if( i >= getAlphabetSize() ) 
    {
      cerr << "This aint suppose to happend\n";
      exit( 1 );
    }
  return children_[ i ];
}


string Node::toString() const
{
  string res = "[ ";
  for( int i = 0; i < count_.size(); ++i )
    {
      res += myToString( count_[i] ) + " ";
    }
  res += "] " + myToString( getTotalC() ) + " [ ";
  for( int i = 0; i < nextSymbolCount_.size(); ++i  )
    {
      res += myToString( nextSymbolCount_[i] ) + " ";
    }
//   res += "][ ";
//   for( int i = 0; i < nextSymbolProb_.size(); ++i  )
//     {
//       res += common::ToString( nextSymbolProb_[i] ) + " ";
//     }
  res += "]";
  return res;
}



double Node::getNextSymbProb( const char& c, const bool& dummy  ) const
{
  int idx = alphabet->getIndex( c );
	  
  if( idx == -1 ) 
    {
      cerr << "Letter: " << c << " is not defined!\n";
      return 0;
    }
  return getNextSymbProb( idx );
}


double Node::getNextSymbCount( const char& c, const bool& dummy  ) const
{
  int idx = alphabet->getIndex( c );
	  
  if( idx == -1 ) 
    {
      cerr << "Letter: " << c << " is not defined!\n";
      return 0;
    }
  return getNextSymbCount( idx );
}


void Node::calculateProbabilities()
{
  double tot = 0;
  for( int i = 0; i < nextSymbolCount_.size(); ++i  )
    {
      tot += nextSymbolCount_[i];
    }
  
  for( int i = 0; i < nextSymbolCount_.size(); ++i  )
    {
      if( tot != 0 ) nextSymbolProb_[ i ] = nextSymbolCount_[i] / tot;
      else nextSymbolProb_[ i ] = 0;
    }
}
