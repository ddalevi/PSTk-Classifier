// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxKLMODIFIERxxx
#define xxxKLMODIFIERxxx

#include <string>
#include <vector>
#include <algorithm>
#include "TreeModifier.h"

using namespace std;

namespace trees
{
  
  class Node;
  /**
   * Implements function for pruning according to Kullback-Liebler method
   * earlier implemented in R.
   * \author  Daniel Dalevi
   * \version 1.0
   * \date 2005-05-30
   */
  class KLModifier : public TreeModifier
  {
    
  protected:
  public:

    /** 
     * Constructor, see base-class
     */ 
    KLModifier( Tree* tree );

    /** 
     * Constructor, see base-class
     */ 
    KLModifier( Node* pHead, Tree* tree );

    /** 
     * destructor implemented with empty body
     */ 
    ~KLModifier();

    void prune() {}
    /**
     * This is a special version of the pruning algorithm that keeps
     * the "num" highest scores of delta-values. Can be used to find
     * the best model of a certain number of parameters.
     * \param num integer that specify the free parameters in a model
     */
    void prune( const int& num );

    /**
     * Pruning according to Buhlmann and Mächler, using a LRT
     * based on the Kullback Liebler distance. Originally 
     * implemented in R.
     * \param cutoff in algorithm
     */
    void prune( const double& cutoff );


    /**
     * Not implemented
     */
    int getOrder() { return -1; }


  protected:
    double getDelta( Node* pNode, Node* next );
    void getAllDeltas( Node* pNode, vector<double>& deltas  );
    void prune( Node* pNode, const double& cutoff, bool& hasRemoved );
    bool prune( Node* pNode, const double& cutoff, bool& hasRemoved, const int& num );
  };
}
#endif
