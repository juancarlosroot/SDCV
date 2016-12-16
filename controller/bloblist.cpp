/* ---------------------------*/
/*       Library Include       */
/* ---------------------------*/
#include "blobList.h"


/*!
 * @namespace	sdcv.
 * @brief		Vehicle Detection and Classification System.
 */
namespace sdcv {
    /*!
     * @class	BlobList.
     * @brief	Used for creating a blob list.
     */
    // Constructor
    BlobList::BlobList(){}

    BlobList::BlobList(std::vector<sdcv::Blob> blobs) {
        this->len = 0;

        for(std::vector<Blob>::iterator blob = blobs.begin(); blob != blobs.end(); ++blob) {
            areas.push_back( blob->getArea() );
            centroids.push_back( blob->getCentroid() );
            bboxes.push_back( blob->getBBox() );
            len++;
        }
    }

    // Get methods
    std::vector<int> 		BlobList::getAreas() { return( areas ); }
    std::vector<cv::Point2f> 	BlobList::getCentroids() { return( centroids ); }
    std::vector<cv::Rect >	BlobList::getBBoxes() { return( bboxes ); }
    int BlobList::getLen( void ) { return this->len; }
    // Set methods


    // Action methods
    void BlobList::clear( void ) {
        areas.clear();
        centroids.clear();
        bboxes.clear();
        len = 0;
    }

    void BlobList::add(sdcv::Blob blob) {
        areas.push_back( blob.getArea() );
        centroids.push_back( blob.getCentroid() );
        bboxes.push_back( blob.getBBox() );
        len++;
    }


    // Destructor
    BlobList::~BlobList() { }

};
