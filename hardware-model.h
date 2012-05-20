#ifndef SYM_RADIO_MODEL_H
#define SYM_RADIO_MODEL_H

#include <stdint.h>
#include <string>
#include "model-element.h"
#include "model-vocabulary.h"

typedef std::map<std::string, ModelElement * > UniqueElement;
class HardwareModel
{
public:
  HardwareModel();
  HardwareModel(std::string name);

  virtual
  ~HardwareModel();

  ModelElement *
  getElement(ModelVocabulary::ElementType et, std::string name);

  void
  setName(std::string name);

  void
  addElementAttribute(ModelVocabulary::ElementType type, std::string elemenName,
      std::string name, std::string value);

  void
  addElement(ModelVocabulary::ElementType type,std::string elemenName );


  void
  printModel(void);

private:
  void printUniqueElement(UniqueElement elem);
  inline UniqueElement& getUniqueElement(ModelVocabulary::ElementType type);
  inline void deleteElements(UniqueElement elem);

  UniqueElement m_properties;
  UniqueElement m_callbacks;
  UniqueElement m_calls;
  UniqueElement m_formats;
  UniqueElement m_sources;
  UniqueElement m_undefined;
  std::string m_name;
};
#endif //SYM_RADIO_MODEL_H
