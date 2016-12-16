#ifndef CLASIFIER_H
#define CLASIFIER_H

/*!
 * @name		Classifier.hpp
 * @author		Fernando Hermosillo.
 * @brief		This file is part of Vehicle Detection and Classification System project.
 * @date		07/12/2016
 *
 * @version
 *	07/12/2016: Initial version.
 *
 */

#pragma once
/* ---------------------------*/
/*       Library Include       */
/* ---------------------------*/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "blob.h"
#include "roi.h"


/*!
 * @namespace	sdcv.
 * @brief		Vehicle Detection and Classification System.
 */
namespace sdcv {

    /*!
     * @class	Classifier
     * @brief	This class has the purpose of managing each blob to track
    */
    class Classifier {
    public:
        Classifier();
        Classifier(int NbClasses, std::vector<double> thresholdValue, std::vector<std::string> className);

        void setNClasses(int NbClasses);
        void setClassName(int idx, std::string name);
        void setClassThresVal(int idx, double ThresVal);

        int getNClasses( void );
        std::string getClassName(int idx);
        int getCount(int idx);

        void update(int idx);
        void update(double value);

    private:
        std::vector<std::string> className;
        std::vector<int> count;
        std::vector<double> thresholdValue;
        int NbClasses;

        void save( void );
        void load( void );
    };
}

#endif
