// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxCLASSIFIERxxx
#define xxxCLASSIFIERxxx

#include <memory>
#include <Tree.h>
#include <RandomSingleton.h>
#include "FileHandler.h"
using namespace std;

class Parameters;

/**
 * Purpose: To provide an interface for Bayesian classification using different models
 *          of liklihoods of DNA sequences. The DNA sequences will be repressented using
 *          short oligomers and all models are of class Tree. The primary purpose of 
 *          the class is to identify irregular genes in genomes of bacteria and plasmids 
 * \author:  Daniel Dalevi
 * \date   09/03/2005
 */
class Classifier
{
public:
  /**
   * Constructor takes two arguments. One, a parameter object
   * that reads extract info from command line. Two, a file handler
   * which will be used for adding pre-, post-, fixes to files.
   */
  Classifier( Parameters&, const FileHandler* );

  /**
   * Destructor doing nada!
   */
  ~Classifier();


  /**
   * Use this function to create a profile for a bacterium.
   * The profile will be made of a part of the fasta-sequence
   * and stored in a tree-file which can later be saved using 
   * the save() function. The remaining fraction "-frac" will 
   * be stored in a new fasta file "-off".
   */
  void train();

  /**
   * This function calculates scores a sequence against the
   * pre-calculated profiles and outputs result
   */
  void score();

  /**
   * So far only outputs the AIC and BIC values ...
   * ADD MORE COMMENTS!
   */
  void modelTesting();

  /**
   * Performs a likelihood ratio test between to objects.
   * ADD MORE COMMENTS!
   */
  void lrt();

  /**
   * ADD MORE COMMENTS
   */
  void scan();

  /**
   * ADD MORE COMMENTS
   */  
  void score( const string&, const string& = "" );

  /**
   * Prints the underlying model for the loaded tree
   */
  void print() const;

  /**
   * Prints a random sequence from the loaded tree 
   * of a user-specified length.
   */
  void simulate();

  /**
   * Returns the Negative log likelihood
   */
  double getNLL();

  /**
   * Returns true if a file already exists, else false
   */
  bool fileExists( const string& );

private:
  /**
   * ADD MORE COMMENTS
   */
  void initRandom();

  
  auto_ptr<trees::Tree> tree_;
  Alphabet* alphabet_;
  Parameters* params_; // Not owned by class, cannot be made const due to nature of Par... 
  RandomSingleton* random_;
  const FileHandler* fileHandler_; // Not owned by class
};

#endif

