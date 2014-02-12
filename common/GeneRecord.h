// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef _GENERECORD_
#define _GENERECORD_

#include <iostream>
#include <string>

/*
 * Keeps a message for error-handling
 */

using namespace std;

class GeneRecord
{    
public:
  GeneRecord() 
  {}
  GeneRecord( const string& name,
	      const char& dir, 
	      const int& start,
	      const int& stop ) :
    name_( name ),
    direction_( dir ),
    startkoord_( start ),
    stopkoord_( stop )
  {}
  ~GeneRecord()
  {}
  char getDirection() const { return direction_; }
  string getName() const    { return name_; }
  string getNote() const    { return note_; }
  string getProteinSequence() { return protseq_; }
  bool isMyName( const string& pat ) { if( pat == name_ ) return true; else return false; }
  int getStartKoord() const { return startkoord_; }
  int getStopKoord() const  { return stopkoord_; }
  
  void setName( const string& n )    { name_ = n; }
  void setNote( const string& n )    { note_ = n; }
  void setDirection( const char& c ) { direction_ = c; }
  void setStartKoord( const int& i ) { startkoord_ = i; }
  void setStopKoord( const int& i )  { stopkoord_ = i; }
  void setProteinSequence( const string& s ) { protseq_ = s; }

  void Print() 
  { 
    cout << name_ << " " 
	 << direction_ << " "
	 << startkoord_ << " " 
	 << stopkoord_ << endl;
  }
private:
  string name_;
  string note_;
  char direction_; // R = reverse, F = forward 
  int startkoord_; // startkoordinate in nuc-seq
  int stopkoord_; // stopkoordinate in nuc-seq
  string protseq_;

};



#endif
