// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "FileHandler.h"
#include "Exception.h"

#include <fstream>

 
using namespace std;
using namespace common;


FileHandler::FileHandler( const int& argc, char** argv ) 
{ 
  params_ = new Parameters( true );
  params_->LoadParameters( argc, argv );

  setFileNames();
  strip();
}  

FileHandler::~FileHandler()
{
  if( params_ != NULL )
    delete params_;
}


void FileHandler::strip()
{
  for( int i = 0; i < fileNames_.size(); ++i )
    {
      strip( fileNames_[ i ] );
    }
}

void FileHandler::strip( string& str )
{
  string res = "";
  for( int i = 0; i < str.size(); ++i )
    {      
      if( str[ i ] != '\n' && str[ i ] != '\t' && str[ i ] != ' ' ) 
	{
	  res += str[ i ];
	}
    }
  str = res;
}


void FileHandler::setFileNames()
{
  fileNames_.clear();
  // -f_f (filenames in file) will overwrite individual -f
  string pfilename = params_->GetStringParam( "-f_f" );
  if( pfilename > "" )
    {
      ifstream fin( pfilename.c_str() );
      if( !fin ) 
	{
	  throw Exception( "Cannot open file: " + pfilename, Exception::ERROR );
	}
      char buffer[ MAXLINEWIDTH ];
      while( fin.getline( buffer, MAXLINEWIDTH ) )
	{
	  if( buffer[0] == '#' ) continue;
	  string filename = buffer;
	  string dummy = "";
	  removeDirpath( filename, dummy );	  
	  if( filename.length() < 1 ) continue;
	  fileNames_.push_back( filename );
	}
    }
  else
    {
      for( unsigned int i = 0; i < params_->GetParamListSize( "-f" ); ++i )
	{
	  string filename = params_->GetStringParam( "-f", i );
	  string dummy = "";
	  removeDirpath( filename, dummy );	
	  fileNames_.push_back( filename );
	}
    }
 }


/* 
 * --- STATIC FUNCTION ---
 * 1: rfind returns an index belonging to a LINUX-fileki
 *   (ie. found "/"). Extract filename and directory path
 * 2: rfind returns an index belonging to a WIND32-file
 *   (ie. found "\"). Extract filename and directory path
 */
void FileHandler::removeDirpath( string& s, string& dir )
{
  size_t i = s.rfind('/') + 1;
  size_t N = s.length();
  if( i < N && i != 0 )
    { 
      dir = s.substr( 0, i );	
      s = s.substr(i, N + 1 - i);
    }
  else
    { //WINDOWS
      i = s.rfind('\\') + 1;
      if( i < N && i != 0 ) 
	{
	  dir = s.substr( 0, i );	
	  s = s.substr( i, N + 1 - i ); 
	}
    }
}



/*
 * This function adds prefix, postfix etc to filenames
 */
vector<string> FileHandler::getOutputFileNames() const
{
  vector<string> res;
  // Modify filenames ...
  string dir = params_->GetStringParam( "-opwd" );
  for( unsigned int i = 0; i < fileNames_.size(); ++i )
    {
      string tmp;
      // Add prefix
      tmp = params_->GetStringParam( "-osf" ) + fileNames_[ i ]; 
	  
      // Add storage directory
      if( dir > "" ) tmp = dir + "/" + tmp;
	  
      // Add postfix
      tmp += params_->GetStringParam( "-opf" );
      res.push_back( tmp );
    }
  return res;
}



/*
 * This function returns the full input names
 */
vector<string> FileHandler::getInputFileNames() const
{
  vector<string> res;
  // Modify filenames ...
  string dir = params_->GetStringParam( "-ipwd" );
  for( unsigned int i = 0; i < fileNames_.size(); ++i )
    {
      string tmp = fileNames_[i];

      // Add prefix
      tmp = params_->GetStringParam( "-isf" ) + fileNames_[ i ]; 
	  
      // Add storage directory
      if( dir > "" ) tmp = dir + "/" + tmp;
	  
      // Add postfix
      tmp += params_->GetStringParam( "-ipf" );
      res.push_back( tmp );
    }
  return res;
}

/*
 * This function returns the full input names with a
 * string extension before the post-fix
 */
vector<string> FileHandler::getInputFileNames( const string & ext ) const
{
  vector<string> res;
  // Modify filenames ...
  string dir = params_->GetStringParam( "-ipwd" );
  for( unsigned int i = 0; i < fileNames_.size(); ++i )
    {
      string tmp;

      // Add prefix
      tmp = params_->GetStringParam( "-isf" ) + fileNames_[ i ] + ext; 
	  
      // Add storage directory
      if( dir > "" ) tmp = dir + "/" + tmp;
	  
      // Add postfix
      tmp += params_->GetStringParam( "-ipf" );
      res.push_back( tmp );
    }
  return res;
}



vector<string> FileHandler::getFileNames() const
{
  vector<string> res;
  // Modify filenames ...
  for( unsigned int i = 0; i < fileNames_.size(); ++i )
    {
      string tmp = fileNames_[i];
      res.push_back( tmp );
    }
  return res;
}




string FileHandler::toHelp() 
{
  string m = "";
  m += "---- File processing options:\n";
  m += "-f     (string) Specifying the name of a file to process\n";
  m += "                Many \"-f\" can be used\n";
  m += "-f_f   (string) Specifying a file including names of\n";
  m += "                 all files to be processed.\n";
  m += "-ipf   (string) A postfix that is common to all input\n";
  m += "                 files to process\n";
  m += "-ipwd  (string) Input directory\n";
  m += "-opf   (string) A postfix added to output files\n";
  m += "-osf   (string) A prefix added to output files \n";
  m += "-isf   (string) A prefix that is shared among all input files\n";  
  m += "-opwd  (string) Output directory\n";
  m += "----------------------------\n";
  return m;
}
