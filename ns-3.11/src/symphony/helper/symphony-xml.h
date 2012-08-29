/*
 * symphony-xml.h
 *
 *  Created on: Mar 14, 2012
 *      Author: lauril
 */

#ifndef SYMPHONY_XML_H_
#define SYMPHONY_XML_H_
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <map>
#include <utility>

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


#include "ns3/ptr.h"
#include "ns3/hardware-model.h"

enum
{
  ERROR_ARGS = 1, ERROR_XERCES_INIT, ERROR_PARSE, ERROR_EMPTY_DOCUMENT
};


class SymphonyXML
{
public:

  SymphonyXML();
  virtual
  ~SymphonyXML();
  std::vector<std::string>
  getExternalFunctions() ;
  void
  readConfigFile(std::string&) throw (std::runtime_error);

  ns3::Ptr<ns3::HardwareModel>
  getModel(std::string name);

private:
//  typedef void
//  (HardwareModel::*ELEMENT_ADD)(ModelVocabulary::ElementType type, std::string name, std::string value);
  inline std::string
  getString(const XMLCh* const toHandle);
  inline std::string
  getAttributeValue(xercesc::DOMElement* node, std::string name);
  inline bool
  hasAttribute(xercesc::DOMNode* node, std::string name);
  /**
   * creates property for model
   *
   */
  void
  createModelElement(xercesc::DOMNodeList* nodeList,
      ModelVocabulary::ElementType type, ns3::Ptr<ns3::HardwareModel> model);

  xercesc::XercesDOMParser *m_ConfigFileParser;
  bool m_init;
  void addCallback(std::string);
  void initModelMap() throw (std::runtime_error);
  void createModels();
  //HardwareModel createHwModel(xercesc::DOMElement* currentElement, std::string name);
  // Internal class use only. Hold Xerces data in UTF-16 SMLCh type.

  xercesc::DOMDocument* xmlDoc;
  xercesc::DOMElement* elementRoot;

  XMLCh* TAG_root;
  XMLCh* TAG_model;
  XMLCh* TAG_property;
  XMLCh* TAG_call;
  XMLCh* TAG_callback;
  XMLCh* TAG_format;
  XMLCh* TAG_source;
  XMLCh* TAG_empty;

  std::vector<std::string> tos_functions;
  std::map<std::string, ns3::Ptr<ns3::HardwareModel> > m_models;

  std::map<std::string, xercesc::DOMElement*> m_modelMap;

};
#endif /* SYMPHONY_XML_H_ */

