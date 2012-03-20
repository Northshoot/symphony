/*
 * SymphonyXML.cc
 *
 *  Created on: Mar 14, 2012
 *      Author: lauril
 */
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "symphony-xml.h"

using namespace xercesc;
using namespace std;

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}
// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}


void
SymphonyXML::readConfigFile(string & configFile) throw( std::runtime_error )
{

	   struct stat fileStatus;
	   // Test to see if the file is ok.
	   int iretStat = stat(configFile.c_str(), &fileStatus);

	   if( iretStat == ENOENT )
	      throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
	   else if( iretStat == ENOTDIR )
	      throw ( std::runtime_error("A component of the path is not a directory."));
	   else if( iretStat == ELOOP )
	      throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
	   else if( iretStat == EACCES )
	      throw ( std::runtime_error("Permission denied."));
	   else if( iretStat == ENAMETOOLONG )
	      throw ( std::runtime_error("File can not be read\n"));
	   // Configure DOM parser.

	   m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Never );

	   m_ConfigFileParser->setDoNamespaces( false );
	   m_ConfigFileParser->setDoSchema( false );
	   m_ConfigFileParser->setLoadExternalDTD( false );

	   // Parser
	   try
	   {
	      m_ConfigFileParser->parse( configFile.c_str() );
	      // no need to free this pointer - owned by the parent parser object
	      xmlDoc = m_ConfigFileParser->getDocument();

	      elementRoot = xmlDoc->getDocumentElement();
	      if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));
	      m_init = true;
	   }
	   catch( xercesc::XMLException& e )
	   {
	      char* message = xercesc::XMLString::transcode( e.getMessage() );
	      ostringstream errBuf;
	      errBuf << "Error parsing file: " << message << flush;
	      XMLString::release( &message );
	   }
}

std::vector<std::string>
SymphonyXML::getTosFunctions() throw( std::runtime_error ){
	if(!m_init) throw(std::runtime_error( "XML is not initialized" ));
	try {
	      //Get External functions, only ONE element can exist
	      DOMNode*		tos_external = elementRoot->getElementsByTagName(TAG_tos_externals)->item(0);
	      DOMNodeList*    ext_list = tos_external->getChildNodes();

	      const  XMLSize_t nodeCount = ext_list->getLength();


	      for(XMLSize_t xx = 0; xx < nodeCount; ++xx) {
	    	  DOMNode* currentNode = ext_list->item(xx);
	    	if( currentNode->getNodeType() &&  // true is not NULL
	    		currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
	    		{
	    			// Found node which is an Element. Re-cast node as element
	    		DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	    		string func = getString(currentElement->getTextContent());
	    		tos_functions.push_back(func);
//	    		cout << "# funk: "  << func << endl;
	    		}
	      // For all nodes, children of "root" in the XML tree.
	      }

	} catch (xercesc::XMLException& e )
	   {
	      char* message = xercesc::XMLString::transcode( e.getMessage() );
	      ostringstream errBuf;
	      errBuf << "Error parsing file: " << message << flush;
	      XMLString::release( &message );
	}

	return tos_functions;
}

inline string
SymphonyXML::getString(const XMLCh* const toHandle){
	string ret= XMLString::transcode(toHandle);
	return trim(ret);

}
SymphonyXML::SymphonyXML() {

	   try
	   {
	      XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
	   }
	   catch( XMLException& e )
	   {
	      char* message = XMLString::transcode( e.getMessage() );
	      cerr << "XML toolkit initialization error: " << message << endl;
	      XMLString::release( &message );
	      // throw exception here to return ERROR_XERCES_INIT
	   }

	   // Tags and attributes used in XML file.
	   // Can't call transcode till after Xerces Initialize()
	   TAG_root        = XMLString::transcode("symphony");
	   TAG_tos_externals = XMLString::transcode("tos_externals");
	   TAG_sensors = XMLString::transcode("sensors");

	   m_ConfigFileParser = new XercesDOMParser;


}

SymphonyXML::~SymphonyXML() {
	   // Free memory

	   delete m_ConfigFileParser;
	   try
	   {
	      XMLString::release( &TAG_root );

	      XMLString::release( &TAG_tos_externals );

	   }
	   catch( ... )
	   {
	      cerr << "Unknown exception encountered in TagNamesdtor" << endl;
	   }

	   // Terminate Xerces

	   try
	   {
	      XMLPlatformUtils::Terminate();  // Terminate after release of memory
	   }
	   catch( xercesc::XMLException& e )
	   {
	      char* message = xercesc::XMLString::transcode( e.getMessage() );

	      cerr << "XML tolkit teardown error: " << message << endl;
	      XMLString::release( &message );
	   }
}

