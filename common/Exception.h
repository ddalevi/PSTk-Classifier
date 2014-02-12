// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef _EXCEPTION_
#define _EXCEPTION_

#include <string>

using namespace std;


/**
 * Wrapping common classes involved in non-specific actions.
 */
namespace common 
{
  /**
   * Class for handling error-messages and error-codes when exceptions 
   * are thrown.
   */
  class Exception
  {    
  public:
    /**
     * Different types of severity of errors
     */
    enum level { 
      REPAIR, /**< Less serious errors, reparable */
      WARNING,/**< Warning, but no interuption in program-flow */
      ERROR   /**< Error, not reparable, interuption in program-flow */
    };

    Exception() :
      text_( "" ),
      level_( 0 )
    {}
    Exception( const string& t, const int& l ) :
      text_( t ),
      level_( l )
    {}
    ~Exception()
    {}
    
    /**
     * \return string holding a message of what went wrong
     */
    string getText() const { return text_; }

    /**
     * \return level of error
     * \see enum level
     */
    int getLevel() const { return level_; }
  
  private:
    string text_;
    int level_;
  };
}

#endif
