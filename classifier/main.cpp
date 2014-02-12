/*
 * Main program for DNA classifier. 
 * Purpose: See Helper.h
 * Author:  Daniel Dalevi
 * Date:    09/03/2005
 **/

/*
 * STD includes
 **/
#include <iostream>
#include <vector>
#include <string>
#include <new>
#include <Exception.h>

/*
 * Local includes
 **/
#include "Parameters.h"
#include "Helper.h"
#include "Classifier.h"

/*
 * non-standard includes
 **/
#include <Exception.h>
#include <Fasta.h>
#include <RandomSingleton.h>
#include <Tree.h>
#include <FixedTree.h>
#include <PstTree.h>


using namespace std;
using namespace common;



int main( int argc, char** argv )
{
  Parameters params( true );
  params.LoadParameters( argc, argv );

  if( params.GetBoolParam( "-h" ) == true ) 
    {
      Helper::DisplayHelp( argv[0] );
      exit( 0 );
    }

  if( params.GetBoolParam( "-v" ) == true ) 
    {
      Helper::DisplayVersion( argv[0] );
      exit( 0 );
    }

  
  FileHandler* myFH;
  try {
       myFH = new FileHandler( argc, argv );
    }
  catch( common::Exception& o )
    {
      cerr << o.getText() << endl;
      if( o.getLevel() == common::Exception::ERROR ) 
	{
	  cerr << "Beyond repair, terminates ... \n";
	  exit( 1 );
	} 
    }
  
  Classifier* myClassifier = new Classifier( params, myFH );
  
  if( params.GetBoolParam( "-crr" ) ) 
    {
      try {
	myClassifier->train();
	// 	myClassifier->prune();
	// 	myClassifier->save();
      }
      catch( common::Exception& o )
	{
	  cerr << o.getText() << endl;
	  if( o.getLevel() == common::Exception::ERROR ) 
	    {
	      cerr << "Beyond repair, terminates ... \n";
	      exit( 1 );
	    }
	}
    }
  else if( params.GetBoolParam( "-sap" ) )
    {
      myClassifier->score();
    }
  else if( params.GetBoolParam( "-scan" ) )
    {
      try{
	myClassifier->scan();
      }
      catch( common::Exception& o )
	{
	  cerr << o.getText() << endl;
	  if( o.getLevel() == common::Exception::ERROR ) 
	    {
	      cerr << "Beyond repair, terminates ... \n";
	      exit( 1 );
	    }
	}
    }
  else if( params.GetBoolParam( "-sim" ) )
    {
      myClassifier->simulate();
    }
  else if( params.GetBoolParam( "-get_aic" ) )
    {
      try{
	myClassifier->modelTesting();
      }
      catch( common::Exception& o )
	{
	  cerr << o.getText() << endl;
	  if( o.getLevel() == common::Exception::ERROR ) 
	    {
	      cerr << "Beyond repair, terminates ... \n";
	      exit( 1 );
	    }
	}
    }
  else if( params.GetBoolParam( "-print" ) )
    { // Will draw model!
      myClassifier->print();
    }
  else if( params.GetBoolParam( "-pfreq" ) )
    {
      //
    }
  else if( params.GetBoolParam( "-lrt" ) )
    {
      try{
	myClassifier->lrt();
      }
      catch( common::Exception& o )
	{
	  cerr << o.getText() << endl;
	  if( o.getLevel() == common::Exception::ERROR ) 
	    {
	      cerr << "Beyond repair, terminates ... \n";
	      exit( 1 );
	    }
	}
    }
  else
  {
    cerr << "Have to specify analyse option!\n"
	 << argv[0] << " -h, for help.\n";
  }

  delete myClassifier;
  return 0; 
}
