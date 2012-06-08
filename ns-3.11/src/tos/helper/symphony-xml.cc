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
#include "ns3/model-vocabulary.h"
#include "ns3/model-element.h"

#include "symphony-xml.h"


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

  m_ConfigFileParser->setValidationScheme(xercesc::XercesDOMParser::Val_Never);

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

      initModelMap();
      createModels();

    }
  catch (xercesc::XMLException& e)
    {
      char* message = xercesc::XMLString::transcode(e.getMessage());
      ostringstream errBuf;
      errBuf << "Error parsing file: " << message << flush;
      xercesc::XMLString::release(&message);
    }
}

void
SymphonyXML::createModelElement(xercesc::DOMNodeList* nodeList,
     ModelVocabulary::ElementType type, HardwareModel* model)
{
  const XMLSize_t nodeCount = nodeList->getLength();
  std::vector<std::string> vacabulary = ModelVocabulary::getInstance().getVocabulary(type);
  std::vector<std::string>::iterator it;
  //now we iterate over all ModelVocabulary::ElementType attributes
  //which are defined in the vocabulary
  //if attribute is not set "EMPTY" is added

  for (XMLSize_t ix = 0; ix < nodeCount; ++ix)
    {
      xercesc::DOMNode* currentNode = nodeList->item(ix);
      xercesc::DOMElement* curElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
      //Extract name, it is common for all elements
      //TODO: possible to extract generic model and derivate it and further make parsing there
      std::string name = getAttributeValue(curElement, "name");
      model->addElement(type,name);
      //Iterate over the vocabulary
      for (it = vacabulary.begin(); it != vacabulary.end();
          it++)
        {
          if (hasAttribute(currentNode, *it))
            {
              model->addElementAttribute(type, name, *it, getAttributeValue(curElement, *it));
            }
          else
            {
              model->addElementAttribute(type,name,*it, "EMPTY");
            }
        }
      if(type == ModelVocabulary::CALL || type == ModelVocabulary::CALLBACK)
        {
          std::string paramsString = getAttributeValue(curElement, "params");
          int params = atoi(paramsString.c_str());
          for (int i =1; i<= params;i++)
            {
              std::stringstream sstm;
              sstm << "param" << i;
              string result = sstm.str();
              model->addElementAttribute(type, name, result, getAttributeValue(curElement, result));
            }
          if(type ==  ModelVocabulary::CALLBACK){
              addCallback(name);
          }
        }

    }


}

void
SymphonyXML::createModels()
{
  std::map<std::string, xercesc::DOMElement*>::iterator mapIter;

  for(mapIter = m_modelMap.begin(); mapIter != m_modelMap.end();
      mapIter++){
      HardwareModel* model = new HardwareModel;
      model->setName(mapIter->first);
      xercesc::DOMElement* currentElement = mapIter->second;
      //get property
      xercesc::DOMNodeList* nodeList ;
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
      m_models[mapIter->first]=model;

  }
}
HardwareModel
SymphonyXML::createHwModel(xercesc::DOMElement* currentElement, std::string name){
  HardwareModel model(name);
  //get property
  xercesc::DOMNodeList* nodeList ;
  nodeList = currentElement->getElementsByTagName(TAG_property);

  createModelElement(nodeList, ModelVocabulary::PROPERTY, &model);
  //  //get call
  nodeList = currentElement->getElementsByTagName(TAG_call);

//  createModelElement(nodeList, ModelVocabulary::CALL, model);
//    //get callback
//  nodeList = currentElement->getElementsByTagName(TAG_callback);
//
//  createModelElement(nodeList, ModelVocabulary::CALLBACK, model);
//    //get format
//  nodeList = currentElement->getElementsByTagName(TAG_format);
//
//  createModelElement(nodeList, ModelVocabulary::FORMAT, model);
//    //get source
//  nodeList = currentElement->getElementsByTagName(TAG_source);
//
//  createModelElement(nodeList, ModelVocabulary::SOURCE, model);

   return model;

}

HardwareModel*
SymphonyXML::getRadioModel(std::string name)
{
//  DOMElement* currentElement = m_modelMap[name];
//  HardwareModel model(name);
//
//
//  //get property
//  DOMNodeList* nodeList ;
//  nodeList = currentElement->getElementsByTagName(TAG_property);
//
//  createModelElement(nodeList, ModelVocabulary::PROPERTY, model);
//  //  //get call
//  nodeList = currentElement->getElementsByTagName(TAG_call);
//
//  createModelElement(nodeList, ModelVocabulary::CALL, model);
//    //get callback
//  nodeList = currentElement->getElementsByTagName(TAG_callback);
//
//  createModelElement(nodeList, ModelVocabulary::CALLBACK, model);
//    //get format
//  nodeList = currentElement->getElementsByTagName(TAG_format);
//
//  createModelElement(nodeList, ModelVocabulary::FORMAT, model);
//    //get source
//  nodeList = currentElement->getElementsByTagName(TAG_source);
//
//  createModelElement(nodeList, ModelVocabulary::SOURCE, model);


  return m_models[name];
}
std::vector<std::string>
SymphonyXML::getTosFunctions() {
  return tos_functions;
}
void
SymphonyXML::initModelMap() throw (std::runtime_error)
{
  if (!m_init)
    throw(std::runtime_error("XML is not initialized"));
  try
    {
      xercesc:: DOMNodeList* modelList = elementRoot->getElementsByTagName(TAG_model);

      const XMLSize_t modelCount = modelList->getLength();
      cout << "# number of models: " << modelCount << endl;

      //we loop through all models
      for (XMLSize_t xx = 0; xx < modelCount; ++xx)
        {
          xercesc::DOMNode* currentNode = modelList->item(xx);
          if (currentNode->getNodeType() && // true is not NULL
              currentNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) // is element
            {
              xercesc::DOMElement* currentElement =
                  dynamic_cast<xercesc::DOMElement*>(currentNode);
              string modelName = getString(
                  currentElement->getAttribute(xercesc::XMLString::transcode("name")));
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
      xercesc::XMLString::release(&message);
    }


}

void
SymphonyXML::addCallback(std::string func){
  tos_functions.push_back(func);
}

inline bool
SymphonyXML::hasAttribute(xercesc::DOMNode* node, std::string name)
{
  return dynamic_cast<xercesc::DOMElement*>(node)->hasAttribute(
      xercesc::XMLString::transcode(name.c_str()));
}

inline string
SymphonyXML::getAttributeValue(xercesc::DOMElement* node, std::string name)
{
  return getString((node)->getAttribute(xercesc::XMLString::transcode(name.c_str())));
}
inline string
SymphonyXML::getString(const XMLCh* const toHandle)
{
  string ret = xercesc::XMLString::transcode(toHandle);
  return trim(ret);

}
SymphonyXML::SymphonyXML()
{

  try
    {
      xercesc::XMLPlatformUtils::Initialize(); // Initialize Xerces infrastructure
    }
  catch (xercesc::XMLException& e)
    {
      char* message = xercesc::XMLString::transcode(e.getMessage());
      cerr << "XML toolkit initialization error: " << message << endl;
      xercesc::XMLString::release(&message);
      // throw exception here to return ERROR_XERCES_INIT
    }

  // Tags and attributes used in XML file.
  // Can't call transcode till after Xerces Initialize()
  TAG_root = xercesc::XMLString::transcode("root");
  TAG_model = xercesc::XMLString::transcode("model");
  TAG_property = xercesc::XMLString::transcode("property");
  TAG_call = xercesc::XMLString::transcode("call");
  TAG_callback = xercesc::XMLString::transcode("callback");
  TAG_format = xercesc::XMLString::transcode("format");
  TAG_source = xercesc::XMLString::transcode("source");

  TAG_empty = xercesc::XMLString::transcode("empty");

  m_ConfigFileParser = new xercesc::XercesDOMParser();




}

SymphonyXML::~SymphonyXML()
{
  // Free memory
  std::map<std::string, HardwareModel*>::iterator iterHw;

  m_modelMap.clear();
  //delete all pointer
  for(iterHw = m_models.begin(); iterHw != m_models.end();
      iterHw++){
      delete(iterHw->second);
  }
  m_models.clear();
  delete m_ConfigFileParser;
  try
    {
      xercesc::XMLString::release(&TAG_root);
      xercesc::XMLString::release(&TAG_model);
      xercesc::XMLString::release(&TAG_property);
      xercesc::XMLString::release(&TAG_call);
      xercesc::XMLString::release(&TAG_callback);
      xercesc::XMLString::release(&TAG_format);
      xercesc::XMLString::release(&TAG_source);
      xercesc::XMLString::release(&TAG_empty);
      xercesc::XMLPlatformUtils::Terminate(); // Terminate after release of memory
    }
  catch (xercesc::XMLException& e)
    {
      char* message = xercesc::XMLString::transcode(e.getMessage());

      cerr << "XML tolkit teardown error: " << message << endl;
      xercesc::XMLString::release(&message);
    }

}

