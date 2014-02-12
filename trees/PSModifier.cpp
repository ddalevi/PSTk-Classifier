// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include <cmath>

#include "TreeModifier.h"
#include "PSModifier.h"
#include "Tree.h"
#include "Node.h"
#include <algorithm>
#include <MyPair.h>

using namespace trees;


PSModifier::PSModifier( Tree* tree ) : TreeModifier( tree )
{
  //  cout << "Head Node from start: " << head_->getString() << endl;
}


PSModifier::PSModifier( Node* pHead, Tree* tree ) : TreeModifier( pHead, tree )
{
}


PSModifier::~PSModifier()
{

}


int PSModifier::getOrder() 
{
  setDeltas();
  vector<double> deltas = getMaxDelta();
  vector<double> der;
  int res = -1;
  double prev = 1;
  for( int i = 0; i < deltas.size(); ++i )
    {
      if( deltas[i] > 0 ) der.push_back( prev / deltas[i] );
      else                der.push_back( 0 );
      prev = deltas[i];
    }
   
  double der_max = *max_element( der.begin(), der.end() );
  for( int i = 0; i < deltas.size(); ++i )
    {
      cout << i+1 << " " << deltas[i] << " " << der[i] << endl;
      if( der[i] == der_max ) res = i+1;//cout << "*";
      //cout << endl;
    }
   return res;
}


vector<double> PSModifier::getMaxDelta() 
{
  vector<double> max_vec;
  double max;
  for( int i = 1; i+1 < tree_->getMaxWordLength(); ++i )
    {
      double max = 0;
      getMaxDelta( head_, head_, 1, i, max );
      //cout << i << " " << max << " " << prev/max << endl;
      max_vec.push_back( max );
    }
  return max_vec;
}


// mNode is the base node to whom all deltas should be calculated.
void PSModifier::getMaxDelta( Node* cNode, Node* pNode, int level, const int& startlevel, double& max ) 
{
  //  cout << "At level = " << level << endl;
  //  cout << cNode->getString() << " " << pNode->getString() << " " << max << endl;

  if( level < startlevel ) 
    {
      for( int i = 0; i < Node::getAlphabetSize(); ++i )
	{
	  double mmax = 0;
	  Node* node = pNode->getNode( i );
	  if( node == NULL ) 
	    {
	      // cerr << "PSModifier not full!\n" << endl;
	      continue;
	    }
	  getMaxDelta( node, node, level+1, startlevel, mmax );
	  if( max < mmax ) max = mmax;
	}
    }
  else 
    {
      if( level > startlevel )
	{
	  double delta = 0;

	  // Delta already set!
 	  if( cNode->getTmpData() > 0 ) 
 	    {
 	      delta = cNode->getTmpData();
 	      if( delta > max ) max = delta;
 	      return;
 	    }
 	  else 
 	    {
	      for( int i = 0; i < Node::getAlphabetSize(); ++i )
		{
		  double d;
		  d = fabs( (double) pNode->getNextSymbCount(i) - cNode->getNextSymbProb(i)*( (double) pNode->getTotalC() ) );
		  if( d > delta ) delta = d;
		  if( delta > max ) max = delta;
		}
	}
	  // cout << cNode->getString() << " " << pNode->getString() << " MAX=" << delta << " MAXMAX=" << max << endl;
	}
      if( level == tree_->getMaxWordLength() ) return;
      for( int i = 0; i < Node::getAlphabetSize(); ++i )
	{
	  Node* node = pNode->getNode( i );
	  if( node == NULL ) 
	    {
	      // cerr << "PSModifier not full!\n" << endl;
	      continue;
	    }
	  getMaxDelta( cNode, node, level+1, startlevel, max ); 
	}
    }
}


void PSModifier::setDeltas()
{
  //cout << "HEAD=" << head_->getString() << endl;
  setDeltas( head_ );
  
  // This function was added since comparisons were only
  // made from the current word v and down in the hiearchy
  // max( delta(v, w) ) for all w but only the v of the top-node
  // If there is a delta below that is bigger it should
  // be taken
  correctDeltas( head_ );
}


void PSModifier::correctDeltas( Node* pNode )
{
  double maxdelta = pNode->getTmpData();
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i );
      if( node != NULL )
	{
	  correctDeltas( node, maxdelta );
	}
    }
  pNode->setTmpData( maxdelta );

  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i );
      if( node != NULL )
	{
	  correctDeltas( node );
	}
    }
}

void PSModifier::correctDeltas( Node* pNode, double& maxdelta )
{
  if( pNode->getTmpData() > maxdelta ) maxdelta = pNode->getTmpData();
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i );
      if( node != NULL )
	{
	  correctDeltas( node, maxdelta );
	}
    }   
}


void PSModifier::setDeltas( Node* pNode )
{
  double delta = 0;
  static int stlev = 1;
  //cout << pNode->getString() << endl;
  getMaxDelta( pNode, pNode, stlev, 1, delta );
  //cout << pNode->getString() <<"---->" << delta << endl;
  pNode->setTmpData( delta );
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i );
      if( node != NULL ) 
	{
	  setDeltas( node );
	}
    }
}




void PSModifier::prune( const int& npar ) 
{
  if( head_ == NULL )
    {
      cerr << "Pruning empty tree?\n";
      return;
    }

  Node* pNode = head_;


  setDeltas();
//   tree_->removeTerminalNodes();

//   tree_->draw();
//   exit( 0 );

  while( true )
     {
       vector<Node*> terminal = tree_->getTerminalNodes();
       vector< MyPair<Node*, double> > deltas;
       for( int i = 0; i < terminal.size(); ++i )
	 {
	   //	   cout << terminal[i]->getString() << " " <<  terminal[i]->getTmpData() << endl;
	   deltas.push_back( MyPair<Node*, double>( terminal[i], terminal[i]->getTmpData() ) );
	 }
       sort( deltas.begin(), deltas.end() );
       
       if( head_->getNumberParameters() <= npar ) break;
  
      deltas[ 0 ].getA()->schedulaToRemove();
      tree_->removeScheduled( head_ );
     }
 
  //  tree_->draw();  
}


void PSModifier::prune()
{
  Node* pNode = head_;
  setDeltas();
  prune( pNode );
  //tree_->draw();
}


void PSModifier::prune( Node* pNode )
{
  double hmax = pNode->getTmpData();
  
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i );
      if( node != NULL ) 
	{
	  vector<double> max_vec;
	  vector<double> der;
	  double prev = hmax;
	  for( int j = 1; j+1 < tree_->getMaxWordLength(); ++j )
	    {
	      double max = 0;
	      getMaxDelta( node, node, 1, j, max );
	      max_vec.push_back( max );
	      if( max != 0 ) der.push_back( prev/max );
	      else           der.push_back( 0 );
	      prev = max;
	    }
	  double max_der = *max_element( der.begin(), der.end() );
	  if( max_der == der[0]  ) 
	    {
	      // Set children of node to NULL
	      //	      pNode->setNode( NULL, i );
	      for( int ik = 0; ik < Node::getAlphabetSize(); ++ik )
		{
		  node->setNode( NULL, ik );
		}
	    }
	}
    }

  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i );
      if( node != NULL ) 
	{
	  prune( node );
	}
    }
}


void PSModifier::getMaxDeltaSubtree( Node* headNode, Node* pNode, double& max ) 
{
  double delta = 0;
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      double d = fabs( (double) pNode->getNextSymbCount(i) - headNode->getNextSymbProb(i)*( (double) pNode->getTotalC() ) );
      // cout << d << " ";
      if( d > delta ) delta = d;
      if( delta > max ) max = delta;
    }
  // cout << " MAX=" << delta << " MAXMAX=" << max << endl;
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i );
      if( node == NULL ) 
	{
	  continue;
	}
      getMaxDeltaSubtree( pNode, node,  max ); 
    }
}


void PSModifier::prune( Node* pNode, const int& npar )
{
//   double hmax = pNode->getTmpData();

//   for( int i = 0; i < Node::getAlphabetSize(); ++i )
//     {
//       Node* node = pNode->getNode( i );
//       if( node != NULL ) 
// 	{
// 	  vector<double> max_vec;
// 	  vector<double> der;
// 	  double prev = hmax;
// 	  for( int j = 1; j+1 < tree_->getMaxWordLength(); ++j )
// 	    {
// 	      double max = 0;
// 	      getMaxDelta( node, node, 1, j, max );
// 	      max_vec.push_back( max );
// 	      if( max != 0 ) der.push_back( prev/max );
// 	      else           der.push_back( 0 );
// 	      prev = max;
// 	    }
// // 	  cout << "1 " << hmax << " ";
// // 	  for( int k = 0; k < max_vec.size(); ++k )
// // 	    {
// // 	      cout << k+1 << " " << max_vec[k] << " "<< der[k] << endl;
// // 	    }
// 	  double max_der = *max_element( der.begin(), der.end() );
// 	  if( max_der == der[0]  ) 
// 	    {
// 	      // Set children of node to NULL
// 	      //	      pNode->setNode( NULL, i );
// 	      for( int ik = 0; ik < Node::getAlphabetSize(); ++ik )
// 		{
// 		  node->setNode( NULL, ik );
// 		}
// 	    }
// 	}
//     }

//   for( int i = 0; i < Node::getAlphabetSize(); ++i )
//     {
//       Node* node = pNode->getNode( i );
//       if( node != NULL ) 
// 	{
// 	  prune( node );
// 	}
//     }
}
