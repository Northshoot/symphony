#ifndef SYM_RADIO_MODEL_H
#define SYM_RADIO_MODEL_H

#include <stdint.h>
#include <string>

#include "ns3/ptr.h"
#include "model-element.h"
#include "model-vocabulary.h"

namespace ns3 {
typedef std::map<std::string, Ptr<ModelElement> > UniqueElement;

class HardwareModel : public Object
{
public:
  static TypeId GetTypeId (void);
  HardwareModel();
  HardwareModel(std::string name);

  virtual  ~HardwareModel();

  Ptr<ModelElement>
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
protected:
    /**
     * The dispose method. Subclasses must override this method
     * and must chain up to it by calling Node::DoDispose at the
     * end of their own DoDispose method.
     */

  virtual void DoDispose (void);
private:
  void printUniqueElement(UniqueElement elem);
  inline UniqueElement& getUniqueElement(ModelVocabulary::ElementType type);
  inline void deleteElements(UniqueElement elem);
  void Constuct();
  bool init;

  UniqueElement m_properties;
  UniqueElement m_callbacks;
  UniqueElement m_calls;
  UniqueElement m_formats;
  UniqueElement m_sources;
  UniqueElement m_undefined;
  std::string m_name;
};
}
#endif //SYM_RADIO_MODEL_H
