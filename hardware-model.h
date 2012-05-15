#ifndef SYM_RADIO_MODEL_H
#define SYM_RADIO_MODEL_H

#include <stdint.h>
#include <string>
#include <google/dense_hash_map>
#include "model-element.h"
#include "model-vocabulary.h"

using google::dense_hash_map;

class HardwareModel
{
public:
  HardwareModel();
  HardwareModel(std::string name);
  virtual
  ~HardwareModel();

  ModelElement
  getElement(ModelVocabulary::ElementType et, std::string name);
  void
  addElement(ModelVocabulary::ElementType type, std::string elemenName,
      std::string name, std::string value);

  void
  printModel(void);

private:
  typedef dense_hash_map<std::string, ModelElement *> UniqueElement;
  typedef std::vector< UniqueElement> ElementCollection;

  ModelElement
  createNewElement(std::string name);
  void
  Construct();
  void
  printKeyVal(dense_hash_map<std::string, std::string> map);
  //hash map for holding model elements
  //
  UniqueElement m_properties;
  UniqueElement m_calls;

  ///key is model name
  //<property units="Kb" size="514" initial="220" name="heap"/>
  //in example case "heap"

  /**
   * Element Collection holds all possible elelent's
   * Accessor is by type m_elemets[PROPERTY]
   * The returned map accessor is by name of the element
   * element["start"]
   * In its turn, each unique element has attributes
   * defined in vocabulary, however
   * TODO: there is no safe guard, so the attributes need to exis uppon they
   * access.
   */
  ElementCollection m_elemets;
  std::string m_name;
};
#endif //SYM_RADIO_MODEL_H
