// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "Node.h"
#include "Tree.h"
#include "PstTree.h"

using namespace std;
using namespace trees;


/*
 * constructors and destructors
 */
PstTree::PstTree( const Alphabet* alp, const int& wl )  
  : Tree( alp, wl )
{
}


PstTree::~PstTree()
{
}


void PstTree::insert( const string& seq )
{
  modified();
  if( !Node::wordIntegrity( seq ) )
    {
      throw common::Exception( Tree::BADALPHABET, common::Exception::ERROR );
    }
  string seq2 = seq;
  //  cout << seq << endl;
  reverse( seq2.begin(), seq2.end() );
  for( int counter = 0; counter+1 < seq2.size(); ++counter ) 
    {
      string s = "";
      if( counter + maxWordLength_ > seq2.size() ) 
	{
	  for( int i = counter; i < seq2.size(); ++i )
	    {
	      s += seq2[i];
	    }
	}
      else
	{
	  s = seq2.substr( counter, maxWordLength_ );
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

// void PstTree::insert( const string& seq )
// {
//   modified();
//   string seq2 = seq;
//   //  cout << seq << endl;
//   reverse( seq2.begin(), seq2.end() );
//   for( int counter = 0; counter+1 < seq2.size(); ++counter ) 
//     {
//       for( int i = 0; i < maxWordLength_; ++i )
//       	{
//       	  if( counter + i >= seq2.size() ) break;
// 	  string s = seq2.substr( counter, i+1 );
// 	  //  cout << "Inserting: " << s << endl;
	  
// 	  if( Node::integrity( s ) )
// 	    {
// 	      insertWord( s );
// 	    }
// 	  else continue;
// 	}
//     }
//   setProbabilities();
// }


void PstTree::constrainTree( const int& min )
{
  DEPTH = -1; // Tree modified
  constrainTree( head_, min );  
}



void PstTree::constrainTree( Node* pNode, const int& min )
{
  for( int i = 0; i < pNode->getAlphabetSize(); ++i )
    {
      Node* curNode = pNode->getNode( i );
      if( curNode == NULL ) 
	{
	  continue;
	}
      else { /* NADA */ }
      if( pNode->getC( i ) < min )
	{
	  cleanUp( curNode );
	  pNode->setNode( NULL, i );
	}
      else
	{
	  constrainTree( curNode, min );
	}
    }  
}


double PstTree::getNLL( const string& seq )
{
  int d = depth() + 1;
  double n = 0;

  for( int i = 0; i < seq.size(); ++i ) 
    {
      string pat = "";
      if( i - d >= 0 ) 
	{
	  pat = seq.substr( i - d + 1, d );
	}
      else
	{
	  pat = seq.substr( 0, i + 1);
	}

      double p = prob( pat );
     
      if( !( p > 0 && p <= 1 ) ) continue;
      n += -log( p );
    }
  return n;
}




double PstTree::getPseudoNLL( const string& seq, const double& pmin )
{
  // The meaning of this function in a variable context must be
  // considered ....
  PstTree::getNLL( seq );
}
