// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxNAIVETREExxx
#define xxxNAIVETREExxx

#include <vector>
#include "FixedTree.h"

using namespace std;

namespace trees
{
  class Node;
  class Exception;
  
  /**
   *  Tree structure to hold naive probabilities for different words.
   * \author  Daniel Dalevi
   * \version 1.0
   * \date 2005-05-30
   */
  class NaiveTree : public FixedTree 
  {
  public: 
    NaiveTree() {}
    NaiveTree( const Alphabet*, const int& ); 
    ~NaiveTree();

    double prob( const string& pat );
  };
}
#endif
