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
#include <map>
#include <utility>
#include "radio-model.h"
#include "hardware-model.h"

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
  getTosFunctions() throw (std::runtime_error);
  void
  readConfigFile(std::string&) throw (std::runtime_error);

  RadioModel
  getRadioModel(std::string name);

private:
  typedef void
  (RadioModel::*ELEMENT_ADD)(std::string key, std::string value);
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
      std::vector<std::string> vacabulary, RadioModel& model, ELEMENT_ADD addFunction);
  xercesc::XercesDOMParser *m_ConfigFileParser;
  bool m_init;
  // Internal class use only. Hold Xerces data in UTF-16 SMLCh type.

  xercesc::DOMDocument* xmlDoc;
  xercesc::DOMElement* elementRoot;

  XMLCh* TAG_root;
  XMLCh* TAG_empty;
  XMLCh* TAG_model;
  XMLCh* TAG_property;
  XMLCh* TAG_callback;
  XMLCh* TAG_call;
  XMLCh* TAG_format;
  XMLCh* TAG_source;
  std::vector<std::string> tos_functions;
  std::vector<std::string> property_vocabulary;
  std::vector<std::string> call_vocabulary;
  std::vector<std::string> callback_vocabulary;
  std::vector<std::string> format_vocabulary;
  std::vector<std::string> source_vocabulary;
  std::map<std::string, xercesc::DOMElement*> m_modelMap;

};
#endif /* SYMPHONY_XML_H_ */

