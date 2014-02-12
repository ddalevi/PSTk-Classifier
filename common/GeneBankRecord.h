// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef _GENEBANKRECORD_
#define _GENEBANKRECORD_

#include <fstream>
#include <string>
#include <vector>
#include "GeneRecord.h"

using namespace std;

class GeneRecord;

namespace common 
{
class GeneBankRecord
{
  static const int MAXLINEWIDTH = 10000;
public:
  GeneBankRecord( const string&, const string& = "" );
  ~GeneBankRecord();

  void resetFeatures();
  void setFeatures( const string& );
  void printRecords();
  vector<GeneRecord> getGeneRecords() const { return genes_; }
  string getSequence( const string& pat, bool allow_complement = true );
  bool getCoordinates( const string&, int&, int& );
  void getDnaRegion( const size_t&, const size_t& );
  string getDnaSequence() const { return nucseq_; }
  void printAllSequences( const bool& allow_complement = true );
  void printNonCoding();
  string getProteinSequence( const string& );
  void printAllNucleotidesExcept( const int& , const int& );

private:
  vector<GeneRecord> genes_;
  vector<string> proteins_, proteinname_;
  string nucseq_;
  string protseq_;
  string geneIdTag_;


  /*
   * booleans indicating where we are in the file
   */
  bool INDfeature_;
  bool ORGfeature_;
  bool TRAfeature_;

  void resetAttributes();
  string stripSequence( const string& ) const;
  void makeComplement( string& seq );


};

};

#endif
