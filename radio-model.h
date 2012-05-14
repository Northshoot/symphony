#ifndef SYM_RADIO_MODEL_H
#define SYM_RADIO_MODEL_H

#include <stdint.h>
#include <string>
#include <google/dense_hash_map>
#include "hardware-model.h"

using google::dense_hash_map;

class RadioModel : public HardwareModel
{
public:
  RadioModel();
  RadioModel(std::string name);
  virtual
  ~RadioModel();

  void
  addModely(std::string key, std::string value);
  //inherited from base model class
  virtual std::string
  getModelName() const;
  virtual void
  addModelProperty(std::string key, std::string value);
  virtual std::string
  getModelProperty(std::string key);
  virtual uint32_t
  getSizeOfProperty();

  virtual std::string
  getModelCall(std::string key);
  virtual void
  addModelCall(std::string key, std::string value);
  virtual uint32_t
  getSizeOfCall();

  virtual std::string
  getModelCallBack(std::string key);
  virtual void
  addModelCallBack(std::string key, std::string value);
  virtual uint32_t
  getSizeOfCallBack();

  virtual std::string
  getModelFormat(std::string key);
  virtual void
  addModelFormat(std::string key, std::string value);
  virtual uint32_t
  getSizeOfFormat();

  virtual std::string
  getModelSource(std::string key);
  virtual void
  addModelSource(std::string key, std::string value);
  virtual uint32_t
  getSizeOfSource();

  virtual void
  printModel(void);

private:
  void
  Construct();
  void
  printKeyVal(dense_hash_map<std::string, std::string> map);
  //hash map for holding model description

  dense_hash_map<std::string, std::string> m_property;
  dense_hash_map<std::string, std::string> m_call;
  dense_hash_map<std::string, std::string> m_callback;
  dense_hash_map<std::string, std::string> m_format;
  dense_hash_map<std::string, std::string> m_source;

  std::string m_name;
};
#endif //SYM_RADIO_MODEL_H
