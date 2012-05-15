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

  //m_elements.set_empty_key(ModelVocabulary::UNDEFINED);
//  m_property.set_empty_key(m_name);
//  m_call.set_empty_key(m_name);
//  m_callback.set_empty_key(m_name);
//  m_format.set_empty_key(m_name);
//  m_source.set_empty_key(m_name);

}

void
HardwareModel::addElement(ModelVocabulary::ElementType type,
    std::string elemenName, std::string name, std::string value)
{
  UniqueElement::iterator it;
  switch (type) {
    case ModelVocabulary::PROPERTY:
      std::cout<<"PROPERTY";
      //if such element exists we add stuff!
      if(it == m_properties.find(elemenName) && it != m_properties.end()){
          std::cout<<" found " << elemenName<<std::endl;
      } else {
          //create element and add
          m_properties[elemenName]= new ModelElement();
          //it = m_properties.find(elemenName);
//          ModelElement * el = (ModelElement * )it->second;
//          el->setName(elemenName);
//          std::cout<<" Element created " << el->getName()<<std::endl;
      }
      break;
    case ModelVocabulary::CALL:
      std::cout<<"CALL" <<std::endl;
      break;
    case ModelVocabulary::CALLBACK:
      std::cout<<"CALLBACK" <<std::endl;
      break;
    case ModelVocabulary::FORMAT:
      std::cout<<"FORMAT" <<std::endl;
      break;
    case ModelVocabulary::SOURCE:
      std::cout<<"FORMAT" <<std::endl;
      break;
    case ModelVocabulary::UNDEFINED:
      std::cout<<" SHOULD NOT END HERE! UNDEFINED MODEL"<<std::endl;
      break;
    default:
      std::cout<<" SHOULD NOT END HERE! MODEL ERROR"<<std::endl;
      break;
  }
  std::cout<< "element name: " << elemenName << " " << name << ":" << value << std::endl;
}

ModelElement
HardwareModel::createNewElement(std::string name)
{
  ModelElement me;
  me.setName(name);
  return me;
}
void
HardwareModel::printModel()
{

}
HardwareModel::~HardwareModel()
{
}
