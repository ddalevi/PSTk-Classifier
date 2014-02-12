// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include <string>
#include <fstream>
#include <iostream>
#include <RandomSingleton.h>
#include "Fasta.h"

using namespace std;


Fasta::Fasta()
{
  fastaname_ = "";
  prand_ = RandomSingleton::instance();
  //  prand_->randomize();
  firstCall_ = true;
}

void Fasta::setSeed( const int& seed )
{
  prand_->randomize( seed );
}


int Fasta::getLength()
{
  int length = 0;
  if( fin_.peek() == EOF ) return length;
  if( fin_.get() != '>' ) { cerr << "This is no fasta file!\n"; }

 char buff[ MAXLINELENGTH ];

  // Get identifier from ">" line
  fin_.getline( buff, MAXLINELENGTH );  

  while( fin_.peek() != '>' && fin_.peek() != EOF ) 
    { 
      fin_.getline( buff, MAXLINELENGTH );
      for( int i = 0; buff[ i ] != '\0' && MAXLINELENGTH; ++i )
	{
	  if( buff[i] == 'A' || buff[i] == 'a' || 
	      buff[i] == 'C' || buff[i] == 'c' || 
	      buff[i] == 'G' || buff[i] == 'g' || 
	      buff[i] == 'T' || buff[i] == 't' ) ++length;
	}
    }
  this->rewind();
  return length; 
}


bool Fasta::getNext( string& id, string& sequence )
{
  // This line was added so that one does not need to 
  // reset sequence manually!
  sequence = "";

  if( fin_.peek() == EOF ) return false;
  if( fin_.get() != '>' ) { cerr << "This is no fasta file!\n"; }


  char buff[ MAXLINELENGTH ];

  // Get identifier from ">" line
  fin_.getline( buff, MAXLINELENGTH );  

  id = buff;
  
  
  while( fin_.peek() != '>' && fin_.peek() != EOF ) 
    { 
      fin_.getline( buff, MAXLINELENGTH );
      sequence += buff;
    }
  return true;
}


void Fasta::chomp( string& str )
{
  string tmp_str = "";
  for( size_t i = 0; i < str.size(); ++ i)
    {
     if( str[i] == ' ' || 
	 str[i] == '\n' || 
	 str[i] == '\r' ) continue;
     tmp_str += str[i];
    }
  str = tmp_str;
}


bool Fasta::setSequence()
{
  if( fin_.peek() == EOF ) return false;
  if( fin_.get() != '>' ) { cerr << "This is no fasta file!\n"; }

  sequence_ = "";

  char buff[ MAXLINELENGTH ];

  // Get identifier from ">" line
  fin_.getline( buff, MAXLINELENGTH );  
  //  id = buff;

  while( fin_.peek() != '>' && fin_.peek() != EOF ) 
    { 
      fin_.getline( buff, MAXLINELENGTH );
      sequence_ += buff;
    }
  chomp( sequence_ );
  return true;
}

/*
 * Set sequence will be run first call
 */
string Fasta::getSequenceFromRandomIntervall( const int& len, double& start ) 
{
  if( firstCall_ )
    {
      if( !setSequence() ) ; //return false;
      //setSeed( 0 );
      firstCall_ = false;
    }
  
  int startPos = (int) ( prand_->flat()*( (int) sequence_.size() - ( len + 1 ) ) );

  if( start >= 0 )
    {
      int i = 0;
      // previous start is not allowed to be in the same intervall, ie. start != [startPos, startPos+len]
      for( ; i < 100 && ( start >= startPos && start < ( startPos + len ) ); ++i )
	{
	  startPos = (int) ( prand_->flat()*( (int) sequence_.size() - ( len + 1 ) ) );
	}
      if( i >= 99 ) cerr << "Warning, have not found ok startPos in 100 reps!\n";
    }
  assert( startPos + len < sequence_.size() );
  start = startPos;
  return sequence_.substr( startPos, len );
}


Fasta::~Fasta()
{
}
