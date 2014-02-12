#include "../common/Common.h"
#include "Parameters.h"

// Public functions
///////////////////

Parameters::Parameters( bool CLUsage )
{
   UseCLArgs = CLUsage;
   // Load the allowed parameters from options table
   LoadIdsAndDefaults();
}

Parameters::~Parameters()
{
}

void Parameters::LoadParameters( const int argc, char* argv[] )
{
   // Check if the command line should be parsed
   if ( UseCLArgs == true )
   {
      ParseCLArgs( argc, argv );
   }
}

// Function getting the current parameters value in boolean format
bool Parameters::GetBoolParam( string in_param, unsigned int in_para_idx )
{
   // Find which parameter index the string corresponds to
   int para_nbr = GetParamIdx( in_param );

   // Check that we found a matching parameter
   if ( para_nbr != -1 )
   {
      // Check that in_para_idx is less than the size of
      // the parameter value vector
      if ( in_para_idx < params[ para_nbr ].value.size() && in_para_idx >= 0 )
      {
         // Check that the parameter is of the correct type
         if ( params[ para_nbr ].parameter_type == PARAM_BOOL )
         {
            // Return correct value
            if ( params[ para_nbr ].value[ in_para_idx ] == PARAM_TRUE )
            {
               return true;
            }
            else
            {
               return false;
            }
         }
         // Parameter was not of the correct type
         else
         {
            // Output warning message
            cerr << ACCESS_ERROR_BOOL;
            // return safe result
            return false;
         }
      }
      // the in_para_idx was larger than the available data
      else
      {
         // Output warning message
         cerr << ACCESS_OUT_OF_BOUNDS[0] << in_param << ACCESS_OUT_OF_BOUNDS[1];
         // Return last value of the value-vector
         unsigned int last_value = params[ para_nbr ].value.size();
         if ( last_value > 0 )
         {
            if ( params[ para_nbr ].value[ last_value - 1 ] == PARAM_TRUE )
            {
               return true;
            }
            else
            {
               return false;
            }
         }
         else
         {
            return false;
         }
      }
   }

   // no matching parameter found
   else
   {
      // Output warning message
      cerr << UNKNOWN_PARAM[0] << in_param << UNKNOWN_PARAM[1];
      // return safe value
      return false;
   }
}

// function getting the current parameter's value in double format
double Parameters::GetDoubleParam( string in_param,
                                       unsigned int in_para_idx )
{
   // Find which parameter index the string corresponds to
   int para_nbr = GetParamIdx( in_param );

   // Check that we found a matching parameter
   if ( para_nbr != -1 )
   {
      // Check that in_para_idx is less than the size of
      // the parameter value vector
      if ( in_para_idx < params[ para_nbr ].value.size() && in_para_idx >= 0 )
      {
         // Check that the parameter is of the correct type
         if ( params[ para_nbr ].parameter_type == PARAM_NUMBER )
         {
            // Return correct value
            return atof( params[ para_nbr ].value[ in_para_idx ].c_str() );
         }
         // Parameter was not of the correct type
         else
         {
            // Output warning message
            cerr << ACCESS_ERROR_DOUBLE;
            // return safe result
            return 0.0;
         }
      }
      // the in_para_idx was larger than the available data
      else
      {
         // Output warning message
         cerr << ACCESS_OUT_OF_BOUNDS[0] << in_param << ACCESS_OUT_OF_BOUNDS[1];
         // Return last value of the value-vector
         unsigned int last_value = params[ para_nbr ].value.size();
         if ( last_value > 0 )
         {
            return atof( params[ para_nbr ].value[ last_value - 1 ].c_str() );
         }
         // No value existed
         else
         {
            return 0.0;
         }
      }
   }

   // no matching parameter found
   else
   {
      // Output warning message
      cerr << UNKNOWN_PARAM[0] << in_param << UNKNOWN_PARAM[1];
      // return safe value
      return 0.0;
   }
}

// Function getting the current parameter's value in int format
int Parameters::GetIntParam( string in_param, unsigned int in_para_idx )
{
   // Find which parameter index the string corresponds to
   int para_nbr = GetParamIdx( in_param );

   // Check that we found a matching parameter
   if ( para_nbr != -1 )
   {
      // Check that in_para_idx is less than the size of
      // the parameter value vector
      if ( in_para_idx < params[ para_nbr ].value.size() && in_para_idx >= 0 )
      {
         // Check that the parameter is of the correct type
         if ( params[ para_nbr ].parameter_type == PARAM_NUMBER )
         {
            // Return correct value
            return atoi( params[ para_nbr ].value[ in_para_idx ].c_str() );
         }
         // Parameter was not of the correct type
         else
         {
            // Output warning message
            cerr << ACCESS_ERROR_INT;
            // return safe result
            return 0;
         }
      }
      // the in_para_idx was larger than the available data
      else
      {
         // Output warning message
         cerr << ACCESS_OUT_OF_BOUNDS[0] << in_param << ACCESS_OUT_OF_BOUNDS[1];
         // Return last value of the value-vector
         unsigned int last_value = params[ para_nbr ].value.size();
         if ( last_value > 0 )
         {
            return atoi( params[ para_nbr ].value[ last_value - 1 ].c_str() );
         }
         // No value existed
         else
         {
            return 0;
         }
      }
   }

   // no matching parameter found
   else
   {
      // Output warning message
      cerr << UNKNOWN_PARAM[0] << in_param << UNKNOWN_PARAM[1];
      // return safe value
      return 0;
   }
}

// Function getting the current parameters value in string format
string Parameters::GetStringParam( string in_param,
                                       unsigned int in_para_idx )
{
   // Find which parameter index the string corresponds to
   int para_nbr = GetParamIdx( in_param );

   // Check that we found a matching parameter
   if ( para_nbr != -1 )
   {
      // Check that in_para_idx is less than the size of
      // the parameter value vector
      if ( in_para_idx < params[ para_nbr ].value.size() && in_para_idx >= 0 )
      {
         // Check that the parameter is of the correct type
         if ( params[ para_nbr ].parameter_type == PARAM_STRING )
         {
            // Return correct value
            return params[ para_nbr ].value[ in_para_idx ];
         }
         // Parameter was not of the correct type
         else
         {
            // Output warning message
            cerr << ACCESS_ERROR_STRING;
            // return safe result
            return "";
         }
      }
      // the in_para_idx was larger than the available data
      else
      {
         // Output warning message
         cerr << ACCESS_OUT_OF_BOUNDS[0] << in_param << ACCESS_OUT_OF_BOUNDS[1];
         // Return last value of the value-vector
         unsigned int last_value = params[ para_nbr ].value.size();
         if ( last_value > 0 )
         {
            return params[ para_nbr ].value[ last_value - 1 ];
         }
         // No value existed
         else
         {
            return "";
         }
      }
   }

   // no matching parameter found
   else
   {
      // Output warning message
      cerr << UNKNOWN_PARAM[0] << in_param << UNKNOWN_PARAM[1];
      // return safe value
      return "";
   }
}

// Get the number of values of a certain parameter
unsigned int Parameters::GetParamListSize( string param )
{
   int para_nbr = GetParamIdx( param );
   // Check that we found an matching parameter
   if ( para_nbr != -1 )
   {
      return (unsigned int)params[ para_nbr ].value.size();
   }
   else
   {
      // No matching parameter, output error message
      cerr <<  PARAM_NOT_FOUND[0] << param << PARAM_NOT_FOUND[1];
      // return safe value
      return 0;
   }
}

// Returns the longname to the parameter with the supplied shortname
string Parameters::GetLongName( string in_param )
{
   // for all parameters
   for ( unsigned int para_idx = 0 ; para_idx < params.size() ; para_idx++ )
   {
      // Check if supplied parameter is matching short
      if ( params[ para_idx ].short_name == in_param )
      {
         // if so, return index
         string longname = params[ para_idx ].long_name;
         longname.erase(0,1);
         return longname;
      }
   }
   // after checking all parameters without match, return UNKNOWN_PARAM
   return UNKNOWN_SHORTNAME;
}

#ifdef XMLSUPPORT
// Function building a parameters subtree from scratch
// the DOM_Document passed in is needed to create the
// new nodes from the same document obj. not doing so
// is illegal
DOM_Node Parameters::BuildXMLRep( DOM_Document &doc )
{
   // Create parameter root
   DOM_Node root = doc.createElement( DOMString( param_tag_name.c_str() ) );

   DOM_Node work_elm;
   PARAM_INSTANCE work_param;

   // Go through and append all parameters
   for ( unsigned int param_idx = 0 ; param_idx < params.size() ; param_idx++ )
   {
      // Check that the parameter should be displayed in output
      if ( params[ param_idx ].visible == true )
      {
         // Check that parameter is not of list type, normal case
         if ( params[ param_idx ].parameter_list == false )
         {
            work_param = params[ param_idx ];
            // Remove leading '-'
            work_param.long_name.erase(0,1);
            // Add element
            work_elm = root.appendChild( doc.createElement(
               DOMString::transcode( work_param.long_name.c_str() ) ) );
            // Add value in subnode
            work_elm.appendChild( doc.createTextNode(
               DOMString::transcode( work_param.value[0].c_str() ) ) );
         }
         // Parameter is of list type, we need to go through all sub elements
         else
         {
            // Another temporary container is needed
            DOM_Node work_sub_elm;
            work_param = params[ param_idx ];
            // Remove leading '-'
            work_param.long_name.erase(0,1);
            // Add 'parent' element
            work_elm = root.appendChild( doc.createElement(
               DOMString::transcode( work_param.long_name.c_str() ) ) );
            // Go through all children and add each of them to tree
            for ( unsigned int list_idx = 0 ; list_idx < work_param.value.size() ;
               list_idx++ )
            {
               // Add children to element
               // First sub-tag, getting name from parameter file
               work_sub_elm = work_elm.appendChild( doc.createElement(
                  DOMString::transcode( work_param.sub_tag.c_str() ) ) );
               // the sub-tag has one child containing the value
               work_sub_elm.appendChild( doc.createTextNode(
                  DOMString::transcode( work_param.value[ list_idx ].c_str() ) ) );
            }
         }
      }
   }
   return root;
}

// Collects the parameters from supplied XML DOM_Document
void Parameters::GetXMLParameters( DOM_Document doc )
{
   // Check that the document isn't empty
   if ( doc != NULL )
   {
      // Just for convenience
      PARAM_INSTANCE cur_param;
      string cur_name;

      // Assign the first parameter element found in tree to node
      // Safe downcasting to DOM_Element

      // Strange variation between Unix and Windows,
      // Fix by doing 2 versions for now
#ifdef WIN32
      DOM_Element node = (DOM_Element &)doc.getElementsByTagName(
         DOMString( param_tag_name.c_str() ) ).item( 0 );
#else
      DOM_Node aNode = doc.getElementsByTagName(
         DOMString( param_tag_name.c_str() ) ).item( 0 );
      DOM_Element node;
      if ( aNode.getNodeType() == DOM_Node::ELEMENT_NODE )
      {
         node = ( DOM_Element &)aNode;
      }
#endif //WIN32

      // Check if there exists a parameter section
      if ( node != NULL )
      {
         // For all parameters
         for ( unsigned int param_idx = 0 ; param_idx < params.size() ;
            param_idx++ )
         {
            cur_param = params[ param_idx ];
            cur_name = cur_param.long_name;

            // Try to find a matching XML parameter in the tree
            DOM_NodeList xml_param_matches = node.getElementsByTagName(
               DOMString( cur_name.erase(0,1).c_str() ) );

            // Go through all found values inserting them into the
            // parameter object. Undefined bahaviour if more than one
            // value for a non-list parameter
            for ( unsigned int param_match_idx = 0 ;
               param_match_idx < xml_param_matches.getLength() ;
               param_match_idx++ )
            {
               // The current match
               // Safe downcasting to DOM_Element

               // Strange variation between Unix and Windows,
               // Fix by doing 2 versions for now
#ifdef WIN32
               DOM_Element cur_match = (DOM_Element &)xml_param_matches.item(
                  param_match_idx );
#else
               DOM_Node cur_match_DOM_Node = xml_param_matches.item(
                  param_match_idx );
               DOM_Element cur_match;
               if ( cur_match_DOM_Node.getNodeType() ==
                  DOM_Node::ELEMENT_NODE )
               {
                  cur_match = (DOM_Element &)cur_match_DOM_Node;
               }
#endif //WIN32

               // Check if the current parameter is of list type, if so
               // it needs special handling
               if ( cur_param.parameter_list == true )
               {
                  // List of the children matching the sub_tag to the
                  // list parameter node
                  DOM_NodeList cur_match_children =
                     cur_match.getElementsByTagName(
                     DOMString( cur_param.sub_tag.c_str() ) );

                  // For each child
                  for ( unsigned int child_idx = 0 ;
                     child_idx < cur_match_children.getLength() ;
                     child_idx++ )
                  {
                     // Current child
                     DOM_Node cur_child = cur_match_children.item(
                        child_idx );
                     // The current child's child
                     DOM_Node cur_childs_child = cur_child.getFirstChild();
                     if ( cur_childs_child != 0 )
                     {
                        SetParam( string("-") + cur_name,
                           cur_childs_child.getNodeValue().transcode() );
                     }
                  }
               }
               // Parameter of normal type
               else
               {
                 if ( cur_match.getFirstChild() != NULL )
                  {
                     SetParam( string("-") + cur_name,
                        cur_match.getFirstChild().getNodeValue().
                        transcode() );
                  }
               }
            }
         }
      }
      // There was no parameter section in the xml file, do nothing
      else
      {
         cerr << NO_PARAM_SECTION[0] << param_tag_name <<
            NO_PARAM_SECTION[1];
      }
   }
   // Document was empty
   else
   {
      // Output warning message
      cerr << NO_DOM_DOCUMENT;
   }
}
#endif // XMLSUPPORT

// Get the application's name
string Parameters::GetAppName()
{
   return app_name;
}

#ifdef _DEBUG
// Debug help function
void Parameters::PrintParams()
{
  cout << "Parameter status: " << '\n';
  for ( unsigned int i = 0; i < params.size(); i++ )
  {
    cout << "paramname: " << params[i].short_name;
    cout << "   type: " << params[i].parameter_type;
    cout << "   list: " << params[i].parameter_list;
    cout << "   value(s): ";
    for ( unsigned int j = 0; j < params[i].value.size() ; j++ )
    {
      cout << params[i].value[j] << ' ';
    }
    cout << '\n';
  }
}
#endif

//Overloaded function of previous function
void Parameters::ParseCLArgs( const vector<string>& argv )
{
   // Go through all arguments except first one which is the command
   for (unsigned int arg_idx = 0 ; arg_idx < argv.size() ; arg_idx++ )
   {
      // Check if we found a matching option, i.e. GetParamIdx() != -1
     int this_arg_para_idx = GetParamIdx( argv[ arg_idx ].c_str() );
     
     if ( this_arg_para_idx != -1 )
       {
         // Check that we have more parameters to not be reading out of bounds
         if ( arg_idx < ( argv.size() - 1 ))
           {
             // Check that _next_ argument is _not_ a valid option (and
             // therefore _this_ is a legal value)
             int next_arg_para_idx = GetParamIdx( argv[ arg_idx + 1 ] );
             if ( next_arg_para_idx == -1 )
               {
               // Next argument is not a valid option
               // Check if value is legal for the current parameter (type check)
               // this in order to not overwrite legal previous values and to
               // indicate to user that the value is illegal
               bool param_legal = CheckParamValidity( argv[ arg_idx + 1 ], this_arg_para_idx );

               // If value was legal for the corresponding parameter,
               // set new value
               if ( param_legal == true )
               {
                  // Assign value to correponding parameter
                  SetParam( argv[ arg_idx ],
                            argv[ arg_idx + 1 ] );
               }
               else
               {
                  // Indicate illegal value to user and do not set value
                  cerr << OP_ILL_VAL[0] << argv[ arg_idx ] << OP_ILL_VAL[1] <<
                     argv[ arg_idx + 1 ] << OP_ILL_VAL[2];
               }
               // increase arg_idx as we should not check the next argument
               // (that was the current value)
               arg_idx++;
            }
            // Next argument _is_ a valid option, _this_ arg must be either a
            // boolean or an option missing it's value
            else
            {
               // Check if _this_ option is of boolean type and if so,
               // set corresponding parameter's value to true
               if ( params[ this_arg_para_idx ].parameter_type == PARAM_BOOL )
               {
                  SetParam( argv[ arg_idx ], string( PARAM_TRUE ) ); 
               }
               // No boolean, ignore option and indicate to user
               else
               { 
                  cerr << OP_NO_VAL[0] << argv[ arg_idx ] << OP_NO_VAL[1];
               }
            }
         }
         // No more parameters, value argument is missing or could be of
         // boolean type
         else
         {
            // Check if argument is of boolean type
            if ( params[ this_arg_para_idx ].parameter_type  == PARAM_BOOL )
            {
               SetParam( argv[ arg_idx ], string( PARAM_TRUE ) ); 
            }
            else 
            {
               cerr << OP_NO_VAL[0] << argv[ arg_idx ] << OP_NO_VAL[1];
            }
         }
      }

      // No matching option found
      else
      {
         cerr << OP_UNKN[0] << argv[ arg_idx ] << OP_UNKN[1];
      }
   }
}


// Private functions
////////////////////

// Function to parse the command line parameters and
// setting the corresponding values
void Parameters::ParseCLArgs( const int argc, char* argv[] )
{
   // Go through all arguments except first one which is the command
   for ( int arg_idx = 1 ; arg_idx < argc ; arg_idx++ )
   {
      // Check if we found a matching option, i.e. GetParamIdx() != -1
      int this_arg_para_idx = GetParamIdx( string( argv[ arg_idx ] ));

      if ( this_arg_para_idx != -1 )
      {
         // Check that we have more parameters to not be reading out of bounds
         if ( arg_idx < ( argc - 1 ))
         {
            // Check that _next_ argument is _not_ a valid option (and
            // therefore _this_ is a legal value)
            int next_arg_para_idx = GetParamIdx( string( argv[ arg_idx + 1 ] ));
            if ( next_arg_para_idx == -1 )
            {
               // Next argument is not a valid option
               // Check if value is legal for the current parameter (type check)
               // this in order to not overwrite legal previous values and to
               // indicate to user that the value is illegal
               bool param_legal = CheckParamValidity(
                  string( argv[ arg_idx + 1 ]), this_arg_para_idx );

               // If value was legal for the corresponding parameter,
               // set new value
               if ( param_legal == true )
               {
                  // Assign value to correponding parameter
                  SetParam( string( argv[ arg_idx ]),
                     string( argv[ arg_idx + 1 ]) );
               }
               else
               {
                  // Indicate illegal value to user and do not set value
                  cerr << OP_ILL_VAL[0] << argv[ arg_idx ] << OP_ILL_VAL[1] <<
                     argv[ arg_idx + 1 ] << OP_ILL_VAL[2];
               }
               // increase arg_idx as we should not check the next argument
               // (that was the current value)
               arg_idx++;
            }
            // Next argument _is_ a valid option, _this_ arg must be either a
            // boolean or an option missing it's value
            else
            {
               // Check if _this_ option is of boolean type and if so,
               // set corresponding parameter's value to true
               if ( params[ this_arg_para_idx ].parameter_type == PARAM_BOOL )
               {
                  SetParam( string( argv[ arg_idx ]), string( PARAM_TRUE ) );
               }
               // No boolean, ignore option and indicate to user
               else
               {
                  cerr << OP_NO_VAL[0] << argv[ arg_idx ] << OP_NO_VAL[1];
               }
            }
         }
         // No more parameters, value argument is missing or could be of
         // boolean type
         else
         {
            // Check if argument is of boolean type
            if ( params[ this_arg_para_idx ].parameter_type  == PARAM_BOOL )
            {
               SetParam( string( argv[ arg_idx ]), string( PARAM_TRUE ) );
            }
            else
            {
               cerr << OP_NO_VAL[0] << argv[ arg_idx ] << OP_NO_VAL[1];
            }
         }
      }

      // No matching option found
      else
      {
         cerr << OP_UNKN[0] << argv[ arg_idx ] << OP_UNKN[1];
      }
   }
}

// Function to load the used options into internal structure
void Parameters::LoadIdsAndDefaults()
{
   // Set app name to the correct one
   app_name = APP_NAME;

   // Set the parameter's section name to the correct one
   param_tag_name = PARAM_TAG;

   int arg_idx = 0;
   // Until encountering the last line (that has PARAM_NULLS at all positions
   while ( PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_SHORT ] != PARAM_NULLS )
   {
      // this needs to be inside loop as otherwise values are added cumulativly
      // Temporary PARAM_INSTANCE struct
      PARAM_INSTANCE param_work;
      // Copy the short name into the temp struct
      // Copy the long name into the temp struct
      // Copy the parameter type into the temp struct
      param_work.short_name = PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_SHORT ];
      param_work.long_name = PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_LONG ];
      param_work.parameter_type = PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_TYPE ];

      // Set the parameter should be displayed
      if ( PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_VISIBLE ] == PARAM_TRUE )
      {
         param_work.visible = true;
      }
      else
      {
         param_work.visible = false;
      }
      // Set wether the parameter can be changed or not
      if ( PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_CHANGEABLE ] == PARAM_TRUE )
      {
         param_work.changeable = true;
      }
      else
      {
         param_work.changeable = false;
      }

      // if the parameter is of PARAM_NORMAL type, set parameter_list to false,
      // and copy dafault parameter to struct, otherwise just set true
      if ( PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_LIST_TYPE ] == PARAM_NORMAL )
      {
         // Copy the default parameters into the temp struct
         param_work.value.push_back( string(
         PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_DEFAULT ]));
         param_work.parameter_list = false;
      }
      // If the parameter is of PARAM_LIST type, set parameter_list to true
      // and set sub_tag to correct label
      else if ( PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_LIST_TYPE ] == PARAM_LIST )
      {
         param_work.parameter_list = true;
         param_work.sub_tag = PARAM_DEFINED_ARGS[ arg_idx ][ PARAM_SUBTAG ];
      }

      // Add the temp struct to the vector containing the parameters
      params.push_back( param_work );
      // Increase index
      arg_idx++;
   }
}

// Checks wether the supplied value is legal for the chosen Parameter
bool Parameters::CheckParamValidity( string value, int para_idx )
{

   // Check that the parameter index is smaller than the total number of
   // parameters
   if ( para_idx < (int)params.size() && para_idx >= 0 )
   {
      // Check which type the parameter has (number, boolean, string)
      // For strings, do nothing, everything is legal
      // For booleans, check if value is true or false
      // For numbers, check if each character is within the legal range
      // or one of the legal special characters, ".-"

      // Check if the PARAM_BOOL type parameter is ok
      if ( params[ para_idx ].parameter_type == PARAM_BOOL )
      {
         if ( value == PARAM_TRUE || value == PARAM_FALSE )
         {
            // Boolean parameter ok!
            return true;
         }
         else
         {
            // Illegal boolean found!
            return false;
         }
      }
      // Check if PARAM_NUMBER type parameter is ok
      if ( params[ para_idx ].parameter_type == PARAM_NUMBER )
      {
         // For each character in argument
         for ( unsigned int str_idx = 0 ; str_idx < value.size() ; str_idx++ )
         {
            // Check if current char is one of the legal characters

            // Note! The case to look for here is NOT when we found a
            // non-matching character, as there ar many of those (for instance,
            // a '7' doesn't match a '8'). Only _after_ going through all
            // allowed characters we can say that the current character wasn't
            // valid, as no match was found.
            bool found_char = false;
            // Go through all legal chars
            for ( unsigned int legal_idx = 0 ;
               legal_idx < PARAM_LEGALNUMBERCHARS.size() ; legal_idx++ )
            {
               // Check if current char is one of the legal ones
               if ( PARAM_LEGALNUMBERCHARS[ legal_idx ] == value[ str_idx ] )
               {
                  found_char = true;
               }
            }
            // Check if we found a illegal character
            if ( found_char == false )
            {
               // Illegal character found, return false!
               return false;
            }
         }
         // All characters where legal, return true
         return true;
      }

      // All other types of parameters are considered ok for the moment
      else
      {
         return true;
      }
   }
   // Trying to access a out of bounds parameter
   else
   {
      cerr << VALIDATION_OOB;
      return false;
   }
}

// Set the supplied parameter with the supplied value
void Parameters::SetParam( string in_param, string value )
{
   // Try to find the supplied parameter
   int found_param_idx = GetParamIdx( in_param );
   // Check that we found a matching parameter
   if ( found_param_idx != -1 )
   {
      // Check if we are allowed to change the current parameter
      if ( params[ found_param_idx ].changeable == true )
      {
         // If parameter is not of list type
         if ( params[ found_param_idx ].parameter_list == false )
         {
            // Set the current value to new one
            params[ found_param_idx ].value[ 0 ] = value;
         }
         // Parameter is of list type
         else
         {
            // Add a new value to the other ones
            params[ found_param_idx ].value.push_back( value );
         }
      }
      // Parameter is not allowed to be changed, output warning message
      else
      {
         cerr << CHANGE_NOT_ALLOWED[0] << in_param << CHANGE_NOT_ALLOWED[1];
      }
   }
   // No matching parameter found
   else
   {
      // Output warning message
      cerr << SETPARAM_FAIL[2] << in_param << SETPARAM_FAIL[2];
   }
}

// Returns the index to the parameter with the supplied name
int Parameters::GetParamIdx( string in_param )
{
   // for all parameters
   for ( unsigned int para_idx = 0 ; para_idx < params.size() ; para_idx++ )
   {
      // Check if supplied parameter is matching short or long name
      if ( ( params[ para_idx ].short_name == in_param ) ||
         ( params[ para_idx ].long_name  == in_param ) )
      {
         // if so, return index
         return para_idx;
      }
   }
   // after checking all parameters without match, return -1
   return -1;
}
