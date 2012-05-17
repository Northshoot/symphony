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
  m_callbacks.set_empty_key("UNDEFINED");
  m_formats.set_empty_key("UNDEFINED");
  m_sources.set_empty_key("UNDEFINED");

}

void
HardwareModel::getOrCreateElement(ModelVocabulary::ElementType type,
    std::string elemenName, UniqueElement unique, ModelElement el)
{
  UniqueElement::iterator it;
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

}

void
HardwareModel::addElement(ModelVocabulary::ElementType type,
    std::string elemenName, std::string name, std::string value)
{

  ModelElement el;
  switch (type) {
    case ModelVocabulary::PROPERTY:
      //        std::cout<<"PROPERTY ";
      //if such element exists we add stuff!
    getOrCreateElement(type, elemenName, m_properties, el);

      break;
    case ModelVocabulary::CALL:
      //        std::cout<<"CALL" <<std::endl;
      getOrCreateElement(type, elemenName, m_calls, el);
      break;
    case ModelVocabulary::CALLBACK:
//      std::cout<<"CALLBACK" <<std::endl;
      getOrCreateElement(type, elemenName, m_callbacks, el);
      break;
    case ModelVocabulary::FORMAT:
      //        std::cout<<"FORMAT" <<std::endl;
      getOrCreateElement(type, elemenName, m_formats, el);
      break;
    case ModelVocabulary::SOURCE:
//      std::cout<<"FORMAT" <<std::endl;
      getOrCreateElement(type, elemenName, m_sources, el);
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
  UniqueElement::iterator it;
  std::cout <<"Model: "<< m_name<<std::endl;
  printKeyVal(m_properties);
  printKeyVal(m_callbacks);
  printKeyVal(m_calls);
  printKeyVal(m_formats);
  printKeyVal(m_sources);


}

void
HardwareModel::printKeyVal(UniqueElement hash)
{
  UniqueElement::iterator it;
  std::cout<<"elements: "<< hash.size()<< std::endl;
  for(it=hash.begin(); it!=hash.end(); it++){
      std::cout<<it->first<<" - ";
      (it->second).printElemet();
        std::cout<< "************"<<std::endl;
  }
}

HardwareModel::~HardwareModel()
{
  std::cout<<"Killing HW model"<<std::endl;
}
