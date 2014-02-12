// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxNODExxx
#define xxxNODExxx


#include <iostream>
#include <vector>
#include <cassert>
#include <Alphabet.h>


using namespace std;

namespace trees 
{
  /**
   * This class is made for word-analyses on any alphabet. The node
   * contains pointers to connect to other nodes and carries data.
   */
  class Node 
  {

  public:
    /**
     * constructor ...
     */
    Node();


    /** Taking a string holding the word obtained by walking from node to root 
     * \param s string
     */
    Node( const string& s );
    ~Node();

    /**
     * Specify the Alphabet to use
     */
    static void setAlphabet( const Alphabet* a )
    {
      alphabet = a;
    } 

    /**
     * \return size of current Alphabet
     */
    static int getAlphabetSize() { return alphabet->size(); }

    static bool wordIntegrity( const string& s ) { return alphabet->testWord( s ); }

    /**
     * \return name of current Alphabet
     */
    static string getAlphabetName() { return alphabet->getName(); }

    /**
     * \return symbol at position i in current Alphabet
     */
    static char getAlphabetChar( const int& i ) { return alphabet->getChar( i ); }
   
    /**
     * \return total number of nodes
     */
    static int getNumberNodes()  { return NUMBERNODES; }

    /**
     * \return total number of free parameters
     */
    static int getNumberParameters()  { return ( ( alphabet->size() - 1 )*( DIMENSION ) ); }

    /**
     * For specifying the number of nodes in the tree, used when 
     * tree is loaded from file
     */
    static void setNumberNodes( const int& i )  { NUMBERNODES = i; }

    /**
     * For specifying the number of parameters in the tree, used when 
     * tree is loaded from file
     */
    static void setNumberParameters( const int& i )  { DIMENSION = i; }
 
    /**
     * checks a string for integrity in the specified Alphabet
     */
    static bool integrity( const string& );

    /**
     * reset class-variables
     */
    static void sReset() { NUMBERNODES = 0; DIMENSION = 0;}
    
    /**
     * Assign a node with a character which is a member of the 
     * current alphabet.
     * \param pn node to assign
     * \param c character 
     */
    void setNode( Node* pn, const char& c );

    /**
     * Assign a node with a character corresponding to 
     * position i  in the alphabet.
     * \param pn node to assign
     * \param i position in alphabet
     */
    void setNode( Node* pn, const int& i );

    /**
     * Assign the counts of the Node, used when loading from file
     */
    void setCounts( const vector<double>& p ) { count_ = p; } 

    /**
     * Assign the counts of the Node, used when loading from file
     */
    void setNextSymbolProb( const vector<double>& p ) { nextSymbolProb_ = p; } 

    /**
     * Assign the counts of the Node, used when loading from file
     */
    void setNextSymbolCount( const vector<double>& p ) { nextSymbolCount_ = p; } 

    /**
     * Assign the nextSymbolProb at position i 
     */
    void setNextSymbolProb( const int& i, const double& p ) { assert( i < nextSymbolProb_.size() ); nextSymbolProb_[i] = p; }

    /**
     * Assign the nextSymbolCount at position i
     */
    void setNextSymbolCount( const int& i, const double& p ) { assert( i < nextSymbolCount_.size() ); nextSymbolCount_[i] = p; }

    /**
     * tmpData_ is used to hold information such as delta-values 
     * in TreeModifier
     */
    void setTmpData( const double& d ) { tmpData_ = d; }
    
    /**
     * increase the count of a symbol
     * \param c char 
     */
    void increaseP( const char& c );

    /**
     * Will check if node is a leaf and if it is assign boolean
     * isLeaf_
     */
    void checkIfLeaf();

    /**
     * \return true if node is a leaf-node
     */
    bool isLeaf() const { return isLeaf_; }

    /**
     * \param c char
     * \return next-node in a Tree corresponding to symbol c
     */
    Node* getNode( const char& ) const;

    /**
     * \param i int
     * \return next-node in a Tree corresponding to symbol number i
     */
    Node* getNode( const int& i ) const;

    /**
     * \return the Node specific string obtained when walking from node to root.
     */
    string getString() const { return s_; }

    /**
     * \return XXX
     */
    double getC( const size_t& i ) { assert( count_.size() > i ); return count_[i]; }


    /**
     * \return XXX
     */
    double getC( const char& c, const bool& dummy );

    /**
     * \return total count of the node
     */
    double getTotalC() const;

    /**
     * \param i int
     * \return nextSymbolProbability of symbol number i in alphabet
     */    
    double getNextSymbProb( const int& i ) const { assert( i < nextSymbolProb_.size() ); return nextSymbolProb_[i]; }

    /**
     * \param c char
     * \return nextSymbolProbability of symbol c in alphabet
     */    
    double getNextSymbProb( const char&, const bool&  ) const;

    /**
     * \param i int
     * \return nextSymbolCount of symbol number i in alphabet
     */    
    double getNextSymbCount( const int& i ) const { assert( i < nextSymbolCount_.size() ); return nextSymbolCount_[i]; }

    /**
     * \param c char
     * \return nextSymbolCount of symbol c in alphabet
     */    
    double getNextSymbCount( const char&, const bool&  ) const;

    /**
     * tmpData_ is used to hold information such as delta-values 
     * in TreeModifier
     * \return temporary node data. 
     */
    double getTmpData() const { return tmpData_; }

    /**
     * Assigns nextSymbolProb_
     */
    void calculateProbabilities();

    /**
     * Each node has a unique identifier
     */
    int getId() const { return id_; }

    /**
     * Each node has a unique identifier
     */
    int setId( const int& id ) { id_ = id; }

    /**
     * Adjusted probabilities are used in some analysis such as AIC and BIC
     */
    bool isAdjusted() const { return isAdjusted_; }

    /**
     * Adjusted probabilities are used in some analysis such as AIC and BIC
     */
    void setAdjusted() { isAdjusted_ = true; }


    /**
     * One can schedule a node for removal at later stage ( removal when 
     * running Tree::removeScheduled().
     * \return true if this node is schedualed to be removed
     */    
    bool schedulaToBeRemoved() const { return schedualToBeRemove_; }

    /**
     * One can schedule a node for removal at later stage ( removal when 
     * running Tree::removeScheduled().
     */
    void schedulaToRemove() { schedualToBeRemove_ = true; }

    /**
     * converts a double into a string
     */
    string myToString( const double& t ) const;

    /**
     * \return string holding node-specific data used when saving Tree
     */
    string toString() const;
  
    /**
     * Print node to standard output
     */
    void print( const bool& = false ) const;

  private:
    // Common to all objects
    static int NUMBERNODES;
    static int DIMENSION; // equals number of nodes with NULLPOINTERS
    static const Alphabet* alphabet; 
    static bool headHasNullPointer;
    static double totalTotal;

    // Inner data of individuals
    vector<Node*> children_;
    vector<double> count_;
    vector<double> nextSymbolProb_;
    vector<double> nextSymbolCount_;
  
        

    string s_;  
    bool isLeaf_;
    bool isAdjusted_;

    // Used for loading and saving to file only!
    int id_;
    vector<int> relations_;

    // This parameter is added to keep node-specific data
    // stored temporary
    double tmpData_;
    bool schedualToBeRemove_;
  };
}
#endif
