#include <iostream>
#include "radio-model.h"

RadioModel::RadioModel()
{
  m_name = "DefaultRadioModel";
  Construct();
}

RadioModel::RadioModel(std::string name)
{
  m_name = name;
  Construct();

}
void
RadioModel::Construct()
{
  m_property.set_empty_key(m_name);
  m_call.set_empty_key(m_name);
  m_callback.set_empty_key(m_name);
  m_format.set_empty_key(m_name);
  m_source.set_empty_key(m_name);

}
RadioModel::~RadioModel()
{

}

void
RadioModel::addModely(std::string key, std::string value)
{
  m_property[key] = value;
}

std::string
RadioModel::getModelName() const
{
  std::cout << "name: " << m_name << std::endl;
  return m_name;
}

void
RadioModel::addModelProperty(std::string key, std::string value)
{
  m_property[key] = value;
}

std::string
RadioModel::getModelProperty(std::string key)
{
  return m_property[key];
}

uint32_t
RadioModel::getSizeOfProperty()
{
  return m_property.size();
}

std::string
RadioModel::getModelCall(std::string key)
{
  return m_call[key];
}

void
RadioModel::addModelCall(std::string key, std::string value)
{
  m_call[key] = value;
}

uint32_t
RadioModel::getSizeOfCall()
{
  return m_call.size();
}

std::string
RadioModel::getModelCallBack(std::string key)
{
  return m_callback[key];
}

void
RadioModel::addModelCallBack(std::string key, std::string value)
{
  m_callback[key] = value;
}

uint32_t
RadioModel::getSizeOfCallBack()
{
  return m_callback.size();
}

std::string
RadioModel::getModelFormat(std::string key)
{
  return m_format[key];
}

void
RadioModel::addModelFormat(std::string key, std::string value)
{
  m_format[key] = value;
}

uint32_t
RadioModel::getSizeOfFormat()
{
  return m_format.size();
}

std::string
RadioModel::getModelSource(std::string key)
{
  return m_source[key];
}

void
RadioModel::addModelSource(std::string key, std::string value)
{
  m_source[key] = value;
}

uint32_t
RadioModel::getSizeOfSource()
{
  return m_source.size();
}

void
RadioModel::printModel(void)
{
  std::cout << "Model: " << m_name << std::endl;
  std::cout << "Properties: ";
  printKeyVal(m_property);
  std::cout<<std::endl;

  std::cout << "Calls: ";
  printKeyVal(m_call);
  std::cout<<std::endl;

  std::cout << "Callback: ";
  printKeyVal(m_callback);
  std::cout<<std::endl;

  std::cout << "Format: ";
  printKeyVal(m_format);
  std::cout<<std::endl;

  std::cout << "Source: ";
  printKeyVal(m_source);
  std::cout<<std::endl;
}

void
RadioModel::printKeyVal(dense_hash_map<std::string, std::string> map)
{
  dense_hash_map<std::string, std::string>::iterator it;
  if(map.begin() != map.end())
    {
    for( it = map.begin(); it != map.end(); it++ )
      {
        std::cout<<"[";
        std::cout << it->first;
        std::cout <<":"<<(it->second);
        std::cout << "] ";
      }
    }
  else
    {
      std::cout << "empty";
    }
}
