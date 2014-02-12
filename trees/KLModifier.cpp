// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include <cmath>
#include <StatisticalTables.h>

#include "KLModifier.h"
#include "Node.h"
#include "Tree.h"
#include "TreeModifier.h"

using namespace trees;


KLModifier::KLModifier( Tree* tree ) : TreeModifier( tree )
{
}


KLModifier::KLModifier( Node* pHead, Tree* tree ) : TreeModifier( pHead, tree )
{
}


KLModifier::~KLModifier()
{
}


void KLModifier::prune( const double& cutoff )
{
  double K = cutoff;
  if( head_ == NULL )
    {
      cerr << "Pruning empty tree?\n";
      return;
    }
  if( K < 0 )
    {
      K = 0.5*StatisticalTables::quantileChiSquare( head_->getAlphabetSize() - 1, 0.05 );
      cerr << "No cutoff set: K = " << K << " is recommended!\n";
      cerr << "Re-run but specify cutoff with \"-nc " << K << "\n";
      exit( 1 ); // Occassionally generates segmentation-fault if re-define cutoff (DD 2005-11-01)
    }

  bool hasRemoved = false;
  for( size_t i = 0; i < tree_->getMaxWordLength(); ++i )
    {
      prune( head_, K, hasRemoved );
    }
}


void KLModifier::prune( const int& num )
{
  if( head_ == NULL )
    {
      cerr << "Pruning empty tree?\n";
      return;
    }
  
  vector<double> deltas;
  getAllDeltas( head_, deltas );
  if( deltas.size() < num ) return;
  sort( deltas.begin(), deltas.end() );
  reverse( deltas.begin(), deltas.end() );
  //  for( size_t i = 0; i < deltas.size(); ++i ) cout << deltas[i] << endl;
  double delta = deltas[ num ];

  int count = 0;
  while( head_->getNumberParameters() > num )
    {
      bool hasRemoved = false;
      if( !prune( head_, delta , hasRemoved, num ) ) break;
      if( !hasRemoved ) 
	{
	  ++delta;
	  ++count;
	  if( count > TreeModifier::MAXITERATION ) 
	    {
	      cerr << "In KLModifier: Prune did not converge for " << num << " parameters!\n";
	      break;
	    }
	}
    }
}



void KLModifier::prune( Node* pNode, const double& cutoff, bool& hasRemoved )
{
  for( int i = 0; i < pNode->getAlphabetSize(); ++i )
    {
      Node* next = pNode->getNode( i );
      if( next == NULL ) continue;
      if( next->isLeaf() )
	{
	  double delta = getDelta( pNode, next );
// 	  cout << pNode->getString() << " " << next->getString() 
// 	       << " delta = " << delta << endl;
	  
// 	  cout << pNode->getString() << " " << tree_->getCount( pNode->getString() ) << " "
// 	       << next->getString() << " " << tree_->getCount( next->getString() ) << " "
// 	       << delta << " " << cutoff << endl;
	  if( delta <= cutoff )
	    {
	      delete next;
	      next = NULL;
	      pNode->setNode( NULL, i );
	      hasRemoved = true;
	    }
	  else
	    {
	      //	      cout << "DO NOT DELETE NODE: " << next->getString() << " " << delta << endl;
	    }
	}
      else
	{
	  prune( next, cutoff, hasRemoved );
	}
    }

}


bool KLModifier::prune( Node* pNode, const double& cutoff, bool& hasRemoved, const int& num )
{

  for( int i = 0; i < pNode->getAlphabetSize(); ++i )
    {
      if( head_->getNumberParameters() <= num ) return true;
      Node* next = pNode->getNode( i );
      if( next == NULL ) continue;
      if( next->isLeaf() )
	{
	  double delta = getDelta( pNode, next );
// 	  cout << pNode->getString() << " " << next->getString() 
// 	       << " delta = " << delta << endl;
	  
//	  cout << delta << endl;
	  if( delta <= cutoff )
	    {
	      if( Node::getNumberNodes() <= 5 ) return false; // Avoid choosing a worse model with same number parameters
	      delete next;
	      next = NULL;
	      pNode->setNode( NULL, i );
	      hasRemoved = true;
	    }
	  else
	    {
	      //	      cout << "DO NOT DELETE NODE: " << next->getString() << " " << delta << endl;
	    }
	}
      else
	{
	  prune( next, cutoff, hasRemoved , num );
	}
    }
  return true;
}



void KLModifier::getAllDeltas( Node* pNode, vector<double>& deltas  )
{
  for( int i = 0; i < pNode->getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i );
      if( node == NULL ) continue;
      deltas.push_back( getDelta( pNode, node ) );
      getAllDeltas( node, deltas );
    }
}

double KLModifier::getDelta( Node* pNode, Node* next )
{
  double res = 0;
  
  for( int i = 0; i < pNode->getAlphabetSize(); ++i )
    {
      double p_w = pNode->getNextSymbProb( i );
      double p_wu = next->getNextSymbProb( i );
      string wu = next->getString();
      if( p_wu == 0 || p_w == 0 ) continue;
      res += p_wu*log( p_wu / p_w ) * next->getTotalC();
    }
  next->setTmpData( res );
  return res;
}
