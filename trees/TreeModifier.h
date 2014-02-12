// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxTREEMODIFIERxxx
#define xxxTREEMODIFIERxxx

#include <string>
#include <Alphabet.h>

using namespace std;

namespace trees
{
  
  class Node;
  class Exception;
  class Tree;
  /**
   * Class to move functions modifying the tree-structure
   * out of the Tree-class. This to allow for a larger range
   * of modifier.
   * \author  Daniel Dalevi
   * \version 1.0
   * \date 2005-05-30
   */
  class TreeModifier 
  {
    
  protected:
    /**
     * If algorithms get stuck, do not run more than this.
     */
    const static int MAXITERATION = 1000000;

  public:
    /**
     * Default-constructor
     */
    TreeModifier();



    /** 
     * Constructor.taking a pointer to the tree.
     * \note if you use this, make sure you specify the 
     * head node of the tree explicitly.
     * \see setHead( Node* )
     */ 
    TreeModifier( Tree* tree );


    /** 
     * Constructor.taking pointer to head-node of tree
     * and a pointer to the tree
     */ 
    TreeModifier( Node* pHead, Tree* tree );

    /** 
     * Will call method cleanUp-method on head-node. \see cleanUp( Node* pNode )
     */ 
    virtual ~TreeModifier() {}

    /**
     * Use when not specifying head node in constructor
     */
    void setHead( Node* pNode ) { head_ = pNode; }
      
    /**
     * Abstract function to implement in the different TreeModifier
     * The core of the class.
     */
    virtual void prune() {}

   
    /**
     * Abstract function to implement in the different TreeModifier
     * The core of the class.
     */
    virtual void prune( const int& ) {}

    /**
     * Abstract function to implement in the different TreeModifier
     * The core of the class.
     */
    virtual void prune( const double& ) {}


    /**
     * May be implemented to return the order according to some 
     * criterion natural to the derived class
     */
    virtual int getOrder() {}

  protected:
    Node* head_;
    Tree* tree_;
  };
}
#endif
