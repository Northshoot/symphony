/*
 * model-element.cc
 *
 *      Author: Laurynas Riliskis
 *      e-mail: laurynas.riliskis@ltu.se
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "model-element.h"
#include "model-vocabulary.h"
#include <boost/lexical_cast.hpp>

ModelElement &
ModelElement::operator=(const ModelElement & rhs) throw ()
{
  this->m_name = rhs.m_name;
  this->m_initial = rhs.m_initial;
  this->m_params = rhs.m_params;
  this->m_regexp = rhs.m_regexp;
  this->m_return = rhs.m_return;
  this->m_size = rhs.m_size;
  this->m_time = rhs.m_time;
  this->m_type = rhs.m_type;
  this->m_units = rhs.m_units;
  this->m_vocabulary = rhs.m_vocabulary;
  return *this;
}

ModelElement::ModelElement()
{
  Construct();
}
ModelElement::ModelElement(ModelElement& rhs)
{
  this->m_name = rhs.m_name;
  this->m_initial = rhs.m_initial;
  this->m_params = rhs.m_params;
  this->m_regexp = rhs.m_regexp;
  this->m_return = rhs.m_return;
  this->m_size = rhs.m_size;
  this->m_time = rhs.m_time;
  this->m_type = rhs.m_type;
  this->m_units = rhs.m_units;
  this->m_vocabulary = rhs.m_vocabulary;
}
ModelElement::ModelElement(const ModelElement& rhs)
{
  m_name = rhs.m_name;
  m_initial = rhs.m_initial;
  m_params = rhs.m_params;
  m_regexp = rhs.m_regexp;
  m_return = rhs.m_return;
  m_size = rhs.m_size;
  m_time = rhs.m_time;
  m_type = rhs.m_type;
  m_units = rhs.m_units;
  m_vocabulary = rhs.m_vocabulary;
}

void
ModelElement::Construct()
{
  m_name = "NOT SET";
}
ModelElement::~ModelElement()
{
//  std::cout <<"OOOOOOOOOOOPS! KILLING" << m_name <<std::endl;
}

void
ModelElement::addAttribute(std::string name, std::string value)
{
  if (strcmp(value.c_str(), "EMPTY") != 0)
    {
      if (strcmp(name.c_str(), "units") == 0)
        {
          setUnits(value);

        }
      else if (strcmp(name.c_str(), "size") != 0)
        {

          uint64_t t = strtoul(value.c_str(), NULL, 0);
          if (errno)
            {
              std::cout << " ERROR CONVERTING" << std::endl;
            }
          else
            {
              setSize(t);
            }
        }
      else if (strcmp(name.c_str(), "initial") != 0)
        {
          uint64_t t = strtoul(value.c_str(), NULL, 0);
          if (errno)
            {
              std::cout << " ERROR CONVERTING" << std::endl;
            }
          else
            {
              setInitial(t);
            }

        }
      else if (strcmp(name.c_str(), "name") != 0)
        {
          setName(value);
        }
      else if (strcmp(name.c_str(), "time") != 0)
        {
          setTime(value);
        }
      else if (strcmp(name.c_str(), "return") != 0)
        {
          setReturn(value);
        }
      else if (strcmp(name.c_str(), "regexp") != 0)
        {
          setRegexp(value);
        }
      else if (strcmp(name.c_str(), "param") != 0)
        {
          setParams(value);
        }
      else if (strcmp(name.c_str(), "uri") != 0)
        {
          setUri(value);
        }
      else
        {
          std::cout << "OOOOOOOOOOOPS!" << name << "X" << value << std::endl;
        }
    }
}
uint64_t
ModelElement::getInitial() const
{
  return m_initial;
}

void
ModelElement::setInitial(uint64_t initial)
{
  m_initial = initial;
}

std::string
ModelElement::getName() const
{
  return m_name;
}

void
ModelElement::setName(std::string name)
{
  m_name = name;
}

std::vector<std::string>
ModelElement::getParams() const
{
  return m_params;
}

void
ModelElement::setParams(std::string param)
{
  m_params.push_back(param);
}

std::string
ModelElement::getReturn() const
{
  return m_return;
}

void
ModelElement::setReturn(std::string _return)
{
  m_return = _return;
}

ModelVocabulary::ElementType
ModelElement::getType() const
{
  return m_type;
}

void
ModelElement::setType(ModelVocabulary::ElementType type)
{
  m_type = type;
  m_vocabulary = ModelVocabulary::getInstance().getVocabulary(m_type);
}

std::string
ModelElement::getUnits() const
{
  return m_units;
}

void
ModelElement::setUnits(std::string units)
{
  m_units = units;
}

std::string
ModelElement::getTime() const
{
  return m_time;
}

std::string
ModelElement::getParam(int param) const
{
  return m_params.at(param);
}

const int
ModelElement::getNParams()
{
  return m_params.size();
}

void
ModelElement::setTime(std::string time)
{
  this->m_time = time;
}

void
ModelElement::printElemet()
{
  std::cout << "element - [name:" << getName() << "|" << "type:" << getType()
      << "|" << "units:" << getUnits() << "|" << "initial:" << getInitial()
      << "|" << "size:" << getSize() << "|" << "time:" << getTime() << "|"
      << "regexp:" << getRegexp() << "|" << "uri:" << getUri() << "|"
      << "return:" << getReturn() << "|" << "params:";
  for (int i = 0; i < getNParams(); i++)
    {
      std::cout << getParam(i) << ",";
    }
  std::cout << "]" << std::endl;
}

std::string
ModelElement::getRegexp() const
{
  return m_regexp;
}

void
ModelElement::setRegexp(std::string regexp)
{
  m_regexp = regexp;
}

uint64_t
ModelElement::getSize() const
{
  return m_size;
}

void
ModelElement::setSize(uint64_t size)
{
  m_size = size;
}

std::string
ModelElement::getUri() const
{
  return m_uri;
}

void
ModelElement::setUri(std::string uri)
{
  m_uri = uri;
}

