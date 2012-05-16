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
  typedef std::vector< UniqueElement > ElementCollection;

  ModelElement
  createNewElement(std::string name);
  void
  Construct();
  void
  printKeyVal(UniqueElement map);
  //hash map for holding model elements
  //


  ///key is model name
  //<property units="Kb" size="514" initial="220" name="heap"/>
  //in example case "heap"

  /**
   * UniqueElement's are stored by name in hash map
   * Element is described by @ModelElement class
   * TODO: create ElementHelper for storing elements.
   */
  UniqueElement m_properties;
  UniqueElement m_callbacks;
  UniqueElement m_calls;
  UniqueElement m_formats;
  UniqueElement m_sources;
  ElementCollection m_elemets;
  std::string m_name;
};
#endif //SYM_RADIO_MODEL_H
