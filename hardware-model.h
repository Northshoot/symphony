/*
 * hardware-model.h
 *
 *  Created on: May 4, 2012
 *      Author: lauril
 */

#ifndef HARDWARE_MODEL_H_
#define HARDWARE_MODEL_H_

#include <stdint.h>
#include <string>
class HardwareModel
{
public:

  virtual
  ~HardwareModel();

  /**
   * returns the name of the model
   */
  virtual std::string
  getModelName() const =0;

  /**
   * setters and getters for the model
   */
  virtual void
  addModelProperty(std::string key, std::string value) =0;
  virtual std::string
  getModelProperty(std::string key) =0;
  virtual uint32_t
  getSizeOfProperty() =0;

  virtual std::string
  getModelCall(std::string key) =0;
  virtual void
  addModelCall(std::string key, std::string value) =0;
  virtual uint32_t
  getSizeOfCall() =0;

  virtual std::string
  getModelCallBack(std::string key) =0;
  virtual void
  addModelCallBack(std::string key, std::string value) =0;
  virtual uint32_t
  getSizeOfCallBack()=0;

  virtual std::string
  getModelFormat(std::string key) =0;
  virtual void
  addModelFormat(std::string key, std::string value) =0;
  virtual uint32_t
  getSizeOfFormat() =0;

  virtual std::string
  getModelSource(std::string key) =0;
  virtual void
  addModelSource(std::string key, std::string value) =0;
  virtual uint32_t
  getSizeOfSource() =0;
  
  /**
   * pretty model print
   */
  virtual void
  printModel()  = 0;

};

#endif /* HARDWARE_MODEL_H_ */
