// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxTREExxx
#define xxxTREExxx

#include <algorithm>
#include <fstream>
#include <string>
#include <Exception.h>
#include <StringTokenizer.h>
#include <Alphabet.h>
#include <new>
#include "TreeModifier.h"

using namespace std;

/**
 * Contains all basic members needed to make different types
 * of trees for Markov models
 */
namespace trees
{
  
  class Node;
  class Exception;

  /**
   *  To provide a common interface for all trees used in repressenting 
   *          Markov models for different alpabets.
   * \author  Daniel Dalevi
   * \version 1.0
   * \date 2005-05-30
   */
  class Tree 
  {
    
  protected:
    static int DEPTH;
    static const string BADALPHABET;

  public:
    /** 
     * Default constructor. \note class requires Alphabet so the use of 
     * this constructor should be avoided. 
     * \see Alphabet.h
     */ 
    Tree();

    /**
     * \param alp Alphabet
     * \param wl maximum word-length
     */ 
    Tree( const Alphabet* alp, const int& wl ); 

    /** 
     * Will call method cleanUp-method on head-node. \see cleanUp( Node* pNode )
     */ 
    virtual ~Tree();

    /** 
     * Will call delete on pNode and all its children.
     */ 
    void cleanUp( Node* pNode );


    /**
     * Function that will transform probabilities to non-cumulative
     * ones
     */
    void adjustNextSymbolCount();

    /**
     * Function that will recursivly add pseudo-counts
     * to all nodes where next-symbol-probabilities are
     * equal to zero!
     */
    void addPseudoCounts();


    /**
     * Auxiliary function
     */
    void setHeadForTM( TreeModifier* tm ) const { tm->setHead( head_ ); }


    void addPseudoCounts( Node* );

    /**
     * Will add count of one to all children of Node*,
     * and their childres and so on...
     */
    void propagatePseudoCounts( Node* );

    /**
     * Estimating the order of a fixed order Markov chains
     * \return integer  
     */
    int getFixedOrder() const
    {
      return treeMod_->getOrder();
    }

    /**
     * Assigns name to tree
     * \param n name 
     */
    void setName( const string& n ) { name_ = n; }

    /**
     * The node id is an integer specific to a node.
     * \param pNode node to assign id
     * \param id identifier
     */
    void setNodeId( Node* pNode, int& id );

    /**
     * \return name of tree
     */
    string getName() const { return name_; }
  
    /**
     * Assigns the next-symbol-probabilities associated with a node.
     * Called after sequences have been inserted into tree 
     * \see insert( const string& )  
     */
    void setProbabilities();
    
    /**
     * Function to specify the use of non-cumulative probabilities.
     * It must be set to true if evaluating the AIC of a model.
     * \param b boolean
     * \see getAIC( const string& s ) 
     * \see prune( const double& cutoff ) 
     * \see prune( const int& num ) 
     * \see adjustNextSymbolCount( Node* )
     */
    void useAdjustedProbabilities( const bool& b ) { useAdj_ = b; }
 
    /**
     * \see setProbabilities()
     */
    void setProbabilities( Node* );


    /**
     * This function will specify which algorithm to use when pruning the tree
     * If none specified, no pruning!
     * \param tm pointer to TreeModifier
     * \note function deletes previous instances of TreeModifier
     */ 
    void setTreeModifier( TreeModifier* tm );
    

    /**
     * Will print a sequence according to the specified model.
     * \param l length
     */
    void printRandomSequence( const int& l );

    /**
     * generates a random sequence according to model
     * \param l = length
     * \param s = seed
     */
    string getRandomSequence( const int& l, const int& s = -1 );

    /**
     * \see save()
     */
    void save( Node*, ofstream& );

    
    /**
     * \return double, negative log-likelihood of model
     */
    double getNLL();


    /**
     * \return double, negative log-likelihood
     */
    void  getNLL( Node*, double&);

    /**
     * \return double, negative log-likelihood of string
     * \param s string of symbols 
     */
    virtual double getNLL( const string& s ) {}

    /**
     * Not yet implemented, should use pseudo-counts
     * when probabilities are undefined.
     */
    virtual double getPseudoNLL(  const string&, const double& ) {}

    /**
     * Function returning the depth of tree
     */
    int depth();

    /**
     * prints nucleotide frequencies. 
     */
    virtual void print() const;//  const bool& = false ) const;

    /**
     * Draw a PST diagram of the model in a similar fashion as 
     * done in "R"
     */
    void draw() const;

    /**
     * \see draw()
     */
    void draw( Node*, string ) const;

    /**
     * Saves tree into a text file 
     * \param filename name of file
     */
    void save( const string& filename );

    /**
     * Loads a saved tree into memory
     * \param filename name of file
     */    
    void load( const string& filename );

    
    /**
     * \param s string of which to find the count \f$N(s)\f$
     * \return \f$N(s)\f$
     */
    double getCount( const string& s ) const;

    /**
     * This function returns the count of the prefix of the pattern "pat" <br>
     * It must be used for calculating the transition probabilities <br>
     * since the trees are stooring data in the opposite direction. <br>
     * TTAAA is inserted as: <br>
     * A->AA->AAA->AAAT->AAATT  <br>
     * prob(AAATT) = N(TTAAA)/N(TAAA*) 
     * \return \f$N(a_1...a_{n-1}*)\f$ (double)  
     */
    double getSuffixCount( const string& ) const;

    /**
     * If no argument given, the model will be evalutated
     * \param s string
     * \return AIC of the string s or by default the model
     */
    double getAIC( const string& s = "" );

    /**
     * If no argument given, the model will be evalutated
     * \param s string
     * \return BIC of the string s 
     */
    double getBIC( const string& s = "" );

    /**
     * \return the count of all nodes, ie. the number of data
     */
    double getTotalTotal();


    /**
     * \see getTotalTotal()
     */
    void totalTotal( Node*, double& );


    /**
     * Resets static variables in Node
     */
    void sReset();

    /**
     * clear the entire Tree
     */
    void clear();
    
    /**
     * Funciton for inserting a sequence into the tree
     * \param seq string to insert into tree
     */
    virtual void insert( const string& seq ) {}

    /**
     * Function removing all nodes with a count 
     * less than \"-minc\"
     */
    virtual void constrainTree( const int& ) {}
    
    /**
     * The pruning has been aggregated to the 
     * class TreeModifier. This function was designed
     * for constraining a tree to a specific number
     * of parameters.
     * \param npar integer
     */
    void prune( const int& npar );

    /**
     * The pruning has been aggregated to the 
     * class TreeModifier. This function can 
     * supply a cut-off to the pruning
     * algorithms
     * \param cutoff double
     */
    void prune( const double& cutoff );

    /**
     * Different derived classes should be able to
     * print the repressentation differently
     */
    virtual void print( Node* ) const;

    /**
     * \param s string
     * \return probability of the string s according to model
     */
    virtual double prob( const string& );

    //    void printTmp( Node* ) const;

    /**
     * Function for obtaining all defined contexts
     * \param res resulting contexts
     * \param s should be an empty string
     * \param depth of tree
     */
    void getAllPatterns( vector<string>& res, string s, const int& n );

    /**
     * Check if the model is an M0 Markov model
     */
    bool isM0() const;

    /**
     * \return vector of pointers to all termninal nodes
     */
    vector<Node*> getTerminalNodes() const;

    
    /**
     * removes all nodes that are "scheduled"
     */
    void removeScheduled( Node* pNode );
    
    /**
     * remove all terminal nodes
     */
    void removeTerminalNodes();
    void removeTerminalNodes( Node* );


    /**
     * \return The maximum depth of tree
     */
    int getMaxWordLength() const { return maxWordLength_; }


  protected:
    /**
     * inserts a word into the tree
     * \param w string
     * \see insert( const string& )
     */
    void insertWord( const string& w );//, const bool& = true );
    
    /**
     * \see insertWord( const string& )
     */
    void insertWord( Node*, const string&, string& );//, int  );//, const bool& = true );

    /**
     * \see depth()
     */
    void depth( Node*, int, int& );

    /**
     * Function evaluating the number of Tokens in string-tokenizer
     */
    void checkNumberTokens( StringTokenizer&, const int&, const string&, const int& );
   
    /**
     * Function adjusting the probabilities in tree to non-cumulative once
     * needed for calculating AIC of a model
     */
    void adjustNextSymbolCount( Node* );

    /**
     * Auxiliary function
     * \see vector<Node*> getTerminalNodes() const
     */
    void getTerminalNodes( Node*, vector<Node*>& res ) const;
    



    /**
     * Should be called by children of Tree after inserting the full sequence
     * It will remove all branches that have zero count. These can arise
     * from when inserting the last part of the seq. For example, AAAAAAT will 
     * result in the words AT, AAT, AAAT, AAAAT ... which will have no
     * defined nextSymbolProbabilities.
     */
    void removeZeroes();
    
    /**
     * Used by removeZeroes in a recursive manner.
     */
    void removeZeroes( Node* );
  
    /**
     * modified(): Should be called whenever tree topology changes 
     */
    void modified() { DEPTH = -1; } 

    /**
     * \return true if tree has been modified
     */
    bool isModified() { return DEPTH == -1; }
    

  protected: // instance variables
    Node* head_;
    TreeModifier* treeMod_;
    unsigned int total_;
    bool firstCall_;
    bool hasRemovedNodes_; /**< Added for handling terminal nodes */
    double totalTotal_;
    int maxWordLength_;
    string name_;
    bool useAdj_;
    vector<Node*> terminalNodes_;
  };
};
#endif
