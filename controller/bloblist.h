#ifndef BLOBLIST_H
#define BLOBLIST_H


/*!
 * @name		BlobList.hpp
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
#include "opencv2/opencv.hpp"
#include "blob.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>


/*!
 * @namespace	sdcv.
 * @brief		Vehicle Detection and Classification System.
 */
namespace sdcv {
    /*!
     * @class	BlobList.
     * @brief	Used for creating a blob list.
     */
    class BlobList {
    public:
        // Constructor
        BlobList();
        BlobList(std::vector<sdcv::Blob> blobs);

        // Get methods
        std::vector<   int   >	getAreas( void );
        std::vector<cv::Point2f> getCentroids( void );
        std::vector<cv::Rect >	getBBoxes( void );
        int getLen( void );
        // Set methods


        // Action methods
        void add(sdcv::Blob blob);
        void clear( void );

        // Destructor
        ~BlobList();


    private:
        std::vector<int>		 areas;
        std::vector<cv::Point2f> centroids;
        std::vector<cv::Rect >	 bboxes;
        int len;
    };

};

#endif
