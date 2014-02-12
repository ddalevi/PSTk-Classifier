// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "Node.h"
#include "NaiveTree.h"

using namespace trees;
using namespace std;

/*
 * constructors and destructors
 */
NaiveTree::NaiveTree( const Alphabet* alp, const int& wl )  
  : FixedTree( alp, wl )
{
}


NaiveTree::~NaiveTree()
{
}


double NaiveTree::prob( const string& pat )
{
  if( !Node::integrity( pat ) ) return 0;
  Node* pNode = head_;
  string::const_reverse_iterator irev = pat.rbegin();
  char lastSymbol = *irev;
  ++irev;
  for( ; irev != pat.rend(); ++irev )
    {
      Node* next = pNode->getNode( *irev );
      if( next == NULL ) break;
      pNode = next;
    }
  return pNode->getNextSymbCount( lastSymbol, true ) / getTotalTotal();
}
