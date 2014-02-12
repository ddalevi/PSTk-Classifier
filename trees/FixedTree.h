// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxFIXEDTREExxx
#define xxxFIXEDTREExxx

#include <vector>
#include "Tree.h"

using namespace std;

namespace trees
{
  class Node;
  class Exception;

  /**
   *  Repressenting a transition matrix in a stationary fixed order Markov chain
   * \author  Daniel Dalevi
   * \version 1.0
   * \date 2005-05-30
   */
  class FixedTree : public Tree 
  {
  public: 
    FixedTree() {}
    FixedTree( const Alphabet*, const int& ); 
    ~FixedTree();

    void insert( const string& );
    //    void insertEmpty( Node*, const int& );

    void print() const{ Tree::print(); }
    //    void setDeltas() { Tree::setDeltas(); }
    void print( Node* ) const;

    virtual double prob( const string& pat ) { return Tree::prob( pat ); }


    double getNLL( const string& );
    double getPseudoNLL( const string&, const double& );

    void constrainTree( const int& ) {}

//     void prune( const double&  ) {}
//     void prune( const int& ) {}
  };
}
#endif
