// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxPSMODIFIERxxx
#define xxxPSMODIFIERxxx

using namespace std;

#include "TreeModifier.h"

namespace trees
{
  
  class Node;
  class Tree;
  /**
   * Implements function for pruning according to <b>Peres-Shields <br>
   * fluctuation formulae</b>. 
   * Let <br><br>
   * \f$
   * N_x(v) := |\{ i \in [n] \mid x_i^{i+\ell} = v\}|,
   * \f$
   * <br><br>
   * denote the frequency of occurrence of the word v of length \f$\ell \leq n\f$ in \f$x_1^n\f$. 
   * <br><br>
   * Using these frequencies, we can form the <k>empirical transition probabilities</k>: for \f$v \in \Gamma^{\ell}$ and
   * $a \in \Gamma\f$,<br><br>
   * \f$
   * \tilde{p}_{v,a} := N_x(va)/N_x(v) 
   * \f$<br><br>
   * 
   * The basic observation of Peres and Shields is that if the source is of true order k, then <br>
   * for any \f$v \in \Gamma^{\ell}\f$, the empirical probabilities
   * \f$\tilde{p}_{v,a}\f$ should be very close to the empirical probabilities <br>
   * \f$\tilde{p}_{\tau_k(v),a}\f$, where \f$\tau_k(v)\f$ denotes the \f$k\f$-suffix of \f$v\f$ i.e. \f$\tau_k(v) := (v_{\ell-k+1}, \cdots,v_{\ell})\f$. 
   * 
   * To quantify this, introduce the <k>Peres--Shields Fluctuation</k> function <br><br> 
   * \f$
   * \label{eq:fluc-fun}
   * \Delta^k_x(v) := \max_{a \in \Gamma} \left|N_x(va) - \frac{N_x(\tau_k(v)a)}{N_x(\tau_k(v))} N_x(v)\right|.
   * \f$<br><br>
   * If the true order is k or less, one expects this fluctuation to be ``small'', otherwise ``large''.
   * 
   * \author  Daniel Dalevi
   * \version 1.0
   * \date 2005-05-30
   */
  class PSModifier : public TreeModifier
  {
    
  protected:
  public:

    /** 
     * Constructor, see base-class
     */ 
    PSModifier( Tree* tree );

    /** 
     * Constructor, see base-class
     */ 
    PSModifier( Node* pHead, Tree* tree );

    /** 
     * destructor implemented
     */ 
    ~PSModifier();

    /**
     * The Peres-Shields method implemented using the interpretation of a <br>
     * sharp transition. See Dalevi and Dubhashi, submitted.
     */
    void prune();

    /**
     * This pruning method works by removing the nodes with lowest deltas <br>
     * until the model has exaclty npar number of parameters. 
     * \param npar integer specifying how many parameters the model should have. 
     */
    void prune( const int& npar );

    /** 
     * Currently, no cutoff can be specified, the method
     * will call prune().
     * \param double which is a dummy
     */
    void prune( const double& ) { prune(); }   

    /**
     * Returns the order according to when the sharp transition 
     * occurs.
     * \return order of the Markov chain
     */
    int getOrder();


  protected:
    /**
     * Assign delta to all nodes and stores the results in nodes 
     * private variable tmpData_.
     */
    virtual void setDeltas();    

    void correctDeltas();
    void correctDeltas( Node* );
    void correctDeltas( Node*, double& );

    
    vector<double> getMaxDelta();
    void getMaxDeltaSubtree( Node*, Node*, double& ); 
    void getMaxDelta( Node*, Node*, int, const int&, double& );
    void setDeltas( Node* );

    /**
     * \warning THIS FUNCTION LEAKS MEMORY <-- QUICK FIX <br>
     * --> TERMINATE PROGRAM AFTER RUN OF THIS FUNCTION!!<br>
     * FUNCTION UNDER DEVELOPMENT
     */
    void prune( Node* );

    void prune( Node*, const int& npar );


  };
}
#endif
