#ifndef TRACK_H
#define TRACK_H
/*!
 * @name		Track.hpp
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
#include "clasifier.h"

/*!
 * @namespace	sdcv.
 * @brief		Vehicle Detection and Classification System.
 */
namespace sdcv {

    /*!
     * @class	Track
     * @brief	This class saves each parameter that describes a tracked vehicle.
    */
    class Track {
    public:
        Track();

        /*!
         * @name	Track
         * @brief	Track class constructor
         *
         * @param newBlob:	sdcv::Blob	new blob to track
         */
        Track(sdcv::Blob newBlob);

        // Action method
        void print( std::ofstream &file );

        /*!
         * @name	~Track
         * @brief	Track class destructor
         */
        ~Track();



        /*!
         * PUBLIC ATRIBUTES
         */
        //!< @param	id: integer ID of track
        int id;

        //!< @param	bbox: cv::Rect current bounding box of object; used for display
        cv::Rect bbox;

        //!< @param	detectedCentroid: cv::Point2f currente detected centroid
        std::vector<cv::Point2f> detectedCentroid;

        //!< @param	predictedCentroid: cv::Point2f predicted centroid
        cv::Point2f predictedCentroid;

        //!< @param	estimatedCentroid: cv::Point2f corrected centroid using AKF
        std::vector<cv::Point2f> estimatedCentroid;

        //!< @param	AKF: cv::KalmanFilter adaptive Kalman filter object
        cv::KalmanFilter AKF;

        //!< @param	area: areas array
        std::vector<double> areas;

        //!< @param	normArea: array of normalized areas
        std::vector<double> normAreas;

        //!< @param	estimatedArea: estimated area
        double estimatedArea;

        //!< @param	velocity: estimated velocity in pixels/s
        double velocity;

        //!< @param	consecutiveBackwardDir: ?
        int consecutiveBackwardDir;

        //!< @param	totalFrames: number of frames since the track was first detected
        int totalFrames;

        //!< @param	totalVisibleFrames: total number of frames in which the track was detected (visible)
        int totalVisibleFrames;

        //!< @param	consInvisibleFrames: number of consecutive frames for which the track was not detected (invisible).
        int consInvisibleFrames;


    private:
        void KalmanFilterInit(void);

    };


    /*!
     * @name	newTrack
     * @brief	This function adds new tracks to the track list.
     *
     * @param tracks: 				Pointer std::vector<sdcv::Track> track list
     * @param unassignedDetections:	std::vector<sdcv::Blob> List of unassigned blobs.
     */
    void newTrack(
                    std::vector<sdcv::Track> *tracks,
                    std::vector<sdcv::Blob> unassignedDetections
                );


    /*!
     * @name	updateTrack
     * @brief	This function update the track list.
     *
     * @param tracks: 			Pointer std::vector<sdcv::Track> track list
     * @param assignments:		std::vector<sdcv::Blob> List of assigned blobs.
     * @param unassignedTracks:	Pointer std::vector<sdcv::Track> List of unassigned tracks.
     * @param unassignments:	std::vector<sdcv::Blob> List of unassigned blobs.
     * @param minVisibleCount:	Minimum visible count of frames in which an blob can be considered for a track.
     */
    void updateTrack(
                        std::vector<sdcv::Track> *tracks,
                        std::vector<sdcv::Blob> assignments,
                        std::vector<sdcv::Track> *unassignedTracks,
                        std::vector<sdcv::Blob> unassignments,
                        int minVisibleCount
                    );

    /*!
     * @name	deleteTrack
     * @brief	This function deletes tracks to the track list.
     *
     * @param tracks: 	Pointer std::vector<sdcv::Track> track list
     * @param unassignedDetections:	std::vector<sdcv::Blob> List of unassigned blobs.
     */
    void deleteTrack(
                        std::vector<sdcv::Track> *tracks,
                        sdcv::Classifier classifier,
                        int minVisibleCount,
                        int minInvisibleCount
                    );
}

#endif

/* ************** E N D   O F   F I L E ----------------- CINVESTAV GDL */
