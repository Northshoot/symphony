#include <iostream>
#include "ns3/object.h"

#include "hardware-model.h"

namespace ns3
{
  NS_OBJECT_ENSURE_REGISTERED(HardwareModel);

  TypeId
  HardwareModel::GetTypeId(void)
  {
    static TypeId tid = TypeId("ns3::HardwareModel").SetParent<Object>();

    return tid;
  }
HardwareModel::HardwareModel()
{
}

HardwareModel::HardwareModel(std::string name)
{
  m_name=name;
  Constuct();
}

void
HardwareModel::Constuct()
{
  init = true;
}

HardwareModel::~HardwareModel()
{

  DoDispose();
  //std::cout<<"HardwareModel::~HardwareModel()"<<std::endl;
}
inline void
HardwareModel::deleteElements(UniqueElement elem){
    elem.clear();
}

Ptr<ModelElement>
HardwareModel::getElement(ModelVocabulary::ElementType type, std::string name)
{
  return getUniqueElement(type)[name];
}

void
HardwareModel::setName(std::string name)
{
  m_name = name;
}

void
HardwareModel::addElementAttribute(ModelVocabulary::ElementType type,
    std::string elemenName, std::string name, std::string value)
{
  getUniqueElement(type)[elemenName]->addAttribute(name, value);
}

void
HardwareModel::addElement(ModelVocabulary::ElementType type,
    std::string elemenName)
{
  getUniqueElement(type)[elemenName]=new ModelElement();
}


void
HardwareModel::printModel(void)
{
  std::cout<<"m_properties: "<<std::endl;
  printUniqueElement(m_properties);
  std::cout<<"m_callbacks: "<<std::endl;
  printUniqueElement(m_callbacks);
  std::cout<<"m_calls: "<<std::endl;
  printUniqueElement(m_calls);
  std::cout<<"m_formats: "<<std::endl;
  printUniqueElement(m_formats);
  std::cout<<"m_sources: "<<std::endl;
  printUniqueElement(m_sources);
}
void
HardwareModel::printUniqueElement(UniqueElement elem)
{
  for(UniqueElement::iterator it=elem.begin();it!=elem.end();++it)
  {
      std::cout <<"element: "<<it->first<<" ";
      ((*it).second)->printElement();
      std::cout<<std::endl;
  }
}

inline UniqueElement&
HardwareModel::getUniqueElement(ModelVocabulary::ElementType type)
{
  switch (type) {
    case ModelVocabulary::PROPERTY:
      return m_properties;
    case ModelVocabulary::CALL:
      return m_calls;
    case ModelVocabulary::CALLBACK:
      return m_callbacks;
    case ModelVocabulary::FORMAT:
      return m_formats;
    case ModelVocabulary::SOURCE:
      return m_sources;
    case ModelVocabulary::UNDEFINED:
      std::cout<<"OOOOPSSS! UNDEFINED element creation!"<<std::endl;
      return m_undefined;
    default:
      std::cout<<"OOOOPSSS! default element creation!"<<std::endl;
      return m_undefined;
  }
}

void
HardwareModel::DoDispose(void)
{
  deleteElements(m_properties);
  deleteElements(m_callbacks);
  deleteElements(m_calls);
  deleteElements(m_formats);
  deleteElements(m_sources);
}
}
