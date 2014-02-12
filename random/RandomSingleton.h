#ifndef cpp_tools_random_singleton_h
#define cpp_tools_random_singleton_h

#include "Random.h"

/**
   Most often you only want, or need, a single random number generator
   in your programs. This class facilitates those needs, and ensures
   that there is only one instance of it and that there is only one
   global point of access to it. This class is a wrapper to the
   rlu_random random number generator.

   This is probably not thread safe.

   @see Design Patterns (the singleton and adapter pattern), rlu_random

   @version $Revision: 1.1.1.1 $ $Date: 2006/01/25 12:46:40 $ */

class RandomSingleton : public rlu_random
{
 public:
  /**
     Construct a new RandomSingleton object if it does not already exists.

     @return A pointer to the RandomSingleton object. */
  static RandomSingleton* instance();

 protected:
  /**
     Construct a RandomSingleton object.

     @see rlu_random */
  RandomSingleton();

 private:
  static RandomSingleton* instance_;
};

#endif
