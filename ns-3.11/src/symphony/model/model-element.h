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

#include "ns3/object.h"
#include "model-vocabulary.h"

namespace ns3 {
class ModelElement : public Object
{

public:
  static TypeId GetTypeId (void);
  ModelElement();



  ModelElement(std::string name);

  void
  addAttribute(std::string, std::string);

  std::string
  getAttributeValue(std::string key);

  void
  printElement();

  ~ModelElement();
protected:
    /**
     * The dispose method. Subclasses must override this method
     * and must chain up to it by calling Node::DoDispose at the
     * end of their own DoDispose method.
     */

  void DoDispose (void);
private:
  typedef std::map<std::string, std::string> Attribute;
  std::string m_name;
  Attribute attribute;
  
};
}
#endif /* MODEL_ELEMENT_H_ */
