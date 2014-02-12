// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include <algorithm>
#include <cstdlib>
#include <cctype>

#include "GeneBankRecord.h"
#include "GeneRecord.h"
#include "Exception.h"

using namespace std;
using namespace common;
/*
 * Constructor takes filename of genebank file!
 */
GeneBankRecord::GeneBankRecord( const string& filename, const string& gid )
{
  geneIdTag_ = gid;
  ifstream fin;
  fin.open( filename.c_str() );
  if( !fin )
    {
      throw Exception( "Could not open file: " + filename, Exception::ERROR );
    }  

  this->resetFeatures();
  this->resetAttributes();
  
  bool featurs = false;

  char buffer[ MAXLINEWIDTH ];

  GeneRecord myRec;
  bool firstgene = false;
  string currname = "";
  string notename = "";

  if( geneIdTag_ == "" ) geneIdTag_ = "gene=";

  while( fin.getline( buffer, MAXLINEWIDTH ) )
  {    
    string tmp_str = buffer;
    
    if( tmp_str.find( "CDS" ) < tmp_str.size() && INDfeature_ )
      {
	if( tmp_str.find( ".." ) < tmp_str.size() ) 
	  { 
	    //cout << tmp_str << endl;

	    firstgene = true;
	    // Extract information about:
	    // start-koord
	    // stop-koord 
	    // direction
	    bool complement = false;
	    if( tmp_str.find( "complement" ) < tmp_str.size() ) 
	      { 
		complement = true; 
		myRec.setDirection( 'R' ); 
	      }
	    else
	      {                                                
		myRec.setDirection( 'F' );
	      }
	    bool firstnum = false;
	    bool secondnum = false;
	    string start, stop;
	    if( complement )
	      {
		for( size_t i = 0; i < tmp_str.size(); ++i )
		  {
		    if( tmp_str[ i ] == '(' ) { firstnum = true; continue; }
		    if( tmp_str[ i ] == '.' ) { secondnum = true; continue; }
		    if( tmp_str[ i ] == ')' ) break;
		    if( firstnum && ! secondnum )
		      {
			start += tmp_str[ i ];
		      }
		    if( secondnum )
		      {
			stop += tmp_str[ i ];
		      }
		  }
	      }
	    else 
	      {
		for( size_t i = 1; i < tmp_str.size(); ++i )
		  {
		    if( tmp_str[ i ] == '.' ) { secondnum = true; continue; }
		    if( !secondnum && !isalpha( tmp_str[ i ] ) )
		      {
			if( tmp_str[ i ] != ' ' ) start += tmp_str[ i ];
		      }
		    if( secondnum )
		      {
			stop += tmp_str[ i ];
		      }
		  }
	      }
	    myRec.setStartKoord( atoi( start.c_str() ) );
	    myRec.setStopKoord( atoi( stop.c_str() ) );
	    genes_.push_back( myRec );
	  }
      }
    if(  tmp_str.find( geneIdTag_ ) < tmp_str.size() ) 
      {
	bool namestarted = false;
	string name;
	for( size_t i = 0; i < tmp_str.size(); ++i )
	  {
	    if( tmp_str[ i ] == '"' ) { namestarted = true; continue; }
	    if( namestarted && tmp_str[ i ] == '"' ) break;
	    if( namestarted ) name += tmp_str[ i ];
	  }
	myRec.setName( name );
	currname = name;
	//cout << "-->" << name << endl;
      }
    
    if( tmp_str.find( "note=" ) < tmp_str.size() )
      {
	bool namestarted = false;
	string name;
	for( size_t i = 0; i < tmp_str.size(); ++i )
	  {
	    if( tmp_str[ i ] == '"' ) { namestarted = true; continue; }
	    if( namestarted && tmp_str[ i ] == '"' ) break;
	    if( namestarted ) name += tmp_str[ i ];
	  }
	myRec.setNote( name );
      }
    
    if( TRAfeature_ )
      {
  	for( size_t i = 0; i < tmp_str.size(); ++i )
	  {
	    if( i > 0 )
	      {
		if( tmp_str[ i-1 ] != '=' &&
		    tmp_str[ i ]   == '"' ) 
		  { 
		    TRAfeature_ = false;
		    proteins_.push_back( protseq_ );
		    if( currname == "" ) proteinname_.push_back( notename );
		    else proteinname_.push_back( currname );
		    protseq_ = "";
		    break;
		  } 
	      }
	    if( tmp_str[ i ] != ' ' &&  tmp_str[ i ] != '\n' ) protseq_ += tmp_str[ i ];
	  }
      }
    
    if( tmp_str.find( "translation=" ) < tmp_str.size() ) 
      { 
	//       	cout << "TRANS = " << tmp_str << endl;
	bool start = false;
	for( size_t i = 0; i < tmp_str.size(); ++i )
	  {
	    if( start ) 
	      {
		if( tmp_str[ i ] == '"' ) 
		  {
		    TRAfeature_ = false;
		    proteins_.push_back( protseq_ );
		    if( currname == "" ) proteinname_.push_back( notename );
		    else proteinname_.push_back( currname );
		    // cout << ">" << currname << endl << protseq_ << endl; 
		    protseq_ = "";
		    break;
		  }
		if( tmp_str[ i ] != ' ' && tmp_str[ i ] != '\n' ) protseq_ += tmp_str[ i ]; 
	      }
	    if( tmp_str[ i ] == '"' ) start = true;
	  }
	
	TRAfeature_ = true;    
      }

    if( ORGfeature_ )
    {
      // cout << tmp_str;
      nucseq_ += stripSequence( tmp_str ); 
    }
    
    /*
     * Feature indicatures are set at end!
     */
    this->setFeatures( tmp_str );
  }
  //  cout << nucseq_ << endl;
 
}


/*
 * Set all indicators to false since we haven't started to 
 * process file yet.
 */ 
void GeneBankRecord::resetFeatures()
{
  INDfeature_ = false;
  ORGfeature_ = false;
  TRAfeature_ = false;
}


string GeneBankRecord::getSequence( const string& pat, bool allow_complement )
{
  string res;
  bool iscomplement = false;
  for( size_t i = 0; i < genes_.size(); ++i )
    {
      //      cout << genes_[ i ].getStartKoord() << " " << genes_[ i ].getStopKoord() << endl;
      if( genes_[ i ].isMyName( pat ) )
	{
	  if( genes_[ i ].getDirection() == 'R' ) if( allow_complement ) iscomplement = true;
	  for( size_t j = genes_[ i ].getStartKoord() - 1; j < genes_[ i ].getStopKoord(); ++j )
	    {
	      res += nucseq_[ j ];
	    }
	}
    }

  if( iscomplement ) makeComplement( res );

  return res;
}


void GeneBankRecord::printNonCoding()
{

  string res;
  bool iscomplement = false;
  int prev_idx = 0;
  for( size_t i = 0; i < genes_.size(); ++i )
    {
      bool isendl = true;

      if( prev_idx < genes_[ i ].getStartKoord() )
	{
	  cout << "> " << prev_idx+1 << " to " << genes_[ i ].getStartKoord()-1 << endl;
	  isendl = false;
	}
      for( size_t j = prev_idx, k = 0; j < genes_[ i ].getStartKoord()-1; ++j, ++k )
	{
	  isendl = false;
	  cout << nucseq_[ j ];
	  if( (k+1)%100 == 0 ) { isendl = true; cout << endl; }
	}
      if( !isendl ) cout << endl;
      prev_idx = genes_[ i ].getStopKoord();
    }
  
  // Print last stretch between too
  bool isendl = true;
  prev_idx = genes_[ genes_.size()-1 ].getStopKoord();
  if( prev_idx < genes_[ genes_.size()-1 ].getStartKoord() )
    {
      cout << "> " << prev_idx << " to " << nucseq_.size() << endl;
      isendl = false;
    }
  for( size_t j = prev_idx, k = 0; j < nucseq_.size(); ++j, ++k )
    {
      isendl = false;
      cout << nucseq_[ j ];
      if( (k+1)%100 == 0 ) { isendl = true; cout << endl; }
    }
  if( !isendl ) cout << endl;
  

}



void GeneBankRecord::printAllSequences( const bool& allow_complement )
{

  string res;
  bool iscomplement = false;
  for( size_t i = 0; i < genes_.size(); ++i )
    {
      if( genes_[ i ].getDirection() == 'R' ) if( allow_complement ) iscomplement = true;
      for( size_t j = genes_[ i ].getStartKoord() - 1; j < genes_[ i ].getStopKoord(); ++j )
	{
	  res += nucseq_[ j ];
	}
      if( iscomplement ) makeComplement( res );
      cout << ">";
      if( genes_[ i ].getName() != "" ) cout << genes_[ i ].getName() << endl;
      else cout << genes_[ i ].getNote() << endl;
      bool isendl = false;
      for( int j = 0; j < res.size(); ++j )
	{
	  cout << res[j];
	  isendl = false;
	  if( (j+1)%100 == 0 ) { isendl = true; cout << endl; }
	}
      if( !isendl ) cout << endl;
      res = "";
    }
}


string GeneBankRecord::getProteinSequence( const string& pat )
{
  for( size_t i = 0; i < genes_.size(); ++i )
    {
      if( proteinname_[ i ] == pat  )
	{
	  return proteins_[ i ];
	}
    }
  return "---NOT FOUND---";
}


/*
 * This function returns start and stop coordinates for the 
 * gene with name "pat"
 */
bool GeneBankRecord::getCoordinates( const string& pat, int& start, int& stop ) 
{
  start = stop = - 1;
  for( size_t i = 0; i < genes_.size(); ++i )
    {
      if( genes_[ i ].getName() == pat  )
	{
	  start = genes_[ i ].getStartKoord();
	  stop  = genes_[ i ].getStopKoord() ;
	}
    }
  if( start < 0 || stop < 0 ) return false;
  else return true;
}


/*
 * sets a single feature to true
 */ 
void GeneBankRecord::setFeatures( const string& tmp_str )
{
  if( tmp_str.find( "FEATURE" ) < tmp_str.size() )       INDfeature_ = true;
  if( tmp_str.find( "ORIGIN"  ) < tmp_str.size() )       ORGfeature_ = true;
}


void GeneBankRecord::printRecords()
{
  for( size_t i = 0; i < genes_.size(); ++i )
    {
      cout << genes_[ i ].getStartKoord() << "\t" 
	   << genes_[ i ].getStopKoord() << "\t"
	   << genes_[ i ].getName() << "\t"
	   << genes_[ i ].getDirection() << "\n";
    }
}

/*
 * clears attributes
 */
void GeneBankRecord::resetAttributes()
{
  nucseq_ = "";
}


string GeneBankRecord::stripSequence( const string& seq ) const
{
  string res;
  for( size_t i = 0; i < seq.size(); ++i )
    {
      if( seq[ i ] == 'a' || seq[ i ] == 'A' ) res += 'A'; 
      else if( seq[ i ] == 'c' || seq[ i ] == 'C' ) res += 'C'; 
      else if( seq[ i ] == 'g' || seq[ i ] == 'G' ) res += 'G'; 
      else if( seq[ i ] == 't' || seq[ i ] == 'T' ) res += 'T'; 
    }
  return res;
}


void GeneBankRecord::makeComplement( string& seq )
{
  for( size_t i = 0; i < seq.size(); ++i )
    {
      if( seq[ i ] == 'A' ) seq[ i ] = 'T';
      else if( seq[ i ] == 'T' ) seq[ i ] = 'A';
      else if( seq[ i ] == 'G' ) seq[ i ] = 'C';
      else if( seq[ i ] == 'C' ) seq[ i ] = 'G';
    }
  string res;
  for( int i = seq.size() - 1; i >= 0; --i )
    {
      res += seq[ i ];
    }
  seq = res;

}


void GeneBankRecord::printAllNucleotidesExcept( const int& min, const int& max )
{
  bool hasentered = false;
  bool hasprinted = false;
  for( size_t i = 0; i < nucseq_.size(); ++i )
    {
      if( i+1 >= min && i < max ) { hasentered = true; continue; }
      if( hasentered && !hasprinted ) { hasprinted = true; cout << "______";}
      cout << nucseq_[ i ];
      if( i > 0 && i%100 == 0 ) cout << endl;
    }
  cout << endl;
}

void GeneBankRecord::getDnaRegion( const size_t& min, const size_t& max )
{
  int start = min >= nucseq_.size() ? 0: min;
  for( size_t i = start; i < nucseq_.size(); ++i )
    {
      // i+1 is due to the numbering convention in c++ which starts from 0 
      // while in genebankfile starts from 1
      if( i+1 >= min && i < max ) 
	{
	  cout << nucseq_[ i ];
	}
    }
  cout << endl;
}
