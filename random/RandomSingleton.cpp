// $Id: RandomSingleton.cpp,v 1.1.1.1 2006/01/25 12:46:40 daniel Exp $


#include "RandomSingleton.h"

RandomSingleton* RandomSingleton::instance_ = NULL;

RandomSingleton* RandomSingleton::instance()
{
  if( instance_ == NULL ) 
    instance_ = new RandomSingleton();
  return instance_;
}

RandomSingleton::RandomSingleton()
  : rlu_random()  
{
}
