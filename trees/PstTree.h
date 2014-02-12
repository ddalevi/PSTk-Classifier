// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxPSTTREExxx
#define xxxPSTTREExxx


#include <string>
#include <cmath>
#include <vector>
#include "Tree.h"

using namespace std;

namespace trees
{
  class Node;
  class Exception;
  
  /**
   * PST = Prediction suffix tree ...
   *
   */
  class PstTree : public Tree 
  {
  public: 
    PstTree() {}
    PstTree( const Alphabet*, const int& ); 
    ~PstTree();

    /**
     * Method for inserting a string representing
     * a sequence of characters (eg. DNA)
     */
    void insert( const string& );

    void print() { Tree::print(); }
    void print( Node* p ) const { Tree::print( p ); }
    //    void setDeltas() { Tree::setDeltas(); }

    /**
     * Will return negative log likelihood of sequence 
     * according to Markov model. The longest 
     * prefix will be used for all patterns. Depth of tree will
     * be used for the longest of all patterns 
     */
    double getNLL( const string& );

    /**
     * This function returns the NLL when adding a minimal probability
     * to counts where no counts exist. NOT YET IMPLEMENTED ....
     */
    double getPseudoNLL( const string&, const double& );

    double prob( const string& pat ) { return Tree::prob( pat ); }


    /**
     * This function fill remove all leaves that do not occur at 
     * least "min" number of times
     */
    void constrainTree( const int& );
    void constrainTree( Node*, const int& );
  };
}
#endif
