#ifndef TRACKER_H
#define TRACKER_H

/*!
 * @name		Tracker.hpp
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
#include <numeric>

#include "blobList.h"
#include "roi.h"
#include "track.h"
#include "clasifier.h"
#include "munkres.h"

/*!
 * @namespace	sdcv.
 * @brief		Vehicle Detection and Classification System.
 */
namespace sdcv {

    /*!
     * @class	Tracker
     * @brief	This class has the purpose of managing each blob to track
    */
    class Tracker {
    public:
            /*!
             * @name	Track
             * @brief	Track class constructor
             * @param minVisibleCount:		M
             * @param minInvisibleCount:
             */
        Tracker(int minVisibleCount, int minInvisibleCount, int fps, sdcv::ROI roi);
        Tracker();

            /*!
             * @name	Track
             * @brief	Track class constructor
             * @param newBlob:	sdcv::Blob	new blob to track
             */
            sdcv::Track getTrack(int id);
            int getMinVisibleCount(void);
            int getMinInvisibleCount(void);


            /*!
             * @name	setMinVisibleCount
             * @brief
             * @param minVisibleCount:
             */
            void setMinVisibleCount(int minVisibleCount);

            /*!
             * @name	setMinInvisibleCount
             * @brief
             * @param minInvisibleCount:
             */
            void setMinInvisibleCount(int minInvisibleCount);

            /*!
             * @name	run
             * @brief
             * @param detectedBlobs:	std::vector<sdcv::Blob>
             */
            void run(std::vector<sdcv::Blob> detectedBlobs, sdcv::Classifier classifier);


            /*!
             * @name	~Track.
             * @brief	Track class destructor.
             */
            ~Tracker();

    private:
        //!< Minimum visible frame count that a blob has to have to add as a track it.
        int minVisibleCount;

        //!< Minimum invisible frame count that a blob has to have to delete it.
        int minInvisibleCount;

        //!< Current assigned ID.
        int currentID;

        //!< Vector of assigned tracks
        std::vector<sdcv::Track> assignedTracks;	// Optional

        //!< Vector of unassigned tracks
        std::vector<sdcv::Track> unassignedTracks;	// Optional

        //!< Vector of tracks
        std::vector<sdcv::Track> tracks;	// This or the two above

        //!< List of blobs
        sdcv::BlobList blobLst;

        //!< Initial state
        bool init;

        //! < Frames per second
        int fps;

        //! < False positive ID
        std::vector<int> FP_ID;

        //!< ID
        int ID;

        //< Region of interest object
        sdcv::ROI roi;

        int FrameCountDebug;

        cv::Mat temp1;
        cv::Mat temp2;
        cv::Mat temp3;
        cv::Mat temp4;
        cv::Mat temp5;

        /*!
        * @name	add
        * @brief	Track class constructor
        * @param newBlob:	sdcv::Blob	new blob to track
        */
        void add(std::vector<sdcv::Blob> detectedBlobs, std::vector<int> unassignedDetections);


        /*!
        * @name	update.
        * @brief	Update tracks.
        * @param assignedBlobs:	std::vector<sdcv::Blob>	a vector of assigned blobs.
        */
        void update(std::vector<sdcv::Blob> detectedBlobs, std::vector<cv::Point> assignments, std::vector<int> unassignedTracks);


        /*!
         * @name	erease.
         * @brief	Deletes tracks and increase the vehicle count according to its class.
         * @param classifier:	sdcv::Classifier
         */
        void erease(sdcv::Classifier classifier);


        /*!
         * @name	distance
         * @brief	This method computes a distance between the location of a detected object and a predicted location.
         *			It takes into account the covariance of the predicted state and the process noise.
         * @param AKF:			Input, Kalman filter object to get the distance
         * @param centroids:	Input, List of detected centroids.
         * @param CostMatrix:	Output, The cost matrix.
         */
        void distance(cv::KalmanFilter AKF, cv::Mat centroids, cv::OutputArray CostMatrix);


        /*!
         * @name	getAssigmentCostMatrix
         * @brief	This method compute the cost matrix for each detected centroid and each tracked centroid.
         * @param none.
         */
        cv::Mat getAssigmentCostMatrix(void);

        /*!
         * @name	assignamentProblemSolver
         * @brief	This method solves the assignament problem.
         * @param CostMatrix:			Input,
         * @param assignments:			Output,
         * @param unassignedTracks:		Output,
         * @param unassignedDetections:	Output,
         */
        void assignamentProblemSolver(cv::Mat CostMatrix, std::vector<cv::Point> &assignments, std::vector<int> &unassignedTracks, std::vector<int> &unassignedDetections);
    };
}

#endif
