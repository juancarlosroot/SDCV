
#include "clasifier.h"
/*!
 * @name		Classifier.cpp
 * @author		Fernando Hermosillo.
 * @brief		This file is part of Vehicle Detection and Classification System project.
 * @date		07/12/2016
 *
 * @version
 *	07/12/2016: Initial version.
 *
 */

namespace sdcv {
    Classifier::Classifier() {}

    Classifier::Classifier(int NbClasses, std::vector<double> thresholdValue, std::vector<std::string> className) {
        CV_Assert(NbClasses == thresholdValue.size() && NbClasses == className.size());

        this->NbClasses = NbClasses;
        this->thresholdValue = thresholdValue;
        this->count = std::vector<int>(NbClasses, 0);
        this->className = className;
    }

    void Classifier::setNClasses(int NbClasses) {
        this->NbClasses = NbClasses;
        className.clear();
        count.clear();
    }

    void Classifier::setClassName(int idx, std::string className) {
        if( idx < count.size() ) this->className.at(idx) = className;
    }

    void Classifier::setClassThresVal(int idx, double ThresVal) {
        if( idx < count.size() ) this->thresholdValue.at(idx) = ThresVal;
    }

    int Classifier::getNClasses( void ) { return NbClasses; }

    std::string Classifier::getClassName(int idx) {
        if( idx < count.size() ) return this->className.at(idx);
        else return "";
    }

    int Classifier::getCount(int idx) {
        if( idx < count.size() ) return this->count.at(idx);
        return -1;
    }

    void Classifier::update(int idx) {
        if( idx < count.size() ) this->count.at(idx)++;
    }

    void Classifier::update(double value) {
        std::vector<int>::iterator cntIt = count.begin();
        for(std::vector<double>::iterator it = thresholdValue.begin(); it != thresholdValue.end() - 1; ++it, ++cntIt) {
            if(value < *it) (*cntIt)++;
        }
    }

    void save( void ) {

    }

    void load( void ) {

    }
}
