/*
 * model-vocabulary.h
 *
 *  Created on: May 15, 2012
 *      Author: lauril
 */

#ifndef MODEL_VOCABULARY_H_
#define MODEL_VOCABULARY_H_
#include <string>
#include <vector>
#include <map>



class ModelVocabulary
{
public:
  enum ElementType {
    PROPERTY,
    CALL,
    CALLBACK,
    FORMAT,
    SOURCE,
    UNDEFINED
  };

  static ModelVocabulary& getInstance();


  std::vector<std::string>
  getCallVocabulary() const
  {
    return call_vocabulary;
  }

  std::vector<std::string>
  getCallbackVocabulary() const
  {
    return callback_vocabulary;
  }

  std::vector<std::string>
  getFormatVocabulary() const
  {
    return format_vocabulary;
  }

  std::vector<std::string>
  getPropertyVocabulary() const
  {
    return property_vocabulary;
  }

  std::vector<std::string>
  getSourceVocabulary() const
  {
    return source_vocabulary;
  }

  std::vector<std::string>
  getTosFunctions() const
  {
    return tos_functions;
  }
  std::vector<std::string>
  getVocabulary(ElementType type) const;

private:
  ModelVocabulary();
  // Dont forget to declare these two. You want to make sure they
   // are unaccessable otherwise you may accidently get copies of
   // your singelton appearing.
   ModelVocabulary(const ModelVocabulary&); // Don't Implement
   ModelVocabulary& operator =(const ModelVocabulary&); // Don't implement

  void Constuct();
  std::vector<std::string> tos_functions;
  std::vector<std::string> property_vocabulary;
  std::vector<std::string> call_vocabulary;
  std::vector<std::string> callback_vocabulary;
  std::vector<std::string> format_vocabulary;
  std::vector<std::string> source_vocabulary;
  std::map< ElementType, std::vector<std::string> > element_vocabularies;


};

#endif /* MODEL_VOCABULARY_H_ */
