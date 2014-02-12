// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include <Util.h>
#include <Exception.h>
#include <RandomSingleton.h>

#include "Tree.h"
#include "FixedTree.h"
#include "PstTree.h"
#include "Node.h"
#include "PSModifier.h"
#include "KLModifier.h"

using namespace std;
using namespace trees;

// Statics 
int Tree::DEPTH = -1;
const string Tree::BADALPHABET = "The symbols of the model are not in accordance with the specified alphabet\nPlease check the integrity of file or the settings. Bad symbol.";


Tree::Tree()
{
  // The total number of nodes should not belong to Node-class 
  // but to Tree class. This to avoid confusion of the static 
  // nature when having more trees. CHANGE THIS!!!
  sReset();
}

/*
 * Constructors and destructors
 */
Tree::Tree( const Alphabet* alp, const int& wl )  
{
  Node::setAlphabet( alp );
  head_ = new Node();
  maxWordLength_ = wl;
  totalTotal_ = 0;
  treeMod_ = NULL;
}




Tree::~Tree()
{
  this->cleanUp( head_ );  
  if( treeMod_ != NULL )
    {
      delete treeMod_;
    }
  treeMod_ = NULL;
}

void Tree::clear()
{
  this->cleanUp( head_ );
  sReset();
  head_ = new Node();
  total_ = 0;
  totalTotal_ = 0;
  firstCall_ = true;
  name_ = "";
  DEPTH = 0;
}


void Tree::sReset()
{
  Node::sReset();
}


void Tree::addPseudoCounts()
{
  addPseudoCounts( head_ );
}


void Tree::addPseudoCounts( Node* pNode )
{
  for( int i = 0; i < Node::getAlphabetSize(); ++i ) 
    {
      if( pNode->getNextSymbCount( i ) == 0 ) 
	{
	  for( int i = 0; i < Node::getAlphabetSize(); ++i ) 
	    {
	      pNode->setNextSymbolCount( i, pNode->getNextSymbCount( i ) + 1 ); 
	    }
	}
    }
  for( int i = 0; i < Node::getAlphabetSize(); ++i ) 
    {
      Node* next = pNode->getNode(i);
      if( next != NULL )
	{
	  addPseudoCounts( next );
	}
    }
}


int Tree::depth()
{
  if( !isModified() ) return DEPTH;
  int max = 0;
  depth( head_, 0, max ); 
  DEPTH = max;
  return max;
}


void Tree::setTreeModifier( TreeModifier* tm )
 {
  if( treeMod_ != NULL )
    {
      delete treeMod_;
    }
   tm->setHead( head_ ); 
   treeMod_ = tm; 
}


void Tree::depth( Node* pNode, int d, int& max )
{
  if( d > max ) max = d;
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* next = pNode->getNode( i );
      if( next == NULL ) continue;
      else
	{
	  depth( next, d+1, max );
	}
    }
}


double Tree::getTotalTotal()
{
  if( totalTotal_ > 0 ) return totalTotal_;
  double res = 0;
  this->totalTotal( head_, res );
  return res;
}

void Tree::totalTotal( Node* pNode, double& res )
{
  res += pNode->getTotalC();
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* next = pNode->getNode(i);
      if( next != NULL ) this->totalTotal( next, res );
    }
}


void Tree::removeZeroes()
{
  if( head_->getTotalC() == 0 )
    {
      cerr << "Warning: Must run setNextSymbolProb() before removeZeroes()\n";
      return;
    }
  removeZeroes( head_ );
}

void Tree::removeZeroes( Node* pNode )
{
  if( pNode->getTotalC() == 0 )
    {
      cleanUp( pNode );
    }
  else
    {
      for( int i = 0; i < Node::getAlphabetSize(); ++i )
	{
	  Node* next = pNode->getNode(i);
	  if( next != NULL )
	    {
	      if( next->getTotalC() == 0 )
		{
		  cleanUp( next );
		  pNode->setNode( NULL, i );
		}
	      else
		{
		  removeZeroes( next );
		}
	    }
	}
    }  
}


// void Tree::insertWord( const string& word )//, const bool& rev )
// {
//   modified();
//   const char& curLetter = word[ 0 ];  
//     //  cout << "increasing head counter: " << word[0] <<  endl;
//   if( word.size() == 1 ) {
//     head_->increaseP( curLetter );
//     //cout << curLetter << endl; head_->print();
//   }
  

//   Node* curNode = head_->getNode( curLetter );
//   if( curNode == NULL )
//     {
//       curNode = new Node( word.substr( 0, 1 ) );
//       head_->setNode( curNode, curLetter );
//     }
//   this->insertWord( curNode, word, 1 );//, rev ); 
// }


void Tree::insertWord( const string& word )//, const bool& rev )
{
  modified();
  string s = "";
  insertWord( head_, word, s );
  //  cout << "TESTING: " << word << " " << s << endl;
}


void Tree::insertWord( Node* pNode, const string& word, string& s )
{
  const char& curLetter = word[ 0 ];
  pNode->increaseP( curLetter );
  s = word[0] + s;

  Node* curNode = pNode->getNode( curLetter );
  if( curNode == NULL )
    {
      curNode = new Node( s );
      pNode->setNode( curNode, curLetter );
    }
  if( word.size() == 1 ) 
    {
      return; 
    }
  else
    {
      this->insertWord( curNode, word.substr( 1, word.size() - 1 ), s );
    }
}


// void Tree::insertWord( Node* pNode, const string& word, int deep )//, const bool& rev )
// {   
//   if( word.size() == deep ) 
//     {
//       return; 
//     }
  
//   const char& curLetter = word[ deep ];

//   if( word.size() == deep+1 ) 
//     {      
//       pNode->increaseP( curLetter );
//       if( dynamic_cast<FixedTree*>( this ) != NULL )
// 	{
// 	  return;
// 	}
//     }
//   Node* curNode = pNode->getNode( curLetter );
//   if( curNode == NULL )
//     {
//       string tmp = word.substr( 0, deep + 1 );
//       reverse( tmp.begin(), tmp.end() );
//       curNode = new Node( tmp );
//       pNode->setNode( curNode, curLetter );
//     }
//    else
//      {
//      }
//   this->insertWord( curNode, word, ++deep );//, rev ); 
// }


/*
 * Protected functions (A-Z)
 */
void Tree::cleanUp( Node* pNode )
{
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
     if( pNode->getNode( i ) != NULL )
       {
	cleanUp( pNode->getNode( i ) );
       }
    }
  delete pNode; // No more nodes further down!
}





double Tree::getSuffixCount( const string& pat ) const
{
  //  cout << "PAT = " << pat << endl;
  if( pat.size() <= 1 ) 
    { 
      double sum = 0;
      for( int i = 0; i < Node::getAlphabetSize(); ++i ) sum += head_->getC( i ); 
      return sum;
    }
  // Skip first nucleotide and get all that ends in pat
  double totalCount = 0;
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* pNode = head_->getNode( i );
      if( pNode == NULL ) continue;

      string::const_reverse_iterator i_pat = pat.rbegin();
      ++i_pat; // Skip first nuc since does not belong to prefix
      
      Node* node = pNode;
      string tmp_pat = node->getString();

      for( ; i_pat+1  != pat.rend(); ++i_pat )
	{
	  node = node ->getNode( *i_pat );
	  tmp_pat += *i_pat;
	  if( node == NULL ) break;
	}
      if( node != NULL ) 
	{
	  totalCount += node->getC( *i_pat, true );
	  //	  cout << tmp_pat + *i_pat << " " <<  node->getC( *i_pat, true ) << endl;
	}
    }
  //  cout << "Total count = " << totalCount << endl;
  return totalCount;
 }


double Tree::getCount( const string& pat ) const
{
  if( pat.size() == 0 ) { return head_->getTotalC(); }
  if( pat.size() == 1 ) 
    {
      return head_->getC( pat[0], true ); 
    }


  string::const_reverse_iterator i_pat = pat.rbegin();
  Node* node = head_;
  for( ; i_pat + 1  != pat.rend(); ++i_pat )
    {
      node = node->getNode( *i_pat );
      if( node == NULL ) break;
    }
  if( node != NULL ) 
    {
      return node->getC( *i_pat, true );
    }
  else return 0.0;
 }


void Tree::setProbabilities() 
{
  setProbabilities( head_ );
}

void Tree::setProbabilities( Node* pNode ) 
{
  string s = pNode->getString();
  if( s == "#" ) s = "";
  
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      string s_pat = s + Node::getAlphabetChar( i );
      double s_nom = getSuffixCount( s_pat );      
      double s_denom = getCount( s_pat );
      
      if( s_nom != 0 ) 
      	{
	  pNode->setNextSymbolProb( i, s_denom / s_nom );
	  pNode->setNextSymbolCount( i, s_denom );
	}
    }
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( pNode->getNode( i ) != NULL )
	{
	  this->setProbabilities( pNode->getNode( i ) );
	}
    }  
}


void Tree::adjustNextSymbolCount( Node* pNode )
{
  if( pNode->isAdjusted() ) return;
  bool isAdjusted = false;
  bool adj = true;
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i ); 
      if( node != NULL )
	{
	  double count = 0;
	  for( int j = 0; j < Node::getAlphabetSize(); ++j )
	    {
	      double p = pNode->getNextSymbCount( j ) - node->getNextSymbCount( j );
	      count += p;
	      pNode->setNextSymbolCount( j, p );
	    }
	  for( int j = 0; j < Node::getAlphabetSize(); ++j )
	    {
	      pNode->setNextSymbolProb( j, pNode->getNextSymbCount( j ) / count );
	    }
	  //	  pNode->setTotal( count );
	}
    }
  
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* node = pNode->getNode( i ); 
      if( node != NULL )
	{
	  this->adjustNextSymbolCount( node );
	}
    }
//   for( int i = 0; i < Node::getAlphabetSize(); ++i )
//     {
//       head_->setNextSymbolCount( i, 0 );
//     }
}


void Tree::print() const 
{
  if( head_ != NULL ) print( head_ );
}


bool Tree::isM0() const
{
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( head_->getNode( i ) != NULL )
	{
	  if( head_->getNode( i )->getTotalC() > 0 )
	    {
	      return false;
	    }
	}
    }  
  return true;
}

double Tree::prob( const string& pat )
{
  if( !Node::integrity( pat ) ) return 0;
  Node* pNode = head_;
  string::const_reverse_iterator irev = pat.rbegin();
  char lastSymbol = *irev;
  ++irev;
  for( ; irev != pat.rend(); ++irev )
    {
      Node* next = pNode->getNode( *irev );
      if( next == NULL ) break;
      pNode = next;
    }
  return pNode->getNextSymbProb( lastSymbol, true );
}


void Tree::removeTerminalNodes()
{
  removeTerminalNodes( head_ );
}

void Tree::removeTerminalNodes( Node* pNode )
{
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( pNode->getNode( i ) != NULL )
	{
	  if( pNode->getNode( i )->isLeaf() )
	    {
	      cleanUp( pNode->getNode( i ) );
	      pNode->setNode( NULL, i );
	    }
	  else
	    {
	      removeTerminalNodes( pNode->getNode( i ) );
	    }
	}
    }
}



void Tree::prune( const double& cutoff ) 
{
  DEPTH = -1; // Tree modified

  // Call tree-modifier
  if( treeMod_ != NULL )
    {
      this->setHeadForTM( treeMod_ ); // This line was added to fix an error, KEEP
      treeMod_->prune( cutoff );
    }

  // Counts must be adjusted
  if( useAdj_ ) adjustNextSymbolCount( head_ );
  //setProbabilities();
}


void Tree::prune( const int& num )
{
  DEPTH = -1; // Tree modified

  // Call tree-modifier
  if( treeMod_ != NULL )
    {
      this->setHeadForTM( treeMod_ ); // This line was added to fix an error, KEEP
      treeMod_->prune( num );
    }

  // Counts must be adjusted
  if( useAdj_ ) adjustNextSymbolCount( head_ );
}


void Tree::adjustNextSymbolCount()
{
  useAdj_ = true;
  adjustNextSymbolCount( head_ );
}


void Tree::print( Node* pNode ) const 
{
  pNode->print();

  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( pNode->getNode( i ) != NULL )
	{
	  this->print( pNode->getNode( i ) );
	}
    }
}


void Tree::load( const string& filename )
{
  modified();
  ifstream fin( filename.c_str() );
  if( !fin )
    {
      throw common::Exception( "Cannot open file: " + filename, common::Exception::WARNING );
    }
  char buffer[1000];

  vector<Node*> nodeList;
  vector<int> relations;


  int lineNumber = 0;
  while( fin.getline( buffer, 1000 ) )
    {
      ++lineNumber;
      string line = buffer;
      StringTokenizer sTok( line, " " );
      string col = sTok.nextToken();
      if( lineNumber == 1 )
	{
	  if( col != "Name:" )
	    {
	      throw common::Exception( "Does not look like a tree-file: " + filename
				 + ", first tag should be Name: ", common::Exception::ERROR );
	    }
	}
      if( col == "Name:" || col == "Date:" ) continue; 
      if( col == "Alphabet:" ) // NOT NECESSARY SINCE DEFINE IN CONSTRUCTOR
 	{
	  this->checkNumberTokens( sTok, 1, col, lineNumber );
	  continue;
	  // 	  Alphabet* pA = new Alphabet();
	  // 	  pA->setAlphabet( sTok.nextToken() );
	  // 	  Node::setAlphabet( pA );
 	}
      if( col == "Tree:" ) 
	{
	  this->checkNumberTokens( sTok, 1, col, lineNumber );
	  continue;
	}
       if( col == "Number(nodes):" )
	 {
	   this->checkNumberTokens( sTok, 1, col, lineNumber );
	   Node::setNumberNodes( 0 );//sTok.nextIntToken() );
	   continue;
	 }
       if( col == "Number(parameters):" )
	 {
	   this->checkNumberTokens( sTok, 1, col, lineNumber );
	   int np = sTok.nextIntToken();
	   Node::setNumberParameters( 0 );
	   continue;
	 }
       if( col == "Node:" ) 
	 {
	   int n = Node::getAlphabetSize();
	   	  
	   int numberOfTokens = 3*n + 8;
	   this->checkNumberTokens( sTok, numberOfTokens, col, lineNumber );
	   
	   // Read identity of node
	   int id = sTok.nextIntToken();
	   
	   // Read nuc-pattern of node
	   string s = sTok.nextToken();

	   // [
	   sTok.nextToken();

	   // Read counts of node-children
	   vector<double> counts;
	   for( int i = 0; i < n; ++i )
	     {
	       double c = sTok.nextFloatToken();
	       counts.push_back( c );
	     }

	   // ]
	   sTok.nextToken();

	   // Read total counts of node-children
	   double total = sTok.nextFloatToken();
	   
	   // [
	   sTok.nextToken();

	   // Read nextSymbolCount
	   vector<double> nextS;
	   for( int i = 0; i < n; ++i )
	     {
	       double c = sTok.nextFloatToken();
	       //cout << c << " ";
	       nextS.push_back( c );
	     }
	   
	   // ][
	   sTok.nextToken();

	   
	   // Save relations for building tree
	   for( int i = 0; i < n; ++i )
	     {
	       int c = sTok.nextIntToken();
	       relations.push_back( c );
	     }
	  
	   // ]
	   sTok.nextToken();

 
	   // Create new node and save for building tree
	   Node* node = new Node( s );
	   node->setId( id );
	   node->setCounts( counts );
	   node->setNextSymbolCount( nextS );
	   //node->setTotal( total );
	   node->calculateProbabilities();
	   nodeList.push_back( node );
	 }
    }

  // Build tree
  head_ = nodeList[0];
  int relIndex = 0;
  if( *max_element( relations.begin(), relations.end() ) > 0 && nodeList.size()-1 != *max_element( relations.begin(), relations.end() ) ) 
    {
      cerr << "\nError in: " << filename << endl << endl
	   << "There seem to be connections to nodes that does not exist, or\n"
	   << "nodes without connections. In either case you need to check the\n"
	   << "integrity of the inputfile. The last columns in the square brackets\n"
	   << "should be assigned -1 if not connected to any nodes!\n\n"
	   << "Beyond repair! Terminates ...\n\n";
      exit( 1 );
    }
  if( Node::getNumberNodes() != nodeList.size() )
    {
      cerr << "\nError in: " << filename << endl << endl     
	   << "There are differently many nodes specified: "<< Node::getNumberNodes()<< endl
	   << "Those listed count to: " << nodeList.size() << "\n\n"
	   << "Beyond repair! Terminates ...\n\n";
    }

  for( vector<Node*>::iterator inode = nodeList.begin(); inode != nodeList.end(); ++inode )
    {
      for( int i = 0; i < Node::getAlphabetSize(); ++i )
	{
	  int id = relations[ relIndex++ ];
	  if( id != -1 )
	    {
	      for( vector<Node*>::iterator jnode = nodeList.begin(); jnode != nodeList.end(); ++jnode )
		{
		  if( id == (*jnode)->getId() )
		    {
		      (*inode)->setNode( (*jnode), i );
		      break;
		    }
		}
	    }
	}
      (*inode)->checkIfLeaf();
    }
}


void Tree::checkNumberTokens( StringTokenizer& str, const int& n,
			      const string& tag, const int& ln )
{
  if( n != str.countTokens() ) 
    {
      cerr << "The input-file seems corrupt for the " << Node::getAlphabetName() << " alphabet, line: " << ln << endl << tag << " ";
      cerr << "Line has " << str.countTokens()+1 << " space separated words, should have: " << n + 1 << endl;
      while( str.hasMoreTokens() )cout << str.nextToken() << " ";
      cout << endl;
      exit( 2 ); // THROW EXCEPTION!!
    }
}

void Tree::save( const string& filename )
{
  // Open file
  ofstream fout( filename.c_str() );
  if( !fout )
    {
      throw common::Exception( "cannot open file: " + filename, common::Exception::ERROR );
    }

  int nodeCounter = 0;
  fout << "Name: " << name_ << endl;
  fout << "Date: " << Util::TimeAndDate2String() << endl;
  if( dynamic_cast<FixedTree*>( this ) != NULL ) fout << "Tree: Fixed" << endl;
  if( dynamic_cast<PstTree*>( this ) != NULL ) fout << "Tree: PST" << endl;
  fout << "Alphabet: " << Node::getAlphabetName() << endl;
  fout << "Number(nodes): " << Node::getNumberNodes() << endl;
  fout << "Number(parameters): " << Node::getNumberParameters() << endl;

  int nodeId = 0;
  setNodeId( head_, nodeId );
  save( head_, fout );
}


void Tree::save( Node* pNode, ofstream& fout )
{
  if( pNode->getId() != 0 )
    {
      fout << "Node: " << pNode->getId() << " " << pNode->getString() << " " << pNode->toString();
    }
  else
    {
      fout << "Node: " << pNode->getId() << " # " << pNode->toString();
    }
  fout << "[ ";
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( pNode->getNode( i ) != NULL )
	{
	  fout << pNode->getNode( i )->getId() << " ";
	}
      else
	{
	  fout << -1 << " ";
	}
    }
  fout << " ]" << endl;
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( pNode->getNode( i ) != NULL )
	{
	  this->save( pNode->getNode( i ), fout );
	}
    }
}


void Tree::setNodeId( Node* pNode, int& nodeId )
{
  pNode->setId( nodeId++ );
  
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( pNode->getNode( i ) != NULL )
	{
	  setNodeId( pNode->getNode( i ), nodeId );
	}
    }
}


string Tree::getRandomSequence( const int& l, const int& seed )
{
  
  string res = ""; 
  RandomSingleton* pRand = RandomSingleton::instance();
  if( firstCall_ )
    {
      if( seed == 0 )
	{
	  pRand->randomize();
	}
      else if( seed > 0 ) 
	{
	  pRand->randomize( seed );
	}
      firstCall_ = false;
    }

  if( isM0() ) 
    {
      vector<double> p;
      double tot = getCount( "" );
      for( int i = 0; i < Node::getAlphabetSize(); ++i )
	{
	  string s = "";
	  s += Node::getAlphabetChar( i );
	  p.push_back( prob( s ) );//(double) getCount( s ) / tot );
	  //cout << s << " " << prob( s ) << endl;
	}
      for( int i = 0; i < l; ++i )
	{
	  double rnd = pRand->flat();
	  double p_acc = 0;
	  for( int j = 0; j < Node::getAlphabetSize(); ++j )
	    {
	      p_acc += p[j];
	      if( rnd <  p_acc )   
		{ 
		  res += Node::getAlphabetChar( j );
		  break;
		}
	    }
	}
      return res;
    }
  else
    {
      vector<double> p( Node::getAlphabetSize(), static_cast<double>(0.0) ) ;
      for( int i = 0; i < l; ++i )
	{
	  for( int j = 0; j < Node::getAlphabetSize(); ++j )
	    {
	      string tmp = res;
	      //if( tmp.size() > 15 ) tmp = tmp.substr( tmp.size()-15, 15 );
	      //cout << Node::getAlphabetChar( j ) << " " << endl;
	      //draw();
	      tmp += Node::getAlphabetChar( j );
	      p[j] = prob( tmp );
	      //	      if( tmp.size() > 2 ) cout << tmp.substr( tmp.size()-2,2) << ": Sannolikheten ska inte vara noll: " << p[j] << endl;
	    }

	  double rnd = pRand->flat();
	  double p_acc = 0;
	  for( int j = 0; j < Node::getAlphabetSize(); ++j )
	    {
	      p_acc += p[j];
	      //	      cout << p_acc << endl;
	      if( rnd <  p_acc )   
		{ 
		  res += Node::getAlphabetChar( j );
		  //		  cout << Node::getAlphabetChar( j ) << " " << res << endl;
		  //	  cout << res << endl;
		  break;
		}
	    }
	}
      return res;
    }
}

void Tree::printRandomSequence( const int& l  ) 
{
  string res = "";
  static bool first = true;
  RandomSingleton* pRand = RandomSingleton::instance();
  if( first )
    {
      pRand->randomize();
    }
  
  for( int i = 0; i < l; ++i )
    {
      double p1 = prob( res + "A" );
      double p2 = prob( res + "C" );
      double p3 = prob( res + "G" );
      double p4 = prob( res + "T" );
      double rnd = pRand->flat();
      if(      rnd <  p1 )              { cout << "A"; res += 'A'; }
      else if( rnd <  p1 + p2 )         { cout << "C"; res += 'C'; }
      else if( rnd <  p1 + p2 + p3 )    { cout << "G"; res += 'G'; }
      else                              { cout << "T"; res += 'T'; }
      if( (i+1)%100 == 0 ) 
	{
	  cout << endl;
	  string tmp = "";
	  if( res.size() == 0 ) continue;
	  for( int i = res.size()-1; i > res.size() - maxWordLength_ - 1 && i > 0; --i )
	    {
	      tmp += res[i];
	    }
	  res = tmp;
	}
    }
}



vector<Node*> Tree::getTerminalNodes() const
{
  vector<Node*> res;
  getTerminalNodes( head_, res );
  return res;
}

void Tree::getTerminalNodes( Node* pNode, vector<Node*>& res ) const
{
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      Node* next = pNode->getNode( i );
      if(  next != NULL )
	{
	  if( next->isLeaf() )
	    {
	      res.push_back( next );
	    }
	  else
	    {
	      getTerminalNodes( next, res );
	    }
	}
    }
}


void Tree::removeScheduled( Node* pNode )
{
  for( int i = 0; i < Node::getAlphabetSize(); ++i )     
    {
      bool hasRemoved = false;
      Node* next = pNode->getNode( i );
      if( next != NULL )
	{
	  if( next->schedulaToBeRemoved() )
	    {
	      cleanUp( next );
	      pNode->setNode( NULL, i );
	      next = NULL;
	      hasRemoved = true;
	    }
	  else
	    {
	      removeScheduled( next );
	    }
	}
      if( hasRemoved )
	{
	  pNode->checkIfLeaf();
	}
    }
}

void Tree::draw() const
{
  draw( head_, "" );
}

void Tree::draw( Node* pNode, string edge ) const 
{
  double c = pNode->getTotalC();


  cout << "[" << pNode->getString() <<"]--(";
  for( int i = 0; i < Node::getAlphabetSize(); ++i )     
    {
      cout << pNode->getNextSymbCount( i ) << " ";
    }

  cout << "| " << c << ") ";
  if( pNode->isLeaf() ) cout << "-T ";
  if( pNode->getTmpData() != 0 ) cout << "<" << pNode->getTmpData() << ">";
  cout << endl;

  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      if( pNode->getNode( i ) != NULL )
	{
	  cout << edge << "+" << "---";
	  draw( pNode->getNode( i ), edge + "     " );
	}
    }
}




double Tree::getAIC( const string& s ) 
{
  if( dynamic_cast<PstTree*>( this ) != NULL )
    {
      if( !useAdj_ ) 
	{
	  cerr << "For AIC option do not use accumulated probs!\n"; 
	  return 0;
	}
    }
  double nll = 0;
  if( s > "" ) nll = getNLL( s );
  else nll = getNLL();
  return 2*nll + 2*Node::getNumberParameters();
}


double Tree::getBIC( const string& s )
{
  double nll = 0;
  if( s > "" ) nll = getNLL( s );
  else nll = getNLL();
  assert( getTotalTotal() > 0 );
  return 2*nll + log( getTotalTotal() )*Node::getNumberParameters();
}



void Tree::getAllPatterns( vector<string>& res, string str, const int& n )
{
  if( str.size() >= n )
    {
      res.push_back( str );
      return;
    }
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      string tmp = str;
      tmp += Node::getAlphabetChar( i );
      getAllPatterns( res, tmp , n );
    }
}




double Tree::getNLL()
{
  double n = 0;  
  getNLL( head_, n );
  return n;
}


void Tree::getNLL( Node* pNode, double& n )
{ 
  for( int i = 0; i < Node::getAlphabetSize(); ++i )
    {
      double p = pNode->getNextSymbProb( i );
      if( p > 0 ) n += pNode->getNextSymbCount( i )*(-log( p ));
      Node* node = pNode->getNode( i );
      if( node != NULL ) getNLL( node, n );
    }
}



