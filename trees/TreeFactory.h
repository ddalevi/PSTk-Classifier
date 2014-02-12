// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#ifndef xxxTREEFACTORYxxx
#define xxxTREEFACTORYxxx

#include "Tree.h"

class Alphabet;

using namespace std;
using namespace trees;

class Parameters;

/**
 * Purpose: To provide the correct tree given a parameter-object
 * Requirements: CLOptions.h need to have the following parameters defined:
 *               "-k", "-kmax", "-model", "-alp" (See bottom of this file)
 * \author  Daniel Dalevi
 * \date    2005-05-30
 * \note  
 *  Add the following lines to your CLOption file:<br>
 *<br>
 * { "-alp"     ,  "-alphabet"                 , "1"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-minc"    ,  "-minimum_count"            , "2"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-npar"    ,  "-number_parameters"        , "16"              , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-c_c"     ,  "-constant_cutoff"          , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-nc"      ,  "-n_cutoff"                 , "5.0"             , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-kmax"    ,  "-max_depth_in_tree"        , "10"              , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-k"       ,  "-order_of_fixed_model"     , "3"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-nocum"   ,  "-not_use_cumulative_prob"  , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 * { "-m"       ,  "-model"                    , "1"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br> 
 * { "-pruning" ,  "-pruning_algorith"         , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },<br>
 */
class TreeFactory
{
public:

  /**
   * Provide command-line parameters to a string<br>
   * Add this to your Helper file (txt):
   *
   * TreeFactory::toHelp
   */
  static string toHelp();

  /**
   * Returns an object of type Tree.
   * \param params Parameter-object that will 
   * specify which object to return
   */
  static trees::Tree* getObject( Parameters& params );

  static Alphabet* alphabet_;
};

#endif

