/* ---------------------------*/
/*       Library Include       */
/* ---------------------------*/
#include "tracker.h"
#include <math.h>


std::ofstream outfile("/stdout.txt");
#define out outfile	// std::cout

namespace sdcv {
    /*-------------------------------------*/
    /*		Private Prototype Function		*/
    /*-------------------------------------*/

    /*--------------------------------*/
    /*     Class reference method     */
    /*--------------------------------*/
    // Constructor ------------------------------------------------------------------------------------
    Tracker::Tracker(){}
    Tracker::Tracker(int minVisibleCount, int minInvisibleCount, int fps, sdcv::ROI roi) {
        this->minVisibleCount = minVisibleCount;
        this->minInvisibleCount = minInvisibleCount;
        this->fps = fps;
        this->roi = roi;
        this->ID = 0;
        this->FP_ID.push_back(0);
        this->init = false;


        FrameCountDebug = 0;

    }

    // Get methods ------------------------------------------------------------------------------------
    sdcv::Track Tracker::getTrack(int id) {
        if( id < (int)this->tracks.size() ) return tracks.at(id);
        else return sdcv::Track();
    }
    int Tracker::getMinVisibleCount(void) { return minVisibleCount; }
    int Tracker::getMinInvisibleCount(void) { return minInvisibleCount; }

    // Set methods ------------------------------------------------------------------------------------
    void Tracker::setMinVisibleCount(int minVisibleCount) { this->minVisibleCount = minVisibleCount; }
    void Tracker::setMinInvisibleCount(int minInvisibleCount) { this->minInvisibleCount = minInvisibleCount; }

    // Action methods ---------------------------------------------------------------------------------
    #define SDCV_TRACKING_DEBUG
    void Tracker::run( std::vector<sdcv::Blob> detectedBlobs, sdcv::Classifier classifier) {
        #ifdef SDCV_TRACKING_DEBUG
        out << std::endl << std::endl << "[TRACKING CLASS BEGIN]-------------------------------------------" << std::endl;
        out << "Frame: " << FrameCountDebug << std::endl;
        #endif

        blobLst = sdcv::BlobList(detectedBlobs);

        int NbDetections = (int)detectedBlobs.size();
        int NbTracks = (int)tracks.size();

        if( NbTracks == 0 ) init = false;
        if( NbDetections == 0 ) return;

        #ifdef SDCV_TRACKING_DEBUG
        out << "Number of tracks: " << NbTracks << std::endl;
        out << "Number of detections: " << NbDetections << std::endl;
        #endif

        if( init == false ) {
            for(std::vector<sdcv::Blob>::iterator it = detectedBlobs.begin(); it != detectedBlobs.end(); ++it) {
                tracks.push_back( sdcv::Track(*it) );
                #ifdef SDCV_TRACKING_DEBUG
                out << "New track was added!" << std::endl;
                #endif

            }

            init = true;

            #ifdef SDCV_TRACKING_DEBUG
            FrameCountDebug++;
            out << "[TRACKING CLASS END]-------------------------------------------" << std::endl;
            //cv::waitKey();
            #endif
            return;
        }

        cv::Mat CostMatrix = getAssigmentCostMatrix();

        /* Solve the assignment problem --------------------------------------------------------*/
        std::vector<cv::Point> assignments;
        std::vector<int> unassignedTracks, unassignedDetections;
        assignamentProblemSolver(CostMatrix, assignments, unassignedTracks, unassignedDetections);

        /* Update tracks -----------------------------------------------------------------------*/
        update(detectedBlobs, assignments, unassignedTracks);

        /* Delete tracks -----------------------------------------------------------------------*/
        erease( classifier );

        /* Create new tracks -------------------------------------------------------------------*/
        add(detectedBlobs, unassignedDetections);

        /* Clear blobs list before exiting */
        blobLst.clear();

        #ifdef SDCV_TRACKING_DEBUG
        out << "[TRACKING CLASS END]-------------------------------------------" << std::endl;
        FrameCountDebug++;
//        cv::waitKey();
        #endif
    }


    // Private methods --------------------------------------------------------------------------------
    void Tracker::add(std::vector<sdcv::Blob> detectedBlobs, std::vector<int> unassignedDetections) {

        #ifdef SDCV_TRACKING_DEBUG
        out << "[Add New Tracks Begin] -------------------" << std::endl;
        out << "Number of new tracks: " << unassignedDetections.size() << std::endl << std::endl;
        #endif

        // Add new tracks
        for(std::vector<int>::iterator it = unassignedDetections.begin(); it != unassignedDetections.end(); ++it) {
            tracks.push_back( sdcv::Track(detectedBlobs.at(*it)) );

            #ifdef SDCV_TRACKING_DEBUG
            out << "Unassigned detection [" << *it << "] has been added to track!" << std::endl;
            detectedBlobs.at(*it).print( out );
            out << std::endl;
            #endif
        }

        #ifdef SDCV_TRACKING_DEBUG
        out << "[Add New Tracks End] -------------------" << std::endl;
        #endif
    }


    void Tracker::update(std::vector<sdcv::Blob> detectedBlobs, std::vector<cv::Point> assignments, std::vector<int> unassignedTracks) {
        int trackIdx, detectionIdx; // Idexes for matched track and detection.
        float Th_OR = 0.3;
        bool test;

        #ifdef SDCV_TRACKING_DEBUG
        out << "[Update Tracks Begin] --------------------" << std::endl;
        out << "Number of assigments detected: " << assignments.size() << std::endl;
        out << "Number of assigments not detected: " << unassignedTracks.size() << std::endl << std::endl;
        #endif
        /* Update assigned tracks */
        for(std::vector<cv::Point>::iterator it = assignments.begin(); it != assignments.end(); ++it) {
            double occlusionRate = 0.001;

            // Set the current blob and track that were matched.
            trackIdx	 = it->x;
            detectionIdx = it->y;
            std::vector<sdcv::Blob>::iterator blob = std::next(detectedBlobs.begin(), detectionIdx);
            std::vector<sdcv::Track>::iterator matchedTrack = std::next(tracks.begin(), trackIdx);

            #ifdef SDCV_TRACKING_DEBUG
            out << "Blob matched: " << detectionIdx << std::endl;
            blob->print( out );
            out << std::endl << "Track matched: " << trackIdx << std::endl;
            matchedTrack->print( out );
            #endif

            if(matchedTrack->id != 0 ) {
                double prevNormArea = matchedTrack->normAreas.back();
                if(prevNormArea < blob->getNormArea()) occlusionRate = 1 - (prevNormArea/(double)blob->getNormArea());

                #ifdef SDCV_TRACKING_DEBUG
                out << std::endl << "Occlusion Rate: " << occlusionRate << std::endl;
                out << "Kalman Filter: Noise Covariances have been updated on condition: ";
                #endif

                if(occlusionRate < Th_OR) {
                    // the measurement result will be trusted more than predicted one
                    cv::setIdentity(matchedTrack->AKF.processNoiseCov, cv::Scalar::all((1 - occlusionRate + 1e-50)));
                    cv::setIdentity(matchedTrack->AKF.measurementNoiseCov, cv::Scalar::all((occlusionRate + 1e-50)));

                    #ifdef SDCV_TRACKING_DEBUG
                    out << "1" << std::endl;
                    #endif
                } else {
                    // The system will trust the predicted result completely
                    cv::setIdentity(matchedTrack->AKF.processNoiseCov, cv::Scalar::all((1e-50)));
                    cv::setIdentity(matchedTrack->AKF.measurementNoiseCov, cv::Scalar::all((100)));

                    #ifdef SDCV_TRACKING_DEBUG
                    out << "2" << std::endl;
                    #endif
                }

            }

            // Correct the estimate of the object's location using the new detection.
            cv::Mat correctedCentroidMat = matchedTrack->AKF.correct( cv::Mat(blob->getCentroid()) );
            cv::Point2f correctedCentroid(correctedCentroidMat.at<float>(0,0), correctedCentroidMat.at<float>(2,0));

            // Update detected centroid.
            matchedTrack->detectedCentroid.push_back( blob->getCentroid() );
            #ifdef SDCV_TRACKING_DEBUG
            out << std::endl << "Corrected Centroid: " << correctedCentroid << std::endl;
            #endif

            // Update total frames.
            matchedTrack->totalFrames++;
            #ifdef SDCV_TRACKING_DEBUG
            out << "Total frames: " << matchedTrack->totalFrames << std::endl;
            #endif

            if( occlusionRate < Th_OR ) {
                // Update velocity
                int endIdx = matchedTrack->estimatedCentroid.size();
                float x1 = matchedTrack->estimatedCentroid.at(endIdx - 2).x;
                float y1 = matchedTrack->estimatedCentroid.at(endIdx - 2).y;
                float x2 = correctedCentroid.x;
                float y2 = correctedCentroid.y;
                float velocity = sqrt(pow((x1 - x2),2)+pow((y1 - y2),2))*fps; // sqrt(...)/dt -> dt = 1/fps

                if( y2 > y1 ) {
                    matchedTrack->velocity = velocity;
                    matchedTrack->consecutiveBackwardDir = 0;
                } else {
                    matchedTrack->velocity = velocity*(-1);
                    matchedTrack->consecutiveBackwardDir++;
                }

                // Replace predicted bounding box with detected bounding box
                matchedTrack->bbox = blob->getBBox();

                // Replace predicted centroid with corrected centroid
                matchedTrack->estimatedCentroid.at(matchedTrack->totalVisibleFrames) = correctedCentroid;

                // Update Track's area
                matchedTrack->areas.push_back( blob->getArea() );
                if( blob->getNormArea() > .06) {
                    if( matchedTrack->normAreas.back() == 0.00 ) matchedTrack->normAreas.back() = blob->getNormArea();
                    else matchedTrack->normAreas.push_back( blob->getNormArea() );
                }

                if( (matchedTrack->id == 0) && (matchedTrack->consecutiveBackwardDir != 0) ) test = true;
                else {
                    // Update visibility.
                    matchedTrack->totalVisibleFrames++;
                    matchedTrack->consInvisibleFrames = 0;
                }

            } /* occlusionRate < Th_OR */

            // Compute estimated area
            #ifdef SDCV_TRACKING_DEBUG
            out << std::endl << ">>>>> Compute estimated area for blob: " << detectionIdx << std::endl;
            out << "Centroid: " << blob->getCentroid() << std::endl << "Line detection: " <<  roi.getCenterLineDetection() << std::endl;
            #endif

            bool in = (blob->getCentroid().y < roi.getCenterLineDetection().y); // See if the object is before line detection
            if( in ) {
                #ifdef SDCV_TRACKING_DEBUG
                out << "It is before line detection" << std::endl;
                #endif

                if( (matchedTrack->id != 0) ) {
                    // Check whether the matched track had had a normalized area or not.
                    if (matchedTrack->estimatedArea == 0) {
                        matchedTrack->estimatedArea = matchedTrack->normAreas.back();
                        #ifdef SDCV_TRACKING_DEBUG
                        out << "New estimated area: " << matchedTrack->estimatedArea << std::endl;
                        #endif
                    } else  {
                        // This sum could be performance if it has a variable/vector that contains it in each track
                        double sumNormAreas = std::accumulate(matchedTrack->normAreas.begin(), matchedTrack->normAreas.end(), 0.0f);
                        matchedTrack->estimatedArea = sumNormAreas/(double)matchedTrack->normAreas.size();

                        #ifdef SDCV_TRACKING_DEBUG
                        out << "Norm areas: " << cv::format(matchedTrack->normAreas,0) << std::endl;
                        out << "Sum of Norm areas: " << sumNormAreas << std::endl;
                        out << "Estimated area: " << matchedTrack->estimatedArea << std::endl;
                        #endif
                    }
                }
            }
            #ifdef SDCV_TRACKING_DEBUG
            else out << "It is after line detection" << std::endl;
            out << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl << std::endl;
            #endif

            // Check overlapping between matched track and all the tracks
            bool overlapFlag = false;

            #ifdef SDCV_TRACKING_DEBUG
            out << std::endl << ">>>>> Check overlapping" << std::endl;
            int idxTrackDebug = 0;
            #endif

            for(std::vector<sdcv::Track>::iterator it = tracks.begin(); it != tracks.end(); ++it) {
                if(it != matchedTrack) {
                    double bbox_A_area = matchedTrack->bbox.area();
                    double bbox_B_area = it->bbox.area();
                    double unionArea = cv::Rect(matchedTrack->bbox & it->bbox).area();
                    double overlapRatio = unionArea/(double)(bbox_A_area + bbox_B_area);
                    double minRatio = unionArea/(double)(std::min(bbox_A_area, bbox_B_area));

                    #ifdef SDCV_TRACKING_DEBUG
                    out << "Minimum ratio [" << trackIdx << ", " << idxTrackDebug << "]: " << minRatio << std::endl;
                    #endif

                    if( (overlapRatio > 0.57) || (minRatio == 1) ) {
                        overlapFlag = true;

                        #ifdef SDCV_TRACKING_DEBUG
                        out << "There was an overlaping between matched track and: " << idxTrackDebug << std::endl;
                        #endif

                        if( it->id == 0 ) it->consInvisibleFrames = 100;
                        else if( matchedTrack->id == 0 ) matchedTrack->consInvisibleFrames = 100;
                        else {
                            if( matchedTrack->totalVisibleFrames > it->totalVisibleFrames ) it->consInvisibleFrames = 100;
                            else matchedTrack->consInvisibleFrames = 100;
                        }

                        break;
                    }
                }

                #ifdef SDCV_TRACKING_DEBUG
                idxTrackDebug++;
                #endif
            }

            #ifdef SDCV_TRACKING_DEBUG
            out << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl << std::endl;
            #endif

            //  Check if the object is a large vehicle created after line detection
            #ifdef SDCV_TRACKING_DEBUG
            out << std::endl << ">>>>> Check for a large vehicle created after line detection" << std::endl;
            out << "Vehicle: ";
            #endif

            bool cond = false;
            if( (matchedTrack->id == 0) && (matchedTrack->normAreas.back() > 1.2) && !in ) {
                matchedTrack->consInvisibleFrames = 100;
                cond = true;
            }
            #ifdef SDCV_TRACKING_DEBUG
            out << (cond ? "Large" : "no") << std::endl;
            out << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl << std::endl;
            #endif

            // Increment the next id
            #ifdef SDCV_TRACKING_DEBUG
            out << std::endl << ">>>>> Increment the next id" << std::endl;
            #endif

            if( (matchedTrack->id == 0) && (matchedTrack->totalVisibleFrames >= minVisibleCount) && (!cond) && (!overlapFlag) ) {
                if( FP_ID.back() != 0 ) {
                    matchedTrack->id = FP_ID.back();

                    #ifdef SDCV_TRACKING_DEBUG
                    out << "Matched ID was setted by FP" << std::endl;
                    out << "Track #" << trackIdx << " has new ID [" << FP_ID.back() << "]" << std::endl;
                    #endif

                    int length_id_FP = (int)FP_ID.size();
                    if( length_id_FP == 1 )  FP_ID.back() = 0;
                    else FP_ID.pop_back();
                } else {
                    this->ID++;

                    #ifdef SDCV_TRACKING_DEBUG
                    out << "Track #" << trackIdx << " has new ID [" << this->ID << "]" << std::endl;
                    #endif

                    matchedTrack->id = this->ID;
                }
            }
            #ifdef SDCV_TRACKING_DEBUG
            out << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl << std::endl;
            #endif
        } /* END FOR */

        /* Update unassigned tracks ----------------------------------------------------------------------*/
        #ifdef SDCV_TRACKING_DEBUG
        out << std::endl << ">>>>> Update unassigned tracks" << std::endl;
        #endif

        for(int i = 0; i < (int)unassignedTracks.size(); i++) {
            int unassignedInds = unassignedTracks.at(i);
            std::vector<sdcv::Track>::iterator unmatchedTrack = std::next(tracks.begin(), unassignedInds);

            unmatchedTrack->totalFrames++;
            if( unmatchedTrack->velocity < 0 ) unmatchedTrack->consecutiveBackwardDir++;

            // Find the indices of 'new' tracks with totalFrames equal to 2 and distance < 25
            std::vector<double> distances;
            for(std::vector<sdcv::Track>::iterator it = tracks.begin(); it != tracks.end(); ++it) {
                cv::Point2f tmp = it->predictedCentroid;
                float x1 = tmp.x;
                float y1 = tmp.y;
                float x2 = unmatchedTrack->estimatedCentroid.back().x;
                float y2 = unmatchedTrack->estimatedCentroid.back().y;
                double dist = sqrt(pow((x1-x2),2) + pow((y1-y2),2));
                if( dist == 0 ) dist = 100;
                distances.push_back( dist );
            }

            std::vector<double>::iterator minElementIt = std::min_element(distances.begin(), distances.end());
            int ind = (int)std::distance(distances.begin(), minElementIt);
            std::vector<sdcv::Track>::iterator minTrack = std::next(tracks.begin(), ind);

            #ifdef SDCV_TRACKING_DEBUG
            out << "Min element: " << *minElementIt << " at " << ind << std::endl;
            #endif

            cv::Mat distancesMat(distances), IdMat, totalFramesMat;
            for(std::vector<sdcv::Track>::iterator it = tracks.begin(); it != tracks.end(); ++it) {
                // IDs
                IdMat.push_back(it->id);

                // totalFrames
                totalFramesMat.push_back(it->totalFrames);
            }

            #ifdef SDCV_TRACKING_DEBUG
            out << "distances: " << std::endl << distancesMat << std::endl << std::endl;
            out << "ID Tracks: " << std::endl << IdMat << std::endl << std::endl;
            out << "Total Frames Tracks: " << std::endl << totalFramesMat << std::endl << std::endl;
            #endif

            cv::Mat newInds = (IdMat == 0) & (totalFramesMat == 2) & (distancesMat <= 25);
            int nonZeroCount = cv::countNonZero( newInds );
            bool noAssignedID = minTrack->id == 0;

            #ifdef SDCV_TRACKING_DEBUG
            out << "New Vehicles: " << std::endl << newInds << std::endl << std::endl;
            #endif

            if(nonZeroCount == 1 && noAssignedID) minTrack->consInvisibleFrames = 100;
            else if(nonZeroCount == 2 && noAssignedID) {
                unmatchedTrack->bbox = minTrack->bbox;
                unmatchedTrack->totalVisibleFrames++;
                unmatchedTrack->areas.push_back(minTrack->areas.at(0));

                if( minTrack->normAreas.back() > .06) unmatchedTrack->normAreas.push_back(minTrack->normAreas.back());

                unmatchedTrack->estimatedCentroid.push_back(minTrack->estimatedCentroid.back());
                unmatchedTrack->detectedCentroid.push_back(minTrack->detectedCentroid.back());
                unmatchedTrack->consInvisibleFrames = 0;
                minTrack->consInvisibleFrames = 100;

            } else unmatchedTrack->consInvisibleFrames++;
        }
        #ifdef SDCV_TRACKING_DEBUG
        out << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl << std::endl;
        out << "[Update Tracks End] --------------------" << std::endl;
        #endif
    }


    /*!
     * @name	erease
     * @brief	Deletes tracks that are not anymore in the frame and false tracks.
     */
    void Tracker::erease(sdcv::Classifier classifier) {
        #ifdef SDCV_TRACKING_DEBUG
        out << "[Delete Tracks Begin] --------------------" << std::endl;
        #endif


        if( tracks.empty() ) {
            #ifdef SDCV_TRACKING_DEBUG
            out << "[Delete Tracks End] --------------------" << std::endl;
            #endif
            return;
        }


        // Compute the fraction of the track's age for which it was visible.
        int NbTracks = tracks.size();
        cv::Mat VisibilityMat;
        cv::Mat lostIndsROI;
        cv::Mat IdMat, consecutiveBackwardDirMat, VelocityMat, consInvisibleFramesMat;
        /*
        // This is incorrect
        std::vector<cv::Point> Contour;
        Contour.push_back(cv::Point(roi.getBbox().x, roi.getBbox().y));
        Contour.push_back(cv::Point(roi.getBbox().x + roi.getBbox().width, roi.getBbox().y));
        Contour.push_back(cv::Point(roi.getBbox().x + roi.getBbox().width, roi.getBbox().y + roi.getBbox().height));
        Contour.push_back(cv::Point(roi.getBbox().x, roi.getBbox().y + roi.getBbox().height));

        // xi and yi defines the vertices of the ROI so the properly is:
        roi.getVertices();
        */

        #ifdef SDCV_TRACKING_DEBUG
        out << "<<<<<<<<<<<<< Visibility" << std::endl;
        out << "Contour: " << roi.getVertices() << std::endl;
        #endif

        for(std::vector<sdcv::Track>::iterator it = tracks.begin(); it != tracks.end(); ++it) {
            double visibilityElement = it->totalVisibleFrames / (double)it->totalFrames;
            VisibilityMat.push_back(visibilityElement);

            // IDs
            IdMat.push_back(it->id);

            // consecutiveBackwardDir
            consecutiveBackwardDirMat.push_back(it->consecutiveBackwardDir);

            // velocity
            VelocityMat.push_back(it->velocity);

            // consInvisibleFrames
            consInvisibleFramesMat.push_back(it->consInvisibleFrames);

            // centroid coordinates of the bounding box.
            double cx = (it->bbox.x + it->bbox.width)/2;
            double cy = (it->bbox.y + it->bbox.height)/2;
            cv::Point2d testPoint(cx, cy);

            // See if the object is inside the ROI
            /*
             * pointPolygonTest > 0: "Inside"
             * pointPolygonTest = 0: "On Edge"
             * pointPolygonTest < 0: "Outside"
             */
            unsigned char testRes = (unsigned char)(cv::pointPolygonTest(roi.getVertices(), testPoint, false) >= 0 ? 0 : 255); // ~cv::pointPolygonTest(...)
            lostIndsROI.push_back( testRes );
        }

        #ifdef SDCV_TRACKING_DEBUG
        out << "Tracks visibility: "			<< std::endl << VisibilityMat << std::endl;
        out << "Tracks ID: "					<< std::endl << IdMat << std::endl;
        out << "Tracks BackwardDir: "			<< std::endl << consecutiveBackwardDirMat << std::endl;
        out << "Tracks Velocity: "			<< std::endl << VelocityMat << std::endl;
        out << "Tracks consInvisibleFrames: " << std::endl << consInvisibleFramesMat << std::endl;
        out << "lost Indexes: "				<< std::endl << lostIndsROI << std::endl;
        out << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl;
        #endif

        // Check backward direction -----------------------------------------------------------------
        cv::Mat lostIndsBackDir = ( (IdMat == 0) & (consecutiveBackwardDirMat == 1) |
                                  ((VelocityMat >= -2) & (VelocityMat <= 2)));

        lostIndsBackDir = (IdMat != 0)	&	( (VelocityMat < -1000)	|	(VelocityMat > 1000)	|
                          ((VelocityMat >= -1)	&	(VelocityMat <= 1)))	|
                          (consecutiveBackwardDirMat == 5)	|	lostIndsBackDir;

        #ifdef SDCV_TRACKING_DEBUG
        out << std::endl << "<<<< Check backward direction" << std::endl;
        out << "lost Indexes Backward Dir:" << std::endl << lostIndsBackDir << std::endl << std::endl;
        out << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
        #endif

        // Find the indices of 'lost' tracks  ----------------------------------------------------------
        cv::Mat lostInds = lostIndsROI | lostIndsBackDir | ((IdMat == 0) & (VisibilityMat < 0.65)) |
                           (consInvisibleFramesMat >= this->minInvisibleCount) ;
        #ifdef SDCV_TRACKING_DEBUG
        out << std::endl << "<<<< Find the indices of 'lost' tracks" << std::endl;
        out << "lost Indexes:" << std::endl << lostInds << std::endl << std::endl;
        out << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl;
        #endif


        /* ------------------------------------------------------------------------------*/

        int nonZero = cv::countNonZero( lostInds );
        #ifdef SDCV_TRACKING_DEBUG
        out << "Lost Indexes non zero values: " << nonZero << std::endl;
        #endif
        if( nonZero > 0) {
            std::vector<sdcv::Track>::iterator lostTrack = tracks.begin();
            for(int idx = 0; idx < lostInds.cols; idx++, ++lostTrack) {
                bool flag = false;
                bool flagId = (lostInds.at<unsigned char>(idx) != 0) && (lostTrack->id != 0);

                if( flagId ) {
                    if (lostTrack->estimatedArea == 0) {
                        // compute estimated area only if the object is created after line detection
                        int sumNormAreas = std::accumulate(lostTrack->normAreas.begin(), lostTrack->normAreas.end(), 0.0f);
                        lostTrack->estimatedArea = sumNormAreas/(double)lostTrack->normAreas.size();
                    }
                }

                // See if the object is before line detection -------------------------------------------
                std::vector<cv::Point> ContourPt;
                ContourPt.push_back(roi.getLineDetection().at(0));	// First point
                ContourPt.push_back( cv::Point(roi.getDivLineLane().at<short>(0,2), roi.getDivLineLane().at<short>(0,3)) );	// Second point
                int NbDvLnIdx = roi.getNumLanes() - 1;
                ContourPt.push_back( cv::Point(roi.getDivLineLane().at<short>(NbDvLnIdx,2), roi.getDivLineLane().at<short>(NbDvLnIdx,3)) ); // Third point
                ContourPt.push_back(roi.getLineDetection().at(1));	// Fourth point
                ContourPt.push_back(roi.getLineDetection().at(0));	// Fiveth point

                bool inPoly = (bool)(cv::pointPolygonTest(ContourPt, lostTrack->estimatedCentroid.back(), false) >= 0 ? true : false);

                #ifdef SDCV_TRACKING_DEBUG
                out << "object is before line detection: " << (inPoly ? "Yes" : "No") << std::endl;
                #endif

                if( flagId && (inPoly || (lostTrack->totalVisibleFrames == minVisibleCount)) ) {
                    flag = true;
                    classifier.update( 3 );
                    if( FP_ID.back() == 0 ) {
                        FP_ID.clear();
                        FP_ID.push_back( lostTrack->id );
                    } else FP_ID.push_back( lostTrack->id );
                }

                // Classification -----------------------------------------------------------------
                if( flagId && !flag ) {
                    // or simply: classifier.update( lostTrack->estimatedArea )	to update each classification type
                    // it is for them according to their defined threshold area.
                    if( lostTrack->estimatedArea < 0.12 ) classifier.update(0);
                    else if( lostTrack->estimatedArea < 1.2 ) classifier.update(1);
                    else classifier.update(2);
                }
            }
        } /* nonZero > 0 */

        // Delete lost tracks ------------------------------------------------------------------
        #ifdef SDCV_TRACKING_DEBUG
        out << std::endl << "<<<<<<<< Delete lost tracks" << std::endl;
        #endif

        /*
        */
        std::vector<sdcv::Track> tmp;
        std::vector<sdcv::Track>::iterator itTrack = tracks.begin();
        for(int i = 0; i < lostInds.cols, itTrack != tracks.end(); i++, ++itTrack) {
            if( lostInds.at<unsigned char>(i) == 0 ) {
                tmp.push_back(*itTrack);
                #ifdef SDCV_TRACKING_DEBUG
                out << "Track #" << i << " wasn't delete!" << std::endl;
                itTrack->print( out );
                out << std::endl;
                #endif
            }
            #ifdef SDCV_TRACKING_DEBUG
            else {
                out << "Track #" << i << " was delete!" << std::endl;
                itTrack->print( out );
                out << std::endl;
            }
            #endif
        }
        tracks.clear();
        tracks = tmp;

        #ifdef SDCV_TRACKING_DEBUG
        out << std::endl << "<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl;
        out << "[Delete Tracks End] --------------------" << std::endl;
        #endif
    }


    cv::Mat Tracker::getAssigmentCostMatrix( void ) {
        cv::Mat MeasurementsCentroid = cv::Mat(blobLst.getCentroids(), true);
        cv::Mat CostMatrix;

        // DEBUG
        #ifdef SDCV_TRACKING_DEBUG
        out << "Detected Centroids:" << std::endl << MeasurementsCentroid << std::endl << std::endl;
        #endif
        // END DEBUG


        for(std::vector<Track>::iterator it = tracks.begin(); it != tracks.end(); ++it) {
            cv::Rect bbox = it->bbox;

            // Predict the current location of the track
            cv::Mat predictedState = it->AKF.predict();
            it->predictedCentroid = cv::Point2f(predictedState.at<float>(0,0), predictedState.at<float>(2,0));
            it->estimatedCentroid.push_back(it->predictedCentroid);

            // Shift the bounding box so that its center is at the predicted location
            cv::Point2f predictBBox((float)bbox.width, (float)bbox.height);
            predictBBox = it->predictedCentroid - (predictBBox * 0.5);
            it->bbox = cv::Rect((int)predictBBox.x, (int)predictBBox.y, bbox.width, bbox.height);

            // Compute the cost of assigning each detection to each track
            distance(it->AKF, MeasurementsCentroid, CostMatrix);
        }

        // Convert cost matrix to <int>.
        CostMatrix.convertTo(CostMatrix, CV_16S);

        // DEBUG
        #ifdef SDCV_TRACKING_DEBUG
        out << "Cost Matrix:" << std::endl << MeasurementsCentroid << std::endl << std::endl;
        #endif
        // END DEBUG

        return CostMatrix;
    }

    /*
     * Use the distance method to find the best matches.
     * The computed distance values describe how a set of measurements matches the Kalman filter.
     *
     * You can thus select a measurement that best fits the filter. This strategy can be used for matching object
     * detections against object tracks in a multiobject tracking problem.
     *
     * This distance computation takes into account the covariance of the predicted state and the process noise.
     * The distance method can only be called after the predict method.
     *
     * d = distance(obj, z_matrix) computes a distance between the location of a detected object and the predicted
     * location by the Kalman filter object. Each row of the N-column z_matrix input matrix contains a measurement
     * vector. The distance method returns a row vector where each distance element corresponds to the measurement
     * input.
     */
    void Tracker::distance(cv::KalmanFilter AKF, cv::Mat centroids, cv::OutputArray CostMatrix) {
        CV_Assert(blobLst.getLen() > 0);

        int NbTracks = (int)tracks.size();
        int NbDetections = blobLst.getLen();
        cv::Mat Tmp;
        cv::Mat costRow = cv::Mat::zeros(cv::Size(1, NbDetections), CV_32F);
        CostMatrix.copyTo(Tmp);

        // Calculating distance for each row of blobLst.getCentroids()
        //S = HPH.T + R
        //d(z) = (z - H*x).T * S.inv * (z- H*x) + ln( det(S) );
        cv::Mat Sigma = (AKF.measurementMatrix * AKF.errorCovPost * AKF.measurementMatrix.t()) + (AKF.measurementNoiseCov);
        cv::Mat centroidPred = cv::Mat(AKF.measurementMatrix * AKF.statePost).t();

        std::vector<float> distances;
        for(int i = 0; i < centroids.rows; i++) {
            float xo = centroids.row(i).at<float>(0,0) - centroidPred.at<float>(0,0);
            float yo = centroids.row(i).at<float>(0,1) - centroidPred.at<float>(0,1);

            cv::Mat aux = (cv::Mat_<float>(1,2) << xo,yo);
            cv::Mat distance = aux * Sigma.inv() * aux.t() + log10( cv::determinant(Sigma) );

            distances.push_back(distance.at<float>(0,0));
        }

        // Add a new row
        Tmp.push_back( cv::Mat(distances).t() );
        Tmp.copyTo( CostMatrix );
    }


    /*!
     * @name
     * @brief
     * @param
     */
    void Tracker::assignamentProblemSolver(cv::Mat CostMatrix, std::vector<cv::Point> &assignments, std::vector<int> &unassignedTracks, std::vector<int> &unassignedDetections) {

        cv::Mat_<int> solvedMatrix( CostMatrix );
        Munkres solver;
        solver.diag( false );
        solver.solve( solvedMatrix );

        // Return the assigned tracks
        for(int i = 0; i < solvedMatrix.rows; i++) {
            int idx;
            std::vector<int> rowVector;
            solvedMatrix.row(i).copyTo( rowVector );

            std::vector<int>::iterator it = std::find(rowVector.begin(), rowVector.end(), 0);
            idx = std::distance(rowVector.begin(), it);

            if (it != rowVector.end()) assignments.push_back(cv::Point(i, idx));
            else unassignedTracks.push_back( i );
        }

        // Return the unassignedDetections
        for(int i = 0; i < solvedMatrix.cols; i++) {
            int countNonZero = cv::countNonZero(solvedMatrix.col(i));
            if( countNonZero == solvedMatrix.rows ) {
                unassignedDetections.push_back(i);
            }
        }

        // Show results
        #ifdef SDCV_TRACKING_DEBUG
        out << "[Assignament Problem Solver Begin]----------------" << std::endl;
        out << "Solved matrix = " << std::endl << solvedMatrix << std::endl << std::endl;

        out << "{Results}" << std::endl;
        out << "Matches = "				<< std::endl << cv::Mat(assignments) << std::endl;
        out << "unassigned Tracks = "		<< std::endl << cv::Mat(unassignedTracks) << std::endl;
        out << "unassigned Detections = " << std::endl << cv::Mat(unassignedDetections) << std::endl;
        out << "[Assignament Problem Solver End]----------------" << std::endl << std::endl;
        #endif
    }

    // Destructor -------------------------------------------------------------------------------------
    Tracker::~Tracker() { }

}
/* ************** E N D   O F   F I L E ----------------- CINVESTAV GDL */
