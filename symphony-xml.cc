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
#include "model-vocabulary.h"
#include "model-element.h"

#include "symphony-xml.h"

using namespace xercesc;
using namespace std;

// trim from start
static inline std::string &
ltrim(std::string &s)
{
  s.erase(s.begin(),
      std::find_if(s.begin(), s.end(),
          std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
static inline std::string &
rtrim(std::string &s)
{
  s.erase(
      std::find_if(s.rbegin(), s.rend(),
          std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}
// trim from both ends
static inline std::string &
trim(std::string &s)
{
  return ltrim(rtrim(s));
}

void
SymphonyXML::readConfigFile(string & configFile) throw (std::runtime_error)
{

  struct stat fileStatus;
  // Test to see if the file is ok.
  int iretStat = stat(configFile.c_str(), &fileStatus);

  if (iretStat == ENOENT)
    throw(std::runtime_error(
        "Path file_name does not exist, or path is an empty string."));
  else if (iretStat == ENOTDIR)
    throw(std::runtime_error("A component of the path is not a directory."));
  else if (iretStat == ELOOP)
    throw(std::runtime_error(
        "Too many symbolic links encountered while traversing the path."));
  else if (iretStat == EACCES)
    throw(std::runtime_error("Permission denied."));
  else if (iretStat == ENAMETOOLONG)
    throw(std::runtime_error("File can not be read\n"));
  // Configure DOM parser.

  m_ConfigFileParser->setValidationScheme(XercesDOMParser::Val_Never);

  m_ConfigFileParser->setDoNamespaces(false);
  m_ConfigFileParser->setDoSchema(false);
  m_ConfigFileParser->setLoadExternalDTD(false);

  // Parser
  try
    {
      m_ConfigFileParser->parse(configFile.c_str());
      // no need to free this pointer - owned by the parent parser object
      xmlDoc = m_ConfigFileParser->getDocument();

      elementRoot = xmlDoc->getDocumentElement();
      if (!elementRoot)
        throw(std::runtime_error("empty XML document"));
      m_init = true;
    }
  catch (xercesc::XMLException& e)
    {
      char* message = xercesc::XMLString::transcode(e.getMessage());
      ostringstream errBuf;
      errBuf << "Error parsing file: " << message << flush;
      XMLString::release(&message);
    }
}

void
SymphonyXML::createModelElement(DOMNodeList* nodeList,
     ModelVocabulary::ElementType type, HardwareModel& model)
{
  const XMLSize_t nodeCount = nodeList->getLength();
  std::vector<std::string> vacabulary = ModelVocabulary::getInstance().getVocabulary(type);
  std::vector<std::string>::iterator it;
  //now we iterate over all ModelVocabulary::ElementType attributes
  //which are defined in the vocabulary
  //if attribute is not set "EMPTY" is added
  model.init(type, modeCout);
  for (XMLSize_t ix = 0; ix < nodeCount; ++ix)
    {
      DOMNode* currentNode = nodeList->item(ix);
      DOMElement* curElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
      //Extract name, it is common for all elements
      //TODO: possible to extract generic model and derivate it and further make parsing there
      std::string name = getAttributeValue(curElement, "name");
      //Iterate over the vocabulary
      for (it = vacabulary.begin(); it != vacabulary.end();
          it++)
        {
          if (hasAttribute(currentNode, *it))
            {
              model.addElement(type, name, *it, getAttributeValue(curElement, *it));
            }
          else
            {
              model.addElement(type,name,*it, "EMPTY");
            }
        }
      if(type == ModelVocabulary::CALL || type == ModelVocabulary::CALLBACK)
        {
          std::string paramsString = getAttributeValue(curElement, "params");
          int params = atoi(paramsString.c_str());
          std::cout << "params: " << params<<" ";
          for (int i =1; i<= params;i++)
            {
              std::stringstream sstm;
              sstm << "param" << i;
              string result = sstm.str();
              std::cout<< "i: " << i << " " <<result<<"=name:"<<name;
              std::cout<<" " <<getAttributeValue(curElement, result) <<std::endl;
              model.addElement(type, name, result, getAttributeValue(curElement, result));

            }
        }

    }


}

HardwareModel
SymphonyXML::getRadioModel(std::string name)
{
  DOMElement* currentElement = m_modelMap[name];
  HardwareModel model(name);


  //get property
  DOMNodeList* nodeList ;
  nodeList = currentElement->getElementsByTagName(TAG_property);

  createModelElement(nodeList, ModelVocabulary::PROPERTY, model);
  //  //get call
  nodeList = currentElement->getElementsByTagName(TAG_call);

  createModelElement(nodeList, ModelVocabulary::CALL, model);
    //get callback
  nodeList = currentElement->getElementsByTagName(TAG_callback);

  createModelElement(nodeList, ModelVocabulary::CALLBACK, model);
    //get format
  nodeList = currentElement->getElementsByTagName(TAG_format);

  createModelElement(nodeList, ModelVocabulary::FORMAT, model);
    //get source
  nodeList = currentElement->getElementsByTagName(TAG_source);

  createModelElement(nodeList, ModelVocabulary::SOURCE, model);


  return model;
}

std::vector<std::string>
SymphonyXML::getTosFunctions() throw (std::runtime_error)
{
  if (!m_init)
    throw(std::runtime_error("XML is not initialized"));
  try
    {
      DOMNodeList* modelList = elementRoot->getElementsByTagName(TAG_model);

      const XMLSize_t modelCount = modelList->getLength();
      cout << "# number of models: " << modelCount << endl;

      //we loop through all models
      for (XMLSize_t xx = 0; xx < modelCount; ++xx)
        {
          DOMNode* currentNode = modelList->item(xx);
          if (currentNode->getNodeType() && // true is not NULL
              currentNode->getNodeType() == DOMNode::ELEMENT_NODE) // is element
            {
              DOMElement* currentElement =
                  dynamic_cast<xercesc::DOMElement*>(currentNode);
              string modelName = getString(
                  currentElement->getAttribute(XMLString::transcode("name")));
              //save models to the map
              m_modelMap[modelName] = currentElement;

            }
        }

    }
  catch (xercesc::XMLException& e)
    {
      char* message = xercesc::XMLString::transcode(e.getMessage());
      ostringstream errBuf;
      errBuf << "Error parsing file: " << message << flush;
      XMLString::release(&message);
    }

  return tos_functions;
}

inline bool
SymphonyXML::hasAttribute(DOMNode* node, std::string name)
{
  return dynamic_cast<xercesc::DOMElement*>(node)->hasAttribute(
      XMLString::transcode(name.c_str()));
}

inline string
SymphonyXML::getAttributeValue(xercesc::DOMElement* node, std::string name)
{
  return getString((node)->getAttribute(XMLString::transcode(name.c_str())));
}
inline string
SymphonyXML::getString(const XMLCh* const toHandle)
{
  string ret = XMLString::transcode(toHandle);
  return trim(ret);

}
SymphonyXML::SymphonyXML()
{

  try
    {
      XMLPlatformUtils::Initialize(); // Initialize Xerces infrastructure
    }
  catch (XMLException& e)
    {
      char* message = XMLString::transcode(e.getMessage());
      cerr << "XML toolkit initialization error: " << message << endl;
      XMLString::release(&message);
      // throw exception here to return ERROR_XERCES_INIT
    }

  // Tags and attributes used in XML file.
  // Can't call transcode till after Xerces Initialize()
  TAG_root = XMLString::transcode("root");
  TAG_model = XMLString::transcode("model");
  TAG_property = XMLString::transcode("property");
  TAG_call = XMLString::transcode("call");
  TAG_callback = XMLString::transcode("callback");
  TAG_format = XMLString::transcode("format");
  TAG_source = XMLString::transcode("source");

  TAG_empty = XMLString::transcode("empty");

  m_ConfigFileParser = new XercesDOMParser;



}

SymphonyXML::~SymphonyXML()
{
  // Free memory

  delete m_ConfigFileParser;
  try
    {
      XMLString::release(&TAG_root);
      XMLString::release(&TAG_model);
      XMLString::release(&TAG_property);
      XMLString::release(&TAG_call);
      XMLString::release(&TAG_callback);
      XMLString::release(&TAG_format);
      XMLString::release(&TAG_source);
      XMLString::release(&TAG_empty);

    }
  catch (...)
    {
      cerr << "Unknown exception encountered in TagNamesdtor" << endl;
    }

  // Terminate Xerces

  try
    {
      XMLPlatformUtils::Terminate(); // Terminate after release of memory
    }
  catch (xercesc::XMLException& e)
    {
      char* message = xercesc::XMLString::transcode(e.getMessage());

      cerr << "XML tolkit teardown error: " << message << endl;
      XMLString::release(&message);
    }
}

