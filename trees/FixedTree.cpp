// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "Node.h"
#include "FixedTree.h"

using namespace trees;
using namespace std;

#include <cmath>
/*
 * constructors and destructors
 */
FixedTree::FixedTree( const Alphabet* alp, const int& wl )  
  : Tree( alp, wl )
{
}


FixedTree::~FixedTree()
{
}

/*
 * Method for inserting a string representing
 * a sequence
 */
void FixedTree::insert( const string& seq )
{
  modified();
  if( !Node::wordIntegrity( seq ) )
    {
      throw common::Exception( Tree::BADALPHABET, common::Exception::ERROR );
    }
  int l = maxWordLength_ + 1;
  string seq2 = seq;
  reverse( seq2.begin(), seq2.end() );
  for( int counter = 0; counter+1 < seq2.size() ; ++counter )
    {
      string s = "";
      if( counter + l > seq2.size() ) 
	{
	  for( int i = counter; i < seq2.size(); ++i )
	    {
	      s += seq2[i];
	    }
	}
      else
	{
	  s = seq2.substr( counter, l );
	}
	   
      if( Node::integrity( s ) )
	{
	  insertWord( s );
	}
      else continue;
    }
  setProbabilities();
  removeZeroes();
}


// void FixedTree::insert( const string& seq )
// {
//   modified();
//   string seq2 = seq;
//   reverse( seq2.begin(), seq2.end() );
//   for( int counter = 0; counter < seq2.size() ; ++counter )
//     {
//       for( int i = 0; i <= maxWordLength_; ++i )
// 	{
// 	  if( counter + i >= seq2.size() ) break;
// 	  string s = seq2.substr( counter,  i+1 );
// 	  if( Node::integrity( s ) && counter+maxWordLength_ < seq.size() ) 
// 	    {
// 	      insertWord( s );
// 	    }
// 	}
//     }
//   setProbabilities();
//   removeZeroes();
// }

// void FixedTree::insert( const string& seq )
// {
//   modified();
//   string::const_reverse_iterator irev = seq.rbegin();
//   for( int counter = 0; irev != seq.rend(); ++irev, ++counter )
//     {
//       for( int i = 0; i <= maxWordLength_; ++i )
//         {
//           if( ( irev + i ) == seq.rend() ) { break; }
//           string s = "";
//           for( int j = 0; j <= i ; ++j )
//             {
//               s += *(irev + j);
//             }
//           if( Node::integrity( s ) && counter+maxWordLength_ < seq.size() )
//             {
//               insertWord( s );
//             }
//         }
//     }
// }


void FixedTree::print( Node* pNode ) const 
{
  //if( !pNode->isLeaf() && 
  if( pNode->getString().length() == maxWordLength_ 
      && pNode->getString() != "#" )
    {
      pNode->print( true );
    }

  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( pNode->getNode( i ) != NULL )
	{
	  this->print( pNode->getNode( i ) );
	}
    }
}



/*
 * Will return negative log likelihood of sequence 
 * according to Markov model. The longest 
 * prefix will be used for all patterns. Depth of tree will
 * be used for the longest of all patterns 
 */
double FixedTree::getNLL( const string& seq )
{
  int d = depth() + 1;
  double n = 0;

  for( int i = 0; i < seq.size(); ++i ) 
    {
      string pat = seq.substr( i, d );	
      if( pat.size() < d ) continue;
      double p = prob( pat );
      if( p <= 0 ) continue;
      n += -log( p );
    }
  return n;
}



/*
 * This function returns the NLL when adding a minimal probability
 * to counts where no counts exist
 */
double FixedTree::getPseudoNLL( const string& seq, const double& pmin )
{ 
  assert( pmin > 0 );
  int d = depth() + 1;
  double n = 0;

  for( int i = 0; i < seq.size(); ++i ) 
    {
      string pat = seq.substr( i, d );	
      if( pat.size() < d ) continue;
      double p = prob( pat );
      if( p <= 0 ) 
	{
	  p = pmin;
	}
      n += -log( p );
    }
  return n;
}


