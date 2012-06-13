/*
 * ModelVocabulary.cpp
 *
 *  Created on: May 15, 2012
 *      Author: lauril
 */

#include "model-vocabulary.h"


ModelVocabulary::ModelVocabulary()
{
  Constuct();

}

ModelVocabulary&
ModelVocabulary::getInstance()
{
  static ModelVocabulary instance;
  return instance;
}
std::vector<std::string>
ModelVocabulary::getVocabulary(ElementType type) const
{
  //TODO: this is not fail safe!
  //element may not exist
  return (element_vocabularies.find(type))->second;
}

void
ModelVocabulary::Constuct()
{
  //Definition of vocabulary
  property_vocabulary.push_back("units");
  property_vocabulary.push_back("size");
//  property_vocabulary.push_back("name");
  property_vocabulary.push_back("initial");
  element_vocabularies[ModelVocabulary::PROPERTY]=property_vocabulary;

  call_vocabulary.push_back("name");
  call_vocabulary.push_back("time");
  call_vocabulary.push_back("return");
  call_vocabulary.push_back("params");
  element_vocabularies[ModelVocabulary::CALL]=call_vocabulary;

  callback_vocabulary.push_back("return");
  callback_vocabulary.push_back("time");
//  callback_vocabulary.push_back("name");
  callback_vocabulary.push_back("params");

  element_vocabularies[ModelVocabulary::CALLBACK]=callback_vocabulary;

  format_vocabulary.push_back("regexp");
  element_vocabularies[ModelVocabulary::FORMAT]=format_vocabulary;

  source_vocabulary.push_back("type");
  source_vocabulary.push_back("uri");
  element_vocabularies[ModelVocabulary::SOURCE]=source_vocabulary;


}


