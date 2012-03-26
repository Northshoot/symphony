/*
 * symphony-xml.h
 *
 *  Created on: Mar 14, 2012
 *      Author: lauril
 */

#ifndef SYMPHONY_XML_H_
#define SYMPHONY_XML_H_
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>

enum {
   ERROR_ARGS = 1,
   ERROR_XERCES_INIT,
   ERROR_PARSE,
   ERROR_EMPTY_DOCUMENT
};



class SymphonyXML {
public:

	SymphonyXML();
	virtual ~SymphonyXML();
	std::vector<std::string>  getTosFunctions() throw( std::runtime_error );
	void readConfigFile(std::string&) throw(std::runtime_error);


private:

	   inline std::string getString(const XMLCh* const toHandle) ;
	   xercesc::XercesDOMParser *m_ConfigFileParser;
	   char* m_OptionA;
	   char* m_OptionB;
	   bool m_init;
	   // Internal class use only. Hold Xerces data in UTF-16 SMLCh type.

	   xercesc::DOMDocument* xmlDoc;
	   xercesc::DOMElement* elementRoot;

	   XMLCh* TAG_root;

	   XMLCh* TAG_tos_externals;
	   XMLCh* TAG_sensors;
	   std::vector<std::string> tos_functions;
	   XMLCh* ATTR_OptionA;
	   XMLCh* ATTR_OptionB;
};
#endif /* SYMPHONY_XML_H_ */
