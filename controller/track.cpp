/* ---------------------------*/
/*       Library Include       */
/* ---------------------------*/
#include "track.h"

namespace sdcv {
    /*--------------------------------*/
    /*     Class reference method     */
    /*--------------------------------*/
    Track::Track(){}

    Track::Track(sdcv::Blob newBlob) {
        id = 0;
        bbox = newBlob.getBBox();
        detectedCentroid.push_back(newBlob.getCentroid());
        predictedCentroid = cv::Point2f(0,0);
        estimatedCentroid.push_back(cv::Point2f(0,0));

        KalmanFilterInit();

        areas.push_back( newBlob.getArea() );
        normAreas.push_back( newBlob.getNormArea() );
        estimatedArea = 0;
        consecutiveBackwardDir = 0;
        totalFrames = 1;
        totalVisibleFrames = 1;
        consInvisibleFrames = 0;
    }

    // Action method
    void Track::print( std::ofstream &file  ) {
        file << "[Track Info]:"				<< std::endl;
        file << "- Bounding box: "				<< bbox << std::endl;
        file << "- Detected Centroids: \n"		<< cv::format(detectedCentroid,0) << std::endl;
        file << "- Predicted Centroids: "		<< predictedCentroid << std::endl;
        file << "- Estimated Centroids: \n"	<< cv::format(estimatedCentroid,0) << std::endl;
        file << "- Kalman Filter: \n"			<< std::endl;
        file << "-- X_hat:\n"					<< AKF.statePost << std::endl;
        file << "-- P:\n"						<< AKF.errorCovPost << std::endl;
        file << "-- K:\n"						<< AKF.gain << std::endl;
        file << "-- R:\n"						<< AKF.measurementNoiseCov << std::endl;
        file << "-- Q:\n"						<< AKF.processNoiseCov << std::endl;
        file << "- Areas: "					<< cv::format(areas,0) << std::endl;
        file << "- Normalized Area: "			<< cv::format(normAreas,0) << std::endl;
        file << "- Estimated Area"				<< estimatedArea << std::endl;
        file << "- Velocity: "					<< velocity << std::endl;
        file << "- Total Frames: "				<< totalFrames << std::endl;
        file << "- Visible Frames: "			<< totalVisibleFrames << std::endl;
        file << "- Invisible Frames: "			<< consInvisibleFrames << std::endl;
        file << "-------------------------------------------------------------" << std::endl << std::endl;
    }

    void Track::KalmanFilterInit(void) {
        int dt = 1;
        AKF.init(4, 2, 0);

        AKF.transitionMatrix = (cv::Mat_<float>(4, 4) << 1,dt,0,0,   0,1,0,0,   0,0,1,dt,   0,0,0,1); // [X	Vx	Y	Vy]
        AKF.measurementMatrix = (cv::Mat_<float>(2, 4) << 1,0,0,0,   0,0,1,0);	// [X	Vx	Y	Vy]

        cv::setIdentity(AKF.processNoiseCov, cv::Scalar::all(0.9));		// Q
        cv::setIdentity(AKF.measurementNoiseCov, cv::Scalar::all(0.3));	// R
        cv::setIdentity(AKF.errorCovPost, cv::Scalar::all(1));			// P(k)+

        AKF.statePost.at<float>(0) = detectedCentroid.back().x;
        AKF.statePost.at<float>(1) = 0;
        AKF.statePost.at<float>(2) = detectedCentroid.back().y;
        AKF.statePost.at<float>(3) = 0;
    }


    Track::~Track() {}
}
/* ************** E N D   O F   F I L E ----------------- CINVESTAV GDL */
