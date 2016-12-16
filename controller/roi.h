#ifndef ROI_H
#define ROI_H

/*!
 * @name		ROI.hpp
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
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "drawing.h"
#include "blob.h"
#include <QDebug>
#include <QString>




/*!
 * @namespace 	sdcv.
 * @brief 		Vehicle Detection and Classification System.
 */
namespace sdcv {
    typedef struct {
        int NbLineLanes;
        cv::Mat lineLane; 					// set of division lines for each lane
        std::vector< double > m_lineLanes; 	// slope for each lane's division line
        std::vector< double > b_lineLanes; 	// intersection for each lane's division line
        std::vector< cv::Mat > DL_mask;
    }DivLaneLine_t;

    typedef enum {
        ROI_TEST_VERTEX = 0,
        ROI_TEST_DIV_LINES,
        ROI_TEST_LINE_DETECTION
    }eROItest;

    /*!
     * @class 	ROI.
     * @brief	Used for setting and characterizing the region of interest (ROI).
     */
    class ROI {
    private:
        //
        cv::String name;

        // Region of Interest
        std::vector<cv::Point> vertices;
        cv::Rect bbox;
        int area;
        cv::Mat mask;

        // Dividing lanes' lines
        int NbLineLanes;
        cv::Mat lineLane; 					// set of division lines for each lane
        std::vector< double > m_lineLanes; 	// slope for each lane's division line
        std::vector< double > b_lineLanes; 	// intersection for each lane's division line
        std::vector< cv::Mat > DL_mask;
        std::vector< cv::Mat > DL_green;

        // Line detection
        std::vector< cv::Point > lineDetection;
        cv::Point2f cLineDetection;
        cv::Mat LineArea;

        int NbRegions;


        void getRoiPoly( cv::OutputArray frame, std::vector<cv::Point> vertex = std::vector<cv::Point>());
        void save( void );
        bool load( void );


    public:
        // Constructor
        ROI();
        ROI( cv::String name );

        // Get methods
        cv::Rect getBbox( void );
        std::vector<cv::Point> getVertices( void );
        cv::Mat getMask( void );
        int getArea(void);

        DivLaneLine_t getLaneData( void );
        int getNumLanes( void );
        cv::Mat getDivLineLane( void );
        std::vector< double > getSlopeLane( void );
        std::vector< double > getIntersecLane( void );
        cv::Mat getDivLaneMask(int Nb);
        std::vector< cv::Mat > getDivLaneMask( void );


        std::vector< cv::Point > getLineDetection( void );
        cv::Point2f getCenterLineDetection( void );

        // Set methods
        void setVertices(std::vector<cv::Point> vertices);
        void setName(cv::String name);

        // Action methods
        void create(cv::String videonamePath, int NbDivLines = 4, bool bLoad = false);
        void apply(cv::InputArray frame, cv::OutputArray image);

        // Testing methods
        void testing(eROItest en2Test, cv::Mat frame, std::vector<cv::Point> input);

        // Destructor
        ~ROI();

    };
};

#endif
