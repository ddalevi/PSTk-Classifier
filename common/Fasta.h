// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxFASTAxxx
#define xxxFASTAxxx

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <RandomSingleton.h>

using namespace std;

class rlu_random;

/**
 * Class holding and performing operations
 * on a fasta-file. (type *.fna or *.ffn in Genbank-format)
 * \note Lines MUST be broken, if longer than constant MAXLINELENGTH
 * the entire sequence will not be read.
 * \autor Daniel Dalevi
 * \date 2004-spring
 */
class Fasta 
{
  static const size_t MAXLINELENGTH = 10000;
public:
  /**
   * Instantiates the random singleton if necessary
   */
  Fasta();

  /**
   * Doing nothing but default actions
   */
  ~Fasta();

  /**
   * Specify the fasta-file to use
   */
  void setFastaFile( const string& s ) { fastaname_ = s; this->open(); } 

  /**
   * If random regions should be drawn from the fasta sequence use
   * this funciton if wanting to specify seed
   */
  void setSeed( const int& seed );

  /**
   * \return name of fasta-sequence read from header-line
   */
  string getName() const { return fastaname_; }

  /**
   * Will get next entry in (call once un-less multifastasfile)
   */
  bool getNext( string&, string& );

  /**
   * \return a random string of length l
   */
  string getSequenceFromRandomIntervall( const int&, double& );

  /**
   * \return the length of the fasta-file
   */
  int getLength(); 

  /**
   * \param str string
   * Removes space and new-line characters from the string 
   */
  void chomp( string& str );

  /**
   * rewind the fasta-file so that getNext() will return the first sequence.
   */
  void rewind() 
  {
    assert( fastaname_.length() > 0 );
    fin_.close();
    fin_.open( fastaname_.c_str() );
    if( !fin_ ) 
      {
       cerr << "Could not open file: " << fastaname_ << endl;
       exit( 0 );
      }
  }


private:
  string fastaname_;
  ifstream fin_;
  string sequence_;
  RandomSingleton* prand_;
  bool firstCall_;
 

  bool setSequence();
  
  /**
   * open the fasta-file for reading
   */
  void open() 
  {
    assert( fastaname_.length() > 0 );
    fin_.open( fastaname_.c_str() );
    if( !fin_ ) 
      {
       cerr << "Could not open file: " << fastaname_ << endl;
       exit( 0 );
      }
  }



};


#endif


