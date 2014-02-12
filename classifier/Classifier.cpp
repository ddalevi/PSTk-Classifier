// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "Classifier.h"

#include <PstTree.h>
#include <FixedTree.h>
#include <NaiveTree.h>
#include <TreeFactory.h>
#include <Fasta.h>
#include <Exception.h>
#include <algorithm>
#include <memory>
#include <RandomSingleton.h>
#include <Node.h>
#include <Util.h>
#include "Parameters.h"

using namespace common;
using namespace std;


Classifier::Classifier( Parameters& params, const FileHandler* fh )
{
  auto_ptr<trees::Tree> tmp( TreeFactory::getObject( params ) );
  tree_ = tmp;
  fileHandler_ = fh;
  params_ = &params;
}

Classifier::~Classifier()
{
}



bool Classifier::fileExists( const string& filename )
{
  ifstream fin( filename.c_str() );
  if( fin ) 
    {
      fin.close();
      return true;
    }
  fin.close();
  return false;
}


void Classifier::train() 
{

  // Initialize pseudo-random object
  initRandom();

  double rnd_number = random_->flat();

  vector<string> infiles = fileHandler_->getInputFileNames();
  vector<string> outfiles = fileHandler_->getOutputFileNames();
  vector<string> files = fileHandler_->getFileNames();

  assert( infiles.size() == outfiles.size() );

  vector<string>::iterator o_file = outfiles.begin();
  vector<string>::iterator n_file = files.begin();
  for( vector<string>::iterator i_file = infiles.begin(); 
       i_file != infiles.end(); 
       ++i_file, ++o_file, ++n_file )
    {
      cout << "-->Processing: " << *n_file << endl;
      // Open the fasta file and get the sequence
      auto_ptr<Fasta> myFasta( new Fasta() );
      myFasta->setFastaFile( *i_file ); 
      string name, seq;
      if( params_->GetBoolParam( "-ffn" ) )
	{
	  string s;
	  while( myFasta->getNext( name, s ) != false )
	    {
	      // The X is added as separator between coding regions
	      seq += "X" +  s; 
	      s = ""; 
	    }
	  name = *i_file;
	}
      else
	{
	  myFasta->getNext( name, seq );
	}
      if( seq.size() == 0 ) 
	{
	  cerr << "Warning: This fasta file is empty: " << *i_file << endl;
	  cerr << "skip...\n";
	  continue;
	}

 
      // Get a fraction of the sequence
      double fraction = params_->GetDoubleParam( "-frac" );
      double length = fraction*seq.length();
      
      double startKoord = rnd_number*seq.length();

      
      while( startKoord + length > seq.length() ) 
	{
	  startKoord = random_->flat()*seq.length();
	}
      double stopKoord = startKoord + fraction*seq.length(); 

      string toFasta, toProfile;

      for( int i = 0; i < seq.size(); ++i )
	{
	  toProfile += seq[ i ]; 
	}
  
      // Save the unused sequences to output fasta file so
      // user can score these against different profiles 
      // in next run!
      if( *o_file == "" ) 
	{
	  cerr << "Empty filename, " << *o_file << ", cannot save!\n";
	  cerr << "skip ...\n";
	  continue;
	}

      string ofile1 = *o_file + ".fna";
      string ofile2 = *o_file + ".tree";

      if( fileExists( ofile2 ) )
	{
	  cerr << "File, " << ofile2 << ", exists, remove first!\n";
	  cerr << "skip ...\n";
	  continue;
	}


      // This section of code creates the Fasta-file for test-set
      if( !params_->GetBoolParam( "-nofna" ) )
      {
	for( int i = 0; i < seq.size(); ++i )
	  {
	    if( (double) i >= startKoord && (double) i < stopKoord )
	      {
		toFasta += seq[ i ];
	      }
	  }
	ofstream fout( ofile1.c_str(), ios::out );
	if( !fout ) 
	  {
	    cerr << "Cannot open file for writing: " << *o_file << endl;
	    cerr << "skip...\n";
	    continue;
	  }
	fout << ">" << name << "(start=" << (int) startKoord <<", stop=" << stopKoord 
	     << ")" << endl;
	for( int i = 0; i < toFasta.length(); ++i )
	  { 
	    fout << toFasta[ i ];
	    if( i%100 == 0 && i > 0 ) fout << endl;
	  }
      }


      // Create profile
      tree_->clear();

      try{
	tree_->insert( toProfile );
      }
      catch( common::Exception o )
	{
	  throw o;
	}
      tree_->setName( name );
      

      tree_->constrainTree( params_->GetIntParam( "-minc" ) );
      if( params_->GetBoolParam( "-pseudo" ) )
	{
	  tree_->addPseudoCounts();
	}
      //tree_->setProbabilities(); Added this to the insert function where it belongs!!!

      if( params_->GetBoolParam( "-c_c" ) )
	{
	  const double cutoff = params_->GetDoubleParam( "-nc" ); 
	  tree_->prune( cutoff );
	  tree_->draw();
	  return;
	}
      else
	{
	  tree_->prune( params_->GetIntParam( "-npar" ) );
	}

      try {
	tree_->save( ofile2 );
      }
      catch( common::Exception& o )
	{
	  cerr << "In tree: " << o.getText() << endl;
	  cerr << "skip...\n";
	  continue;
	}
      cout << "-->done\n";
    }
}


void Classifier::score()
{ 
  auto_ptr<Fasta> p_fas( new Fasta() );
  
  p_fas->setFastaFile( params_->GetStringParam( "-seq" ) );
  string s, n;

  int numSamp = params_->GetIntParam( "-nsamp" );
  if( numSamp < 0 ) 
    {
      while( p_fas->getNext( n, s ) )
	{
	  //cout << s.length() << endl;
	  score( s, n );
	  s = ""; //n = "";
	}
    }
  else 
    {
      int seed = params_->GetIntParam( "-s" );
      int length = params_->GetIntParam( "-l" );
      if( seed > 0  ) p_fas->setSeed( seed );
      double prevStart = -1;
      for( int i = 0; i < numSamp; ++i )
	{
	  string s = p_fas->getSequenceFromRandomIntervall( length, prevStart );
	  cout << "Processing: " << (int) prevStart << " ";
	  score( s );
	}
    }
}


void Classifier::simulate()
{
  string filename = params_->GetStringParam( "-f" );
  try {
    tree_->load( filename );
  }
  catch( common::Exception& o )
    {
      cout << o.getText() << endl;
      return;
    }	  


  cout << ">" << filename << endl;
  tree_->printRandomSequence( params_->GetIntParam( "-l" ) );
  cout << endl;
}

void Classifier::initRandom()
{
  random_ = RandomSingleton::instance();
  static bool first = true;
  if( first )
    {
      int seed = params_->GetIntParam( "-s" );
      if( seed > 0  ) 
	{
	  random_->randomize( seed );
	}
      else random_->randomize();
      first = false;
    }
}

void Classifier::lrt()
{
  // Initialize pseudo-random object
  initRandom();

  vector<string> infiles = fileHandler_->getInputFileNames();
  string filename = params_->GetStringParam( "-seq" );
  auto_ptr<Fasta> myFasta2( new Fasta() );
  myFasta2->setFastaFile( filename );
  string seq, name;
  myFasta2->getNext( name, seq );
  
  for( vector<string>::iterator i_file = infiles.begin(); 
       i_file != infiles.end(); 
       ++i_file )
    {
      cerr << "-->THIS OPTION IS NOT IMPLEMENTED!!!: " << *i_file << endl;
      auto_ptr<Fasta> myFasta( new Fasta() );
      myFasta->setFastaFile( *i_file ); 
      double dummy;
      for( int i = 0; i < params_->GetIntParam( "-nsamp" ); ++i )
	{
	  string s = myFasta->getSequenceFromRandomIntervall( params_->GetIntParam( "-l" ), dummy ); 
	  // Create profile
	  tree_->clear();
	  
	  try{
	    tree_->insert( s );
	  }
	  catch( common::Exception o )
	    {
	      throw o;
	    }
	  
	  tree_->constrainTree( params_->GetIntParam( "-minc" ) );
	  if( params_->GetBoolParam( "-pseudo" ) )
	    {
	      tree_->addPseudoCounts();
	    }
	  // tree_->setProbabilities(); // Added this to the insert function where it belongs!!!
	  tree_->prune( params_->GetIntParam( "-npar" ) );
	  
	  cout << ">\n" << s << endl; //seq << " " << tree_->getNLL( seq ) << endl;
	}
      
      
    }
}




double Classifier::getNLL()
{
  auto_ptr<Fasta> p_fas( new Fasta() );
  p_fas->setFastaFile( params_->GetStringParam( "-seq" ) );
  string s, n;
  p_fas->getNext( n, s );
  return tree_->getNLL( s );
}



void Classifier::print() const
{
  string filename = params_->GetStringParam( "-f" );
  try {
    tree_->load( filename );
  }
  catch( common::Exception& o )
    {
      cout << o.getText() << endl;
      return;
    }	  
  tree_->draw();
}



void Classifier::score( const string& s, const string& n )
{
  vector<string> infiles = fileHandler_->getInputFileNames();
  vector<string> filenames = fileHandler_->getFileNames();
  vector<string>::iterator i_name = filenames.begin();
  //  vector<string>  extras;

  vector<double> nll;
  if( params_->GetBoolParam( "-revcomp" ) && trees::Node::getAlphabetName() == "DNA" )
    {
      string s_rc =  Util::reverseComplement( s );
      vector<double> nll_ff, nll_rf;
      for( vector<string>::iterator i_file = infiles.begin(); i_file != infiles.end(); ++i_file )
	{
	  try {
	    tree_->load( *i_file );
	  }
	  catch( common::Exception& o )
	    {
	      cout << o.getText() << endl;
	      continue;
	    }	  
	  
	  nll_ff.push_back( tree_->getNLL( s ) );
	  nll_rf.push_back( tree_->getNLL( s_rc ) );
	  tree_->clear(); // Obmitting this line may cause a memory-leak!!
	}
      
      for( int i = 0; i < nll_ff.size(); ++i )
	{
	  double nll_1 = 0, nll_2 = 0;
	  // Assume DNA is at forward string, then nll_ff will be its correct
	  // likelihood
	  nll_1 = nll_ff[ i ];
	  // Assume DNA is not in correct dir, then if we revComp it, then the
	  // correct likelihood will be nll_rf ..
	  nll_2 = nll_rf[ i ];
	  if( nll_1 < nll_2 ) nll.push_back( nll_1 );
	  else                nll.push_back( nll_2 );
	}
    }
  else
    {
      for( vector<string>::iterator i_file = infiles.begin(); i_file != infiles.end(); ++i_file )
	{
	  try {
	    tree_->load( *i_file );
	  }
	  catch( common::Exception& o )
	    {
	      cout << o.getText() << endl;
	      continue;
	    }
	  nll.push_back( tree_->getNLL( s ) );
	  tree_->clear(); // Obmitting this line will cause a memory-leak!!
	}
    }

  if( nll.size() == 0 ) return;
  
  double min = *min_element( nll.begin(), nll.end() );

  cout << "Query = ";
  if( n > "" ) cout << n << "\n";
  for( int i = 0; i < nll.size(); ++i )
    {
      if( nll[i] == min ) 
      	{
	  cout << "Hit: " << filenames[ i ] << " " << nll[ i ] << "\n";
	}
      //else cout << filenames[i] << " " << nll[i] << endl;
    } 
  cout << "-----------------------------------------\n";
}


void Classifier::modelTesting()
{
  vector<string> infiles = fileHandler_->getInputFileNames();
  vector<string> files = fileHandler_->getFileNames();
  vector<string>::iterator i_name = files.begin();
  
  for( vector<string>::iterator i_file = infiles.begin(); i_file != infiles.end(); ++i_file, ++i_name )
    {
      auto_ptr<Fasta> myFasta( new Fasta() );
      myFasta->setFastaFile( *i_file );  
      string name, seq;
      if( !myFasta->getNext( name, seq ) )
	{
	  cerr << "Fasta error!\n";
	  return;
	}
      cout << "Name of file: " << *i_file << endl;
      for( int i = params_->GetIntParam( "-min" ); i < params_->GetIntParam( "-max" ); i += params_->GetIntParam( "-sl" ) )
	{
	  // Create profile
	  tree_->clear();
	  
	  try{
	    tree_->insert( seq );
	  }
	  catch( common::Exception o )
	    {
	      throw o;
	    }
	  tree_->setName( name );
	  
	  tree_->constrainTree( params_->GetIntParam( "-minc" ) );
	  if( params_->GetBoolParam( "-pseudo" ) )
	    {
	      tree_->addPseudoCounts();
	    }

	  // tree_->setProbabilities(); // Added this to the insert function where it belongs!!!
	  tree_->prune( i  );
	  
	  
	  cout << i << " " << tree_->getAIC() << " " << tree_->getBIC() << " " << endl;
	}
    }
}


/* 
 * Used for scanning a genome for HGT
 */
void Classifier::scan() 
{
  auto_ptr<Fasta> p_fas( new Fasta() );
  
  p_fas->setFastaFile( params_->GetStringParam( "-seq" ) );
  string s, n;
  p_fas->getNext( n, s );
  
  int win = params_->GetIntParam( "-win" );
  int step =  params_->GetIntParam( "-slen" );

  for( int i = 0; i < s.size(); i += step )
    {
      if( i + win > s.size() ) break;
      string tmp_str = s.substr( i, win );
      string tmp_clm = s.substr( 0, i );
      tmp_clm += s.substr( i+win, s.size() - i - win + 1 );
      
      tree_->clear();


      try{
	tree_->insert( tmp_clm );
      }
      catch( common::Exception o )
	{
	  throw o;
	}
      tree_->constrainTree( params_->GetIntParam( "-minc" ) );
      if( params_->GetBoolParam( "-pseudo" ) )
	{
	  tree_->addPseudoCounts();
	}

      // tree_->setProbabilities(); // Added this to the insert function where it belongs!!!
      tree_->prune( params_->GetIntParam( "-npar" ) );
      double nll1 = tree_->getNLL( tmp_str );
      double nll2 = tree_->getNLL( Util::reverseComplement( tmp_str ) );
      double nll = nll1 > nll2 ? nll1 : nll2 ;
      cout << i << " " <<  nll << endl;
    } 
}
