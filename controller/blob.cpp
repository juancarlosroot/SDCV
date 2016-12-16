#include "blob.h"

/*!
 * @namespace	sdcv.
 * @brief		Vehicle Detection and Classification System.
 */

namespace sdcv {
    // Constructor
    Blob::Blob(std::vector< cv::Point > contour, int area) {
        cv::Moments m = moments(contour);
        this->centroid = cv::Point2f((float)(m.m10/(double)m.m00), (float)(m.m01/(double)m.m00));

        if( area < 0 ) this->area = (int)cv::contourArea(contour);
        else this->area = area;

        this->bbox = cv::boundingRect(contour);
    }

    // Get methods
    cv::Point2f Blob::getCentroid( void ) { return this->centroid; }
    int Blob::getArea(void) { return this->area; }
    double Blob::getNormArea(void) { return normArea; }
    cv::Rect Blob::getBBox(void) { return this->bbox; }

    // Set methods
    void Blob::setBlob(std::vector< cv::Point > contour) {
        cv::Moments m = moments(contour);
        this->centroid = cv::Point2f((float)(m.m10/(double)m.m00), (float)(m.m01/(double)m.m00));
        this->area = (int)cv::contourArea(contour);
        this->bbox = cv::boundingRect(contour);
    }

    void Blob::setNormArea(double normArea) { this->normArea = normArea; }

    // Action methods
    void Blob::print( std::ofstream &file  ) {
        file << "[Blob Info]:"			<< std::endl;
        file << "- Centroid: "			<< centroid << std::endl;
        file << "- Bounding box: "		<< bbox << std::endl;
        file << "- Area: "				<< area << std::endl;
        file << "- normalized Area: "	<< normArea << std::endl;
        file << "-----------------------------------" << std::endl << std::endl;
    }

    void Blob::print( void  ) {
        std::cout << "[Blob Info]:"			<< std::endl;
        std::cout << "- Centroid: "			<< centroid << std::endl;
        std::cout << "- Bounding box: "		<< bbox << std::endl;
        std::cout << "- Area: "				<< area << std::endl;
        std::cout << "- normalized Area: "	<< normArea << std::endl;
        std::cout << "-----------------------------------" << std::endl << std::endl;
    }

    // Destructor
    Blob::~Blob(void) { }
}
