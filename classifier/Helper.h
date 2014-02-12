// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include <string>
#include <iostream>
#include <TreeFactory.h>

#include "FileHandler.h"

namespace Helper
{
  using namespace std;
  
  string version() 
    {
      return "( 1, 0, 3 )\nLast update 13 September 2006.";
    }
  
  
  void DisplayHelp( const string& progName ) 
  {
    cout << "\n"
	 << "-------------------------------------------------------------------\n"
	 << "PSTk-Classifier " << version() << endl
	 << "Usage: " << progName << " options\n\n"
	 << "\n---- Analyse options:\n"
	 << "-alp:    Alphabet, 0=Binary, 1=DNA, 2=Protein (1)\n"
	 << "-l:      Length of sequence when randomly samples from fasta\n"
	 << "         as done in the \"-sap\" option\n (1000)\n"
	 << "-crr:    Create a random profile tree of 1 - \"frac\" percent\n"
	 << "         of the sequence. Remaining part will be saved in a file\n"
	 << "         specified with \"off\"\n"
	 << "-ffn:    Used to concatenate regions when training, if sequence\n"
	 << "         format is ffn\n"
	 << "-frac:   See \"-crr\"\n"
	 << "-aic:    Prints AIC value for PST (not tested)\n"
	 << "-nsamp:  Number of samples of random sequences drawn from\n"
	 << "         sequence \"-seq\" specified in \"-sap\" option\n"
	 << "         negative number=whole sequence will be used (-1)\n"
	 << "-nofna:  Do not create a fasta file for the remainder \n"
	 << "         sequence (test-set). \n"
	 << "-print:  Draw tree-structure of model specified with \"-f\"\n"
	 << "-pseudo: Add pseudo-counts to weak nodes where next-symbol\n"
	 << "         counts are zero. A unit will be added to each of the\n"
	 << "         next-symbol-counts\n"
	 << "-revcomp:Use when also consider reverse comp. strand (false)\n"
	 << "-sap:    Score against profile \"-crr\"\n"
	 << "-scan:   Score against itself using window \n"
	 << "-s:      Seed for random number generator, 0=use clock (0)\n"
	 << "-slen:   Step increment in \"-scan\" (1) \n"
	 << "-win:    Size of window \"-win\" (10) \n"
	 << "-h:      View this help text\n"
	 << "-v:      View version of software\n"
	 << TreeFactory::toHelp()
	 << FileHandler::toHelp()
	 << "\nExamples:\n"
	 << "./classifier -crr -f_f my_list_of_species.txt -ipf .fna -ipwd data_folder -opwd profiles -osf 16_ -pseudo -npar 16 -minc 15 -kmax 7 -frac 0.1 -s 333 -nofna\n"
	 << "---/\n"
	 << "./classifier -sap -s 333 -f_f my_list_of_species.txt -ipf .tree -ipwd profiles -isf m2_ -seq profiles/m2_mySequences.fna -nsamp 100 -l 35 -m 0 -revcomp\n"
	 << "---/\n";

  }

  void DisplayVersion( const string& progName ) 
  {
    cout << "PSTk-Classifier " << version() << endl;
  }

}
