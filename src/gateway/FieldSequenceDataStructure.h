/*
 * FieldSequence.h
 *
 *  Created on: Mar 19, 2014
 *      Author: sebastian
 */

#ifndef FIELDSEQUENCE_H_
#define FIELDSEQUENCE_H_

#include <vector>
#include "FieldElement.h"
#include <memory>

using namespace dataStruct;

typedef std::vector<std::shared_ptr<FieldElement>> FieldSequence;

class FieldSequenceDataStructure{
    private:
        FieldSequence fieldSequence;
    public:
        FieldSequenceDataStructure(){
            fieldSequence = FieldSequence();
        }

        ~FieldSequenceDataStructure(){
            fieldSequence.clear();
        }

        /**
         *  Adds the given element to the sequence.
         */
        template<typename T>
        void pushField(T element){
            fieldSequence.push_back(element);
        }

        /**
         * Returnes first occurrence of specified type. The Element will not be deleted!
         */
        template<typename T>
        std::shared_ptr<T> getField(){
            std::shared_ptr<T> specificElement = NULL;
            for (int i = 0; i < fieldSequence.size(); i++) {
                std::shared_ptr<FieldElement> element = fieldSequence.at(i);
                if(std::dynamic_pointer_cast<T>(element) != NULL){
                    specificElement  = std::dynamic_pointer_cast<T>(element);
                    break;
                }
            }
            if(specificElement == NULL){
                throw cException("Specified FieldElement not found in FieldSequenceDataStructure!");
            }
            return specificElement;
        }

        /**
         * Deletes all Elements of the sequence.
         */
        void clear(){
            fieldSequence.clear();
        }

        /**
         * Returns the number of elements within the datastructure
         */
        int size(){
            return fieldSequence.size();
        }
};


#endif /* FIELDSEQUENCE_H_ */
