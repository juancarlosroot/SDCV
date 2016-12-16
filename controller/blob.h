#ifndef BLOB_H
#define BLOB_H

/*!
 * @name		Blob.hpp
 * @author		Fernando Hermosillo.
 * @brief		This file is part of Vehicle Detection and Classification System project.
 * @date		25/11/2016
 *
 * @version
 *	25/11/2016: Initial version.
 *  26/11/2016:
 */
#pragma once


/* ---------------------------*/
/*       Library Include       */
/* ---------------------------*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <opencv2/opencv.hpp>

/*!
 * @namespace	sdcv.
 * @brief		Vehicle Detection and Classification System.
 */
namespace sdcv {
    /*!
     * @class	Blob.
     * @brief	Used for getting blob features.
     */
    class Blob
    {
    public:
        // Constructor
        Blob(std::vector< cv::Point > contour, int area = -1);

        // Get methods
        cv::Point2f getCentroid( void );
        cv::Rect getBBox( void );
        int	getArea( void );
        double getNormArea(void);

        // Set methods
        void setBlob(std::vector< cv::Point > contour);
        void setNormArea(double normArea);

        // Action methods
        void print();
        void print( std::ofstream &file );

        // Destructor
        ~Blob(void);

    private:
        int area;
        double normArea;
        cv::Point2f centroid;
        cv::Rect bbox;
    };
}

#endif
