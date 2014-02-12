// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include <Parameters.h>
#include <Alphabet.h>

#include "Tree.h"
#include "PstTree.h"
#include "FixedTree.h"
#include "NaiveTree.h"
#include "TreeFactory.h"
#include "TreeModifier.h"
#include "KLModifier.h"
#include "PSModifier.h"

Alphabet* TreeFactory::alphabet_ = NULL;

string TreeFactory::toHelp() 
{
  string m = "";
  m += "---- General tree options:\n";
  m += "-alp:     Alphabet, 0=Binary, 1=DNA, 2=Protein (1)\n";
  m += "-c_c:     Use constant cut-off (not npar, see \"-nc\"\n";
  m += "-kmax:    Maximum depth of tree, ie. longest memory (10)\n";
  m += "-k:       Order if fixed model, ie. word-length - 1 (3)\n";
  m += "-m:       Model, 0=Fixed. 1=Variable, 2=Naive (1)\n";
  m += "-minc:    Minimum count of any pattern in the PST tree (2)\n";
  m += "-npar:    Number of parameters allowed in the PST tree (16)\n";
  m += "-nc:      Constant (K) for pruning tree in KL method. This\n";
  m += "          value is greater than zero. If a negative value\n";
  m += "          is assigned, K = 0.5*Chi(r,0.05) where r is the\n";
  m += "          degrees of freedom. (-1.0)\n";
  m += "-nocum:   Do not use accumulated prob.in PST           (false)\n";
  m += "-pruning: Pruning algorithm to use. Options:\n";
  m += "          \"\" = None\n"; 
  m += "          KL = Kullback-Liebler-pruning\n";
  m += "          PS = Peres-Shields-prunine .                (\"KL\")\n";
  m += "          At present: Only implemented for PST!\n";
  m += "-------------------------\n";    
  return m;
}


trees::Tree* TreeFactory::getObject( Parameters& params )
{
  // Set alphabet 
  if( alphabet_ != NULL )
    {
      // IF WE DELETE THE ALPHABET --> SEGMENTATION-FAULT IN
      // Trees THAT BEEN INSTANTIATED ALREADY!!! THEREFORE
      // CANNOT CHANGE ALPHABET DURING A RUN
      //  delete alphabet_;
    }
  else
    { 
      alphabet_ = new Alphabet();
      switch( params.GetIntParam( "-alp" ) )
	{
	case 0:
	  {
	    alphabet_->setAlphabet( Alphabet::BINARY );
	    break;
	  }
	case 1: // Default (see CLOptions.h)
	  {
	    alphabet_->setAlphabet( Alphabet::DNA );
	    break;
	  }
	case 2:
	  {
	    alphabet_->setAlphabet( Alphabet::PROTEIN );
	    break;
	  }      
	case 3: // Default (see CLOptions.h)
	  {
	    alphabet_->setAlphabet( Alphabet::N_DNA );
	    break;
	  }

	default:
	  {
	    cerr << "No such alphabet in classifier!\n"
		 << "Alphabet be set to DNA\n";
	    alphabet_->setAlphabet( Alphabet::DNA );
	    break;
	  }
	}
    }
  // Set model
  switch( params.GetIntParam( "-model" ) )
    {
    case 0:
      {
	return new trees::FixedTree( alphabet_, params.GetIntParam( "-k" )  );
      }
    case 1:  // Default (see BBC_CLOptions.h)
      {
	trees::Tree* myTree = new trees::PstTree( alphabet_, params.GetIntParam( "-kmax" ) );
	myTree->useAdjustedProbabilities( params.GetBoolParam( "-nocum" ) );

	// Set the correct pruning-algorithm
	string method = params.GetStringParam( "-pruning" );
	if( method != "" )
	  {
	    //     * \exception see class Exception.h in common, if wrong method specified
	    if( method == "PS" )
	      {
		myTree->setTreeModifier( new PSModifier( myTree ) );
	      }
	    else if( method == "KL" )
	      {
		myTree->setTreeModifier(  new KLModifier( myTree ) );
	      }
	    else
	      {
		cerr << " No such TreeModifier: " << method << ", none will be used!\n";
		//throw common::Exception( "No such modifier...", common::Exception::ERROR );
	      }
	  }
	return myTree;	
      }
    case 2:  // Default (see BBC_CLOptions.h)
      {
	return new trees::NaiveTree( alphabet_, params.GetIntParam( "-k" ) );
      }
    default:
      {
	cerr << "No such model defined in classifier!\n"
	     << "Model will be set to Variable!\n";
	trees::Tree* myTree = new trees::PstTree( alphabet_, params.GetIntParam( "-kmax" ) );
	myTree->useAdjustedProbabilities( params.GetBoolParam( "-nocum" ) );
	return myTree;
      }	      
    }
 }
