// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2


#include "Util.h"
using namespace std;

std::string Util::reverseComplement( const std::string& s )
{
  std::string res;
  for( std::string::const_reverse_iterator ir = s.rbegin(); ir !=  s.rend() ; ++ir )
    {
      res += *ir;
    }
  for( size_t i = 0; i < res.size(); ++i )
    {
      if( toupper( res[ i ] ) == 'A' )      res[ i ] = 'T';
      else if( toupper( res[ i ] ) == 'C' ) res[ i ] = 'G';
      else if( toupper( res[ i ] ) == 'G' ) res[ i ] = 'C';
      else if( toupper( res[ i ] ) == 'T' ) res[ i ] = 'A';
    }
  return res;
}





std::string Util::ToString( const int& t, bool in_hex )
  {
    // Create a stream
    std::ostringstream oss; 
    // Insert value to stream
    if ( !in_hex )
      {
	oss << std::setprecision( 8 ) << t;
      }
    else
      {
	oss << std::hex << t;
      }
    // Return copy of string
    return oss.str();
  }


std::string ToString( const double& t, bool in_hex )
{
  // Create a stream
  std::ostringstream oss; 
    // Insert value to stream
  if ( !in_hex )
      {
	oss << std::setprecision( 8 ) << t;
      }
    else
      {
	oss << std::hex << t;
      }
    // Return copy of string
  return oss.str();
}




std::string Util::TimeAndDate2String()
{
  const std::string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

  // Get the current time in tm format
  time_t cur_time = time( 0 );
  tm* cur_tm = localtime( &cur_time );

  // Construct return string
  std::string result = "";

  // Add hour
  if ( cur_tm->tm_hour < 10 ) result += "0";
  result += ToString( cur_tm->tm_hour ) + ":";
  // Add minutes
  if ( cur_tm->tm_min < 10 ) result += "0";
  result += ToString( cur_tm->tm_min ) + ":";
  // Add seconds
  if ( cur_tm->tm_sec < 10 ) result += "0";
  result += ToString( cur_tm->tm_sec ) + ", ";
  // Add day of month
  if ( cur_tm->tm_mday < 10 ) result += "0";
  result += ToString( cur_tm->tm_mday ) + " ";
  // Add name of month
  result += months[ cur_tm->tm_mon ] + ", ";
  // Add year
  result += ToString( 1900 + cur_tm->tm_year );
  return result;
}
