/*
 * model-element.cc
 *
 *      Author: Laurynas Riliskis
 *      e-mail: laurynas.riliskis@ltu.se
 */
#include <iostream>
#include <stdio.h>
#include <string>

#include "ns3/object.h"
#include "model-element.h"
#include "model-vocabulary.h"

namespace ns3
{
  NS_OBJECT_ENSURE_REGISTERED(ModelElement);

  TypeId
  ModelElement::GetTypeId(void)
  {
    static TypeId tid = TypeId("ns3::ModelElement").SetParent<Object>();

    return tid;
  }

ModelElement::ModelElement()
{
}

ModelElement::ModelElement(std::string name)
{
  m_name=name;
}

void
ModelElement::addAttribute(std::string key, std::string value)
{
  attribute[key]=value;

}

std::string
ModelElement::getAttributeValue(std::string key)
{
  return attribute[key];
}

void
ModelElement::printElement()
{
  std::cout<<"[";
  Attribute::iterator iter;
  Attribute::iterator it=attribute.begin();
  iter=it;
  iter++;
  for(;it !=attribute.end();++it)
      {

        std::cout<<it->first<<":"<<it->second;
        if(iter !=attribute.end())
          {
          std::cout<<",";
          iter++;
          }

      }
      std::cout<<"]";
}

ModelElement::~ModelElement()
{
  DoDispose();
  //std::cout<< "ModelElement::~ModelElement()"<<std::endl;
}

void
ModelElement::DoDispose(void)
{
  //std::cout << "DoDispose " << count << std::endl;
  attribute.clear();
}
}
