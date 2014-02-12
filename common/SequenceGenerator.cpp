// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "SequenceGenerator.h"

using namespace std;

const Alphabet* SequenceGenerator::alphabet = NULL;

 
SequenceGenerator::SequenceGenerator( const Alphabet* alp, const int& seed )
{
  auto_ptr<RandomSingleton> tmp( RandomSingleton::instance() );
  prand_ = tmp;
  if( seed > 0 ) prand_->randomize( seed );
  else prand_->randomize();
  base_ = -1;
  gc_ = 0.5;

  setAlphabet( alp );
}


void SequenceGenerator::test()
{
  const int NUM = 10000;

//   SequenceGenerator rGen;
//   rGen.setGC( 0.5 );
//   rGen.setBase( 2 );
//   rGen.setRandomTransitions();
//   rGen.printFasta( NUM ); 
}


// Will set GC content according to a normal distribution
void SequenceGenerator::setGCnormal( const double& mean, const double& std )
{
  gc_ = -1;
  while( gc_ < 0 || gc_ >= 1 )
    {
      gc_ = prand_->gauss1d( std,  mean );
    }
}



string SequenceGenerator::getSequence( const int& NUM, const double& p_pollute )
{
  assert( base_ >= 0 ); 
  if( base_ == 1 ) return completelyRandom( NUM );
  
  string sequence( "" );

  list<char> seq;
  for( int i = 0; i < NUM; ++i )
    {
      double x = prand_->flat();  
      double pA, pC, pG, pT;
      char c;
      string pat;
      if( i < base_ ) 
	{
	  pC = pG = gc_ / 2;
	  pA = pT = ( 1 - gc_ ) / 2;
	}
      else
	{
	  list<char>::const_iterator i_list;
	  for( i_list = seq.begin(); i_list != seq.end(); ++i_list ) pat += *i_list;
	  pA = trans_[ pat + "A" ];
	  pC = trans_[ pat + "C" ];
	  pG = trans_[ pat + "G" ];
	  pT = trans_[ pat + "T" ];
	}

      if( p_pollute > 0 )
	{
	  double y = prand_->flat();
	  if( y < p_pollute )
	    {
	      pA = pC = pG = pT = 0.25;
	    }
	}
      if( x < pA )                c = 'A'; 
      else if( x < pA + pC )      c = 'C';
      else if( x < pA + pC + pG ) c = 'G';
      else                        c = 'T';
    
      
      seq.push_back( c );
      if( seq.size() >= base_ ) seq.pop_front();
      sequence += c;
    }
  return sequence;
}


string SequenceGenerator::getMixture( const int& NUM, const int& sbase, 
				      const double& pLowerModel, const double& p_pollute )
{
  assert( base_ > 0 && sbase > 0 ); 
  assert( sbase < base_ );
  if( base_ == 1 ) return completelyRandom( NUM );
  setSubsetTransition( sbase );


  string sequence( "" );

  list<char> seq;

  for( int i = 0; i < NUM; ++i )
    {
      double x = prand_->flat();  
      double pA, pC, pG, pT;
      char c;
      string pat;
      if( i < base_ ) 
	{
	  pC = pG = gc_ / 2;
	  pA = pT = ( 1 - gc_ ) / 2;
	}
      else
	{
	  list<char>::const_iterator i_list;
	  for( i_list = seq.begin(); i_list != seq.end(); ++i_list ) pat += *i_list;
	  if( prand_->flat() < pLowerModel )
 	    {
 	      string spat = pat.substr( base_ - sbase_, sbase_ - 1);
	      // cout << pat << " " << spat << endl;
	      pA = strans_[ spat + "A" ];
	      pC = strans_[ spat + "C" ];
	      pG = strans_[ spat + "G" ];
	      pT = strans_[ spat + "T" ];	
 	    }
	  else
 	    {
	      pA = trans_[ pat + "A" ];
	      pC = trans_[ pat + "C" ];
	      pG = trans_[ pat + "G" ];
	      pT = trans_[ pat + "T" ];	      
	    }
	}

      if( p_pollute > 0 )
	{
	  double y = prand_->flat();
	  if( y < p_pollute )
	    {
	      pA = pC = pG = pT = 0.25;
	    }
	}
      if( x < pA )                c = 'A'; 
      else if( x < pA + pC )      c = 'C';
      else if( x < pA + pC + pG ) c = 'G';
      else                        c = 'T';
    
      
      seq.push_back( c );
      if( seq.size() >= base_ ) seq.pop_front();
      sequence += c;
    }
  return sequence;
}


void SequenceGenerator::printFasta( const int& NUM )
{
  assert( base_ >= 0 ); 
  cout << ">Random sequence from Markov M" << base_-1 << " of size " << NUM << endl;

  list<char> seq;
  for( int i = 0; i < NUM; ++i )
    {
      double x = prand_->flat();  
      double pA, pC, pG, pT;
      char c;
      string pat;
      if( i < base_ ) 
	{
	  pC = pG = gc_ / 2;
	  pA = pT = ( 1 - gc_ ) / 2;
	}
      else
	{
	  list<char>::const_iterator i_list;
	  for( i_list = seq.begin(); i_list != seq.end(); ++i_list ) pat += *i_list;
	  pA = trans_[ pat + "A" ];
	  pC = trans_[ pat + "C" ];
	  pG = trans_[ pat + "G" ];
	  pT = trans_[ pat + "T" ];
	}

      
      if( x < pA )                c = 'A'; 
      else if( x < pA + pC )      c = 'C';
      else if( x < pA + pC + pG ) c = 'G';
      else                        c = 'T';
    
      
      seq.push_back( c );
      if( seq.size() >= base_ ) seq.pop_front();
      cout << c;
      if( i%100 == 0 && i > 0 ) cout << endl;
    }
  cout << endl;
}


void SequenceGenerator::setRandomTransitions( const bool& newseed )
{
  assert( base_ >= 0 ); 
  int N = (int) pow( (double) alphabet->size(), (double) base_ );
  vector<double> prob;
  
  if( newseed )
    {
      prand_->randomize();
    }


  for( size_t j = 0; j < N; j += alphabet->size() )
    {
      double p1 = prand_->flat();
      double p2 = prand_->flat();
      double p3 = prand_->flat();
      double p4 = prand_->flat();
      double tot = p1 + p2 + p3 + p4;
      p1 /= tot; // A
      p2 /= tot; // C
      p3 /= tot; // G   
      p4 /= tot; // T
      
      // GC 
      double gc_factor = gc_/(p2+p3);
      p2 *= gc_factor;
      p3 *= gc_factor;
      
      // AT
      double at_factor = ( 1 - gc_ )/( p1 + p4 );
      p1 = p1*at_factor;
      p4 = p4*at_factor;

      prob.push_back( p1 );      
      prob.push_back( p2 );
      prob.push_back( p3 );      
      prob.push_back( p4 );
    }

  map<string, double> trans;
  string tmp = "";
  int counter = 0;
  setEmpty( trans, base_, prob, tmp, counter );    
  trans_ = trans;
}


/*
 * Given a vector of probabilities the transition matrix will be assigned values.
 */
void SequenceGenerator::setTransitions( const vector<double>& prob )
{
  assert( base_ >= 0 ); 
  int N = (int) pow( (double) alphabet->size(), (double) base_ );
  assert( prob.size() == N );
  map<string, double> trans;
  string tmp = "";
  int counter = 0;
  setEmpty( trans, base_, prob, tmp, counter );    

  trans_ = trans;
}




void SequenceGenerator::setEmpty( map<string, double>& mymap, const int& base_, const vector<double>& values, string tmp_str, int& counter )
{
  string myAlp = alphabet->toString();
  if( tmp_str.size() == base_-1 ) 
    {
      for( size_t i = 0; counter < values.size() && i < myAlp.size() ; ++counter, ++i )
	{
	  string tmp = tmp_str;
	  tmp +=  myAlp[i];
	  mymap[ tmp ] = values[ counter ]; 
	}
    }
  else
    {
      for( size_t i = 0; i < alphabet->size() ; ++i )
	{
	  string tmp = tmp_str;
	  tmp += myAlp[i];
	  setEmpty( mymap, base_, values, tmp, counter ); 
	}
    } 
}



void SequenceGenerator::setSubsetTransition( const int& sbase )
{
  assert( sbase < base_ );
  sbase_ = sbase;
  vector<double> prob( (int) pow(4.0, (double) sbase_ ), 0 );
  string tmp;
  int counter = 0;
  setEmpty( strans_, sbase, prob, tmp, counter );  
  for( map<string, double>::iterator i = strans_.begin(); i  != strans_.end(); ++i )
    {
      double p = 0;
      for( map<string, double>::iterator j = trans_.begin(); j  != trans_.end(); ++j )
	{
	  if( j->first.substr( base_ - sbase, sbase ) == i->first )
	    {
	      p += j->second;
	    }
	}
      i->second = p/4;
    }
} 


string SequenceGenerator::completelyRandom( const int& num_data )
{
  double pA, pC, pG, pT;
  pA = pT = ( 1 - gc_ ) / 2;
  pC = pG = gc_ / 2;

  string seq;
  for( int i = 0; i < num_data; ++i )
    {
      double x = prand_->flat();
      char c;
      if( x < pA )                c = 'A';
      else if( x < pA + pC )      c = 'C';
      else if( x < pA + pC + pG ) c = 'G';
      else                        c = 'T';
      seq += c;
    }
  return seq;
}
