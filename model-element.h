/*
 * model-element.h
 *
 *  Created on: May 15, 2012
 *      Author: Laurynas Riliskis
 *      e-mail: laurynas.riliskis@ltu.se
 *
 *  Class for handling elements in the model.
 *  This is general class therefore some of the attributes may not be initialized.
 *  TODO: need a good way to handle the exception when user tries to access some
 *  attribute which does not to belong to specific element.
 */

#ifndef MODEL_ELEMENT_H_
#define MODEL_ELEMENT_H_
#include <string>
#include <stdint.h> 
#include <vector>
#include "model-vocabulary.h"


class ModelElement
{
public:
  ModelElement();
  virtual
  ~ModelElement();
  uint64_t
  getInitial() const;
  void
  setInitial(uint64_t initial);
  std::string
  getName() const;
  void
  setName(std::string name);
  /**
   * return param with some number
   */
  std::string
  getParam(int param) const;
  std::vector<std::string>
  getParams() const;
  void
  setParams(std::string param);
  /**
   * Return number of parameters
   */
  int const
  getNParams();
  std::string
  getReturn() const;
  void
  setReturn(std::string _return);
  ModelVocabulary::ElementType
  getType() const;
  void
  setType(ModelVocabulary::ElementType type);
  std::string
  getUnits() const;
  void
  setUnits(std::string units);
  std::string
  getTime() const;
  void
  setTime(std::string time);
  

  private:
  /***
   * Hardware models element class
   * each element can only have one instance of the the parameters
   * expect the m_params, which is the list of the parameters
   */
  ModelVocabulary::ElementType m_type;
  std::string m_name;
  std::vector<std::string> m_params;
  std::string m_return;
  std::string m_units;
  std::string time;
  uint64_t m_initial;
  std::vector<std::string> m_vocabulary;
  
};

#endif /* MODEL_ELEMENT_H_ */
