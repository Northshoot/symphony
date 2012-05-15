/*
 * model-element.cc
 *
 *      Author: Laurynas Riliskis
 *      e-mail: laurynas.riliskis@ltu.se
 */

#include "model-element.h"
#include "model-vocabulary.h"

ModelElement::ModelElement()
{
}

ModelElement::~ModelElement()
{
  // TODO Auto-generated destructor stub
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
  return time;
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
  this->time = time;
}


