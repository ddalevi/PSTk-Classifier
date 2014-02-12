// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxFILEHANDLERxxx
#define xxxFILEHANDLERxxx

#include <string>
#include <vector>
#include "Parameters.h"
using namespace std;

/**
 * This class requires the use of Parameters and will
 * perform various operations needed in order to process
 * many files in a software. Add the lines on the buttom 
 * of this file to the CLOptions.h file. The following 
 * flags br used used: <br>
 * "-f"   (string) Specifying the name of a file to process
 *                 Many "-f" can be used<br>
 * "-f_f" (string) Specifying a file including names of
 *                 all files to be processed<br>.
 * "-ipf" (string) A postfix that is common to all input 
 *                 files to process<br>
 * "-ipwd"(string) Input directory<br>
 * "-opf" (string) A postfix added to output files<br>
 * "-osf" (string) A prefix added to output files  <br>
 * "-isf" (string) A prefix that is shared among all input files <br> 
 * "-opwd"(string) Output directory <br>
 * \author Daniel Dalevi
 * \date 2005-05-30
 * \note 
 * File options <br>
 * { "-f"      ,  "-file"                      , "xxx"             , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-f_f"    ,  "-file_of_filenames"         , "xxx"             , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-off"     ,  "-output_fasta_file"        , "xxx"             , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-opf"     ,  "-output_post_fix"          , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-ipf"     ,  "-input_post_fix"           , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-osf"     ,  "-output_pre_fix"           , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-isf"     ,  "-input_pre_fix"            , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-opwd"     ,  "-output_file_path"        , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-ipwd"    ,  "-input_file_path"          , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 *
 */
class FileHandler
{
  static const int MAXLINEWIDTH = 1000;

public:
  FileHandler( const int&, char** );
  ~FileHandler();
  
  /**
   * A static function that extracts the filename from 
   * the full pwd. Works for both windows and linux.
   */
  static void removeDirpath( string&, string& );


  /**
   * Copies filenames from commandline, or, file
   * to the vector filenames_
   */
  void setFileNames();

  /**
   * Returns the output file names with prefix, postfix 
   * and the directory path
   */
  vector<string> getOutputFileNames() const;

  /**
   * Returns the input file names with prefix, postfix 
   * and the directory path
   */
  vector<string> getInputFileNames() const;

  vector<string> getFileNames() const;

  vector<string> getInputFileNames( const string& ) const;

  /**
   * print this string in the help-message of any
   * application using this class.
   */
  static string toHelp();

  void strip();
  void strip( string& );
private:
  Parameters* params_;
  vector<string> fileNames_;
};
#endif





