#include <iostream>
#include "hardware-model.h"

HardwareModel::HardwareModel()
{
  m_name = "DefaultRadioModel";
  Construct();
}

HardwareModel::HardwareModel(std::string name)
{
  m_name = name;
  Construct();

}
void
HardwareModel::Construct()
{

  m_properties.set_empty_key("UNDEFINED");
  m_calls.set_empty_key("UNDEFINED");
 // m_callbacks.set_empty_key("UNDEFINED");
  m_formats.set_empty_key("UNDEFINED");
  m_sources.set_empty_key("UNDEFINED");

}
void
HardwareModel::init(ModelVocabulary::ElementType type, unsigned int num){
  std::map<std::string, ModelElement*>::iterator it;
  it=m_callbacks.begin();
  for(int i=0; i< num; i++){

  }
}
inline ModelElement
HardwareModel::getOrCreateElement(ModelVocabulary::ElementType type,
    std::string elemenName, UniqueElement unique)
{
  UniqueElement::iterator it;
  ModelElement el;
  //if such element exists we add stuff!
  if ((it = unique.find(elemenName)) != unique.end())
    {
      el = unique[elemenName];

    }
  else
    {
      //create element and add

      el.setName(elemenName);
      el.setType(type);
      unique[elemenName]=el;
    }
    return el;
}

void
HardwareModel::addElement(ModelVocabulary::ElementType type,
    std::string elemenName, std::string name, std::string value)
{

  ModelElement el;
  UniqueElement::iterator it;
  std::map<std::string, ModelElement*>::iterator iter;
  switch (type) {
    case ModelVocabulary::PROPERTY:
      //        std::cout<<"PROPERTY ";
      //if such element exists we add stuff!
      if ((it = m_properties.find(elemenName)) != m_properties.end())
        {
          std::cout<<"found: "<<elemenName ;
          el = m_properties[elemenName];
        }
      else
        {
          //create element and add
          std::cout<<"creating: "<<elemenName ;
          el.setName(elemenName);
          el.setType(type);
          m_properties[elemenName]=el;
        }


      break;
    case ModelVocabulary::CALL:
      //        std::cout<<"CALL" <<std::endl;
      if ((it = m_calls.find(elemenName)) != m_calls.end())
        {
          el = m_calls[elemenName];
        }
      else
        {
          //create element and add
          el.setName(elemenName);
          el.setType(type);
          m_calls[elemenName]=el;
        }


      break;
    case ModelVocabulary::CALLBACK:
////      std::cout<<"CALLBACK" <<std::endl;
      ModelElement * elem;
      iter=m_callbacks.find(elemenName);
      if (iter != m_callbacks.end())
        {
          elem = m_callbacks[elemenName];
        }
      else
        {
          //create element and add
          elem = new ModelElement();
          elem->setName(elemenName);
          elem->setType(type);
          elem->addAttribute(name, value);
          m_callbacks[elemenName]=elem;
        }

      break;
    case ModelVocabulary::SOURCE:

      if ((it = m_sources.find(elemenName)) != m_sources.end())
        {
          el = m_sources[elemenName];
        }
      else
        {
          //create element and add
          el.setName(elemenName);
          el.setType(type);
          m_sources[elemenName]=el;
        }

      break;
    case ModelVocabulary::FORMAT:
////      std::cout<<"FORMAT" <<std::endl;
      if ((it = m_formats.find(elemenName)) != m_formats.end())
        {
          el = m_formats[elemenName];
        }
      else
        {
          //create element and add
          el.setName(elemenName);
          el.setType(type);
          m_formats[elemenName]=el;
        }

      break;
    case ModelVocabulary::UNDEFINED:
      std::cout<<" SHOULD NOT END HERE! UNDEFINED MODEL"<<std::endl;
      break;
    default:
      std::cout<<" SHOULD NOT END HERE! MODEL ERROR"<<std::endl;
      break;
  }

  el.addAttribute(name, value);


}


void
HardwareModel::printModel()
{
  std::map<std::string, ModelElement*>::iterator iter;
  std::cout <<"Model: "<< m_name<<std::endl;
  std::cout <<(m_properties["packet"]).getSize()<<std::endl;
  std::cout<<"***************"<<std::endl;
  //printKeyVal(m_properties);
  iter=m_callbacks.begin();
  while(iter != m_callbacks.end())
    {
      (iter->second)->printElemet();
      iter++;
    }
//  printKeyVal(m_callbacks);
//  printKeyVal(m_calls);
//  printKeyVal(m_formats);
//  printKeyVal(m_sources);


}

void
HardwareModel::printKeyVal(UniqueElement hash)
{
  UniqueElement::iterator it;
  std::cout<<"elements: "<< hash.size()<< std::endl;
  it=hash.begin();
  for(; it!=hash.end(); it++){
      std::cout<<it->first<<" - ";
      (it->second).printElemet();
        std::cout<< "************"<<std::endl;
  }
}

HardwareModel::~HardwareModel()
{
  //TODO: delete obje
  std::cout<<"Killing HW model NEED to delete obj"<<std::endl;
}
