#ifndef PARAMETERS_H
#define PARAMETERS_H

// Standard Includes
////////////////////
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#ifdef XMLSUPPORT
// XML include
#include <xercesc/dom/DOM.hpp>
#endif // XMLSUPPORT

// Class specific includes
#include "CLOptions.h"


// Constants/Declarations
/////////////////////////
struct PARAM_INSTANCE
{
   string short_name;
   string long_name;
   string parameter_type;
   bool parameter_list;
   vector<string> value;
   string sub_tag;
   bool visible;
   bool changeable;
};

// Strings used in class
const string OP_ILL_VAL[3] = { "Warning: Option: ", ", had an illegal value: \'", "\'. Ignored\n" };
const string OP_NO_VAL[2] = { "Warning: Option: ", ", didn't have a value. Ignored\n" };
const string OP_UNKN[2] = { "Warning: Unknown option: \'", "\'\n" };
const string NO_PARAM_SECTION[2] = { "Warning: No \'", "\' section in XML file\n" };
const string SETPARAM_FAIL[2] = { "Warning: Failed to set the parameter \'", "\'. Nonexistant.\n" };
const string NO_DOM_DOCUMENT = "Warning: GetXMLParameters cannot extract from an empty document. Nothing done\n";
const string UNKNOWN_PARAM[2] = { "Error: A GetXXParam function was called with an unknown parameter argument, \'", "\'\n" };
const string PARAM_NOT_FOUND[2] = { "Warning: GetParamListSize: Parameter \'", "\' not found.\n" };
const string VALIDATION_OOB = "Warning: Could not validate parameter, out-of-bounds.\n";
const string ACCESS_ERROR_BOOL = "Error: GetBoolParam used to get a non-boolean parameter.\n";
const string ACCESS_ERROR_DOUBLE = "Error: GetDoubleParam used to get a non-double parameter.\n";
const string ACCESS_ERROR_INT = "Error: GetIntParam used to get a non-integer parameter.\n";
const string ACCESS_ERROR_STRING = "Error: GetStringParam used to get a non-string parameter.\n";
const string ACCESS_OUT_OF_BOUNDS[2] = { "Error: Trying to access parameter \'", "\' out-of-bounds.\n" };
const string CHANGE_NOT_ALLOWED[2] = { "Warning: Parameter \'", "\' is not allowed to be changed. Ignored.\n" };
const string UNKNOWN_SHORTNAME = "unknown parameter";


// Namespace stuff
/////////////////////
using namespace std;


// Class declarations
/////////////////////
class Parameters
{
public:
   // Constructor/Destructor
   Parameters( bool CLUsage );
   ~Parameters();

   // Function loading the CL parameters depending on the value of
   // the UseCLArgs attribute set by the constructor
   void LoadParameters( const int argc, char* argv[] );

   void ParseCLArgs( const vector<string>& );

   // Get functions. Return the value of the supplied parameter
   bool GetBoolParam( string in_param, unsigned int in_para_idx = 0);
   double GetDoubleParam( string in_param, unsigned int in_para_idx = 0);
   int GetIntParam( string in_param, unsigned int in_para_idx = 0 );
   string GetStringParam ( string in_param, unsigned int in_para_idx = 0);

   // Get the number of values in the parameter with supplied name
   // Used when there are several values in one parameter (list type)
   unsigned int GetParamListSize( string param );

   // Function returning the longname to the Parameter with supplied shortname
   string GetLongName( string in_param );

   // Sets the supplied parameter to the value
   void SetParam( string in_param, string value );

#ifdef XMLSUPPORT
   // Function returning a DOM representation of the Parameters
   DOM_Node BuildXMLRep( DOM_Document &doc );

   // Function extracting parameters from xml tree
   void GetXMLParameters( DOM_Document doc );

#endif // XMLSUPPORT

   // Get the application's name
   string GetAppName();

#ifdef _DEBUG
   // Debug help function
   void PrintParams();
#endif

private:
   // Vector of PARAM_INSTANCE holding the different parameters and their
   // identifiers
   vector< PARAM_INSTANCE > params;

   // The application's name, used when writing the parameter as an XML file
   string app_name;

   // The parameter's sub-tag used when building the Parameter XML tree
   string param_tag_name;

   // Variable saying if we should parse the command line for options.
   bool UseCLArgs;



   // Parse the command line and extract values found
   void ParseCLArgs( const int argc, char* argv[] );

   // Loads current parameters from table
   void LoadIdsAndDefaults();

   // Function checking wether the value is legal for the selected parameter
   bool CheckParamValidity( string value, int para_idx );

   // Function returning the index to the Parameter with supplied name
   int GetParamIdx( string in_param );

};

#endif //PARAMETERS_H
