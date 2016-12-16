#ifndef DETECTOR_H
#define DETECTOR_H

/*!
 * @name		Detector.hpp
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
    const int MinBlobArea = 100;
    /*!
     * @class	Detector.
     * @brief	Used for detecting objects.
     */
    class Detector {
    public:
        // Constructor
        Detector();
        Detector(int MinimumBlobArea, int MaximumBlobArea, bool bDrawID = false, bool bDrawBBox = false);

        // Get methods
        std::vector<sdcv::Blob> getBlobList( void );

        // Set methods
        void setMOG(cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG);
        void setErodeKernel(cv::Mat kernel);
        void setDilateKernel(cv::Mat kernel);
        //inline void setROI(cv::InputArray RoiMask);

        void setMinimumBlobArea(int MinimumBlobArea);
        void setMaximumBlobArea(int MaximumBlobArea);
        void setDrawBBox(bool bDrawBBox);
        void setDrawLabel(bool bDrawLabel);
        void setAreaOutput( bool bAreaOutput );
        void setCentroidOutput( bool bCentroidOutput );

        void setROI(sdcv::ROI roi);
        void setOclussion(bool bOclussionHandling);
        void setOclussionParam(std::vector<double> Params); // laneWidthThresC1, normAreaThresC1, laneWidthThresC2, overlapRatio

        // Action methods
        bool isReady( void );
        void detect(cv::Mat frame, cv::OutputArray mask);
        void draw( cv::Mat frame );

        // Destructor
        ~Detector();


    private:
        cv::Ptr<cv::BackgroundSubtractorMOG2> BgSubMoG;
        std::vector<sdcv::Blob> blobs;

        cv::Mat erodeKernel;
        cv::Mat dilateKernel;

        double learningRate;

        bool bBBox;
        bool bLabel;
        bool bCentroid;
        bool bArea;
        bool bOclussionHandling;

        int MinimumBlobArea;
        int MaximumBlobArea;

        std::vector<double> oclussionParams;
        sdcv::ROI roi;

        int NbFrame;
        int j;

        void oclussionHandling(cv::InputArray mask, cv::OutputArray maskOclussion);
        void getBlobs(cv::InputArray mask, cv::OutputArray blobMask);
    };
};

#endif
