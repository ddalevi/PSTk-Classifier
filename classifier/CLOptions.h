#ifndef XXX_CLOPTIONS_H
#define XXX_CLOPTIONS_H

using namespace std;

// constants for the different columns in "PARAM_DEFINED_ARGS"
const int PARAM_SHORT = 0;
const int PARAM_LONG = 1;
const int PARAM_DEFAULT = 2;
const int PARAM_TYPE = 3;
const int PARAM_LIST_TYPE = 4;
const int PARAM_SUBTAG = 5;
const int PARAM_VISIBLE = 6;
const int PARAM_CHANGEABLE = 7;

// constants for the different types
const string PARAM_NUMBER = "number";
const string PARAM_STRING = "string";
const string PARAM_BOOL = "boolean";

// constants for the boolean values
const string PARAM_TRUE = "true";
const string PARAM_FALSE = "false";

// constants for normal and list type
const string PARAM_LIST = "list";
const string PARAM_NORMAL = "normal";

// constants for legalnumbers and null-strings
const string PARAM_NULLS = "";
const string PARAM_LEGALNUMBERCHARS = "0123456789-.eEdD";

// Command line parameters, in order 1) short name, 2) long name,
// 3) default value 4) Value type, 5) if command is of list type
// 5) if parameter is of list type, what is the subtags name

// All strings, end with row of all null strings (PARAM_NULLS)
// Allowed types: PARAM_NUMBER for all kinds of numerical values,
// PARAM_STRING for strings and PARAM_BOOL for booleans
// Only one of each parameter!



// This is the string that is supposed to be in the root element in order to
// match a <APP_NAME> with the parameters!
const string APP_NAME = "classifier";

// This is the name of the sub-section holding the Parameter information
const string PARAM_TAG = "parameters";

// The allowed arguments
static string PARAM_DEFINED_ARGS[][8] = 
{
  // General params
{ "-ff"      ,  "-fasta_file"               , "infile.fna"      , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-seq"      ,  "-seq_file"                , "seq.fna"         , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-l"       ,  "-length"                   , "1000"            , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-min"     ,  "-min_value"                , "10"              , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-max"     ,  "-max_value"                , "1000"            , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-sl"      ,  "-step_length"              , "5"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-nsamp"   ,  "-number_samples"           , "-1"              , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-frac"    ,  "-fraction"                 , "0"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-win"     ,  "-window"                   , "10"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-s"       ,  "-seed"                     , "0"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-slen"    ,  "-step_length"              , "1"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },

  // Tree options
{ "-alp"     ,  "-alphabet"                 , "1"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-minc"    ,  "-minimum_count"            , "2"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-npar"    ,  "-number_parameters"        , "16"              , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-c_c"     ,  "-constant_cutoff"          , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-nofna"   ,  "-no_save_test_seq"         , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-nc"      ,  "-n_cutoff"                 , "-1.0"            , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-kmax"    ,  "-max_depth_in_tree"        , "10"              , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-k"       ,  "-order_of_fixed_model"     , "3"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-nocum"   ,  "-not_use_cumulative_prob"  , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-m"       ,  "-model"                    , "1"               , PARAM_NUMBER  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-pruning" ,  "-pruning_algorithm"        , "KL"              , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-pseudo"  ,  "-pseudo_count"             , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },

  // File options
{ "-f"      ,  "-file"                      , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-f_f"    ,  "-file_of_filenames"         , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-off"     ,  "-output_fasta_file"        , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-opf"     ,  "-output_post_fix"          , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-ipf"     ,  "-input_post_fix"           , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-osf"     ,  "-output_pre_fix"           , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-isf"     ,  "-input_pre_fix"            , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-opwd"     ,  "-output_file_path"        , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-ipwd"    ,  "-input_file_path"          , ""                , PARAM_STRING  , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-revcomp" ,  "-reverse_complement"       , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },


{ "-crr"     ,  "-create_random_repr"       , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-aic"     ,  "-get_aic"                  , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-sap"     ,  "-score_against_profile"    , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-scan"    ,  "-score_against_itself"     , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-sim"     ,  "-simulate"                 , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-ffn"     ,  "-file_format_ffn"          , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-lrt"     ,  "-likelihood_ratio_test"    , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-h"       ,  "-help"                     , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-print"   ,  "-print"                    , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ "-v"       ,  "-version"                  , PARAM_FALSE       , PARAM_BOOL    , PARAM_NORMAL, "", PARAM_TRUE, PARAM_TRUE },
{ PARAM_NULLS,  PARAM_NULLS                 , PARAM_NULLS       , PARAM_NULLS   , PARAM_NULLS , PARAM_NULLS, PARAM_NULLS, PARAM_NULLS }
};

#endif

