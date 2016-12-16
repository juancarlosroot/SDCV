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


/* ---------------------------*/
/*       Library Include       */
/* ---------------------------*/
#include "detector.h"

#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

std::ofstream fileout("/detection.txt");
#define outDet fileout
/*!
 * @namespace	sdcv.
 * @brief		Vehicle Detection and Classification System.
 */
namespace sdcv {
    static std::string ItoS(int Number) {
        std::string str;          // string which will contain the result

        std::ostringstream bridge;   // stream used for the conversion

        bridge << Number;      // insert the textual representation of 'Number' in the characters in the stream

        str = bridge.str(); // set 'Result' to the contents of the stream

        return( str );
    }

    typedef struct {
        double normArea;
        double laneWidth;
        int i;
        double x_DL1;
        double x_DL2;
    }NormArea_t;

    static NormArea_t normalizeArea(DivLaneLine_t DivLaneLine, std::vector<sdcv::Blob>::iterator blob);

    // ----------------------------------------------------
    Detector::Detector() {
        this->BgSubMoG = cv::createBackgroundSubtractorMOG2();

        this->bBBox = true;
        this->bLabel = true;
        this->bArea = true;
        this->bCentroid = true;

        this->MinimumBlobArea = sdcv::MinBlobArea;
        this->MaximumBlobArea = -1;

        this->erodeKernel = cv::Mat::ones(cv::Size(2, 2), CV_8U);
        this->dilateKernel = cv::Mat::ones(cv::Size(3, 3), CV_8U);

        this->oclussionParams.push_back(1.2);
        this->oclussionParams.push_back(1.22);
        this->oclussionParams.push_back(2.27);
        this->oclussionParams.push_back(0.02);
    }

    Detector::Detector(int MinimumBlobArea, int MaximumBlobArea, bool bDrawID, bool bDrawBBox) {
        //this->BlobsList = BlobList::BlobList();
        this->BgSubMoG = cv::createBackgroundSubtractorMOG2();
        /*this->BgSubMoG->setHistory(200);
        this->BgSubMoG->setNMixtures(3);
        this->BgSubMoG->setDetectShadows(false);
        this->BgSubMoG->setBackgroundRatio(0.5);
        this->learningRate = 0.005;*/

        this->MinimumBlobArea = MinimumBlobArea;
        this->MaximumBlobArea = MaximumBlobArea;
        this->bBBox = bDrawBBox;
        this->bLabel = bDrawID;

        this->bArea = true;
        this->bCentroid = true;

        this->erodeKernel = cv::Mat::ones(cv::Size(2, 2), CV_8U);
        this->dilateKernel = cv::Mat::ones(cv::Size(3, 3), CV_8U);

        this->oclussionParams.push_back(1.2);
        this->oclussionParams.push_back(1.22);
        this->oclussionParams.push_back(2.7);
        this->oclussionParams.push_back(0.02);

        this->NbFrame = 0;
        this->j = 0;
    }


    // Get methods
    std::vector<sdcv::Blob> Detector::getBlobList( void ) { return( this->blobs ); }

    // Set methods
    void Detector::setMOG(cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG) { this->BgSubMoG = pMOG; }
    void Detector::setErodeKernel(cv::Mat kernel) { this->erodeKernel = kernel; }
    void Detector::setDilateKernel(cv::Mat kernel) { this->dilateKernel = kernel; }
    void Detector::setMinimumBlobArea(int MinimumBlobArea) { this->MinimumBlobArea = MinimumBlobArea; }
    void Detector::setMaximumBlobArea(int MaximumBlobArea) { this->MaximumBlobArea = MaximumBlobArea; }
    void Detector::setDrawBBox(bool bDrawBBox) { this->bBBox = bDrawBBox; }
    void Detector::setDrawLabel(bool bDrawLabel) { this->bLabel = bDrawLabel; }
    void Detector::setAreaOutput( bool bAreaOutput ) { this->bArea = bAreaOutput; }
    void Detector::setCentroidOutput( bool bCentroidOutput ) { this->bCentroid = bCentroidOutput; }
    void Detector::setOclussion(bool bOclussionHandling) { this->bOclussionHandling = bOclussionHandling; }
    void Detector::setROI(sdcv::ROI roi) { this->roi = roi; }
    void Detector::setOclussionParam(std::vector<double> Params) {
        CV_Assert(Params.size() == 4);
        this->oclussionParams = Params;
    }


    // Action methods
    bool Detector::isReady( void ) {
        bool bReady = (!this->BgSubMoG->empty()) & ( !this->dilateKernel.empty() ) & ( !this->erodeKernel.empty() );
        return bReady;
    }


    //#define DETECTION_DEBUG		// Uncomment this line to debug this method
    void Detector::detect(cv::Mat frame, cv::OutputArray mask) {
        cv::Mat foreground, roiFore;

        #ifdef DETECTION_DEBUG
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        std::cout << std::endl << std::endl << "[BLOB DETECTOR]\nCalled on Frame: " << NbFrame << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        #endif

        CV_Assert( !frame.empty() );

        // Apply Mixture of Gaussians Model
        BgSubMoG->apply(frame, foreground);

        #ifdef DETECTION_DEBUG
        //cv::Mat Background;
        //BgSubMoG->getBackgroundImage(Background);
        //cv::imshow("Background", Background);
        #endif

        // Applying ROI
        CV_Assert( !roi.getMask().empty() );
        roi.apply(foreground, roiFore);

        // Apply filters
        cv::erode(roiFore, roiFore, erodeKernel);
        cv::dilate(roiFore, roiFore, dilateKernel);
        //cv::waitKey(0);

        // Get Blobs
        getBlobs(roiFore, mask);
        CV_Assert( !mask.empty() );


        /*if( !this->blobs.empty() ) {
            std::vector<int> areas;
            for(std::vector<sdcv::Blob>::iterator it = blobs.begin(); it != blobs.end(); ++it) {
                areas.push_back( it->getArea() );
            }

            std::vector<int>::iterator maxElementIt = std::max_element(areas.begin(), areas.end());
            double Th = double(*maxElementIt)/(double)roi.getArea();

            if(Th>0.5) {
                learningRate = 0.02;
                j++;
            } else j = 0;
        }*/

        #ifdef DETECTION_DEBUG
        std::cout << std::endl << "Blobs found: " << blobs.size() << std::endl;
        #endif

        // Oclussion Handling
        if( bOclussionHandling ) {
            cv::Mat OclussionMask;
            oclussionHandling(mask, OclussionMask);
            OclussionMask.copyTo(mask);
        }
        CV_Assert( !mask.empty() );

        /*if(j == 0) {
            if( (blobs.size() <= 3) && learningRate != .005) learningRate = .005;
            else if( (blobs.size() == 4) && learningRate != 0.01) learningRate = 0.01;
            else if( (blobs.size() == 5) && learningRate != 0.02) learningRate = 0.02;
            else if( (blobs.size() >= 6) && learningRate != 0.05) learningRate = 0.05;
        }*/

        #ifdef DETECTION_DEBUG
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        std::cout << std::endl << "[BLOB DETECTOR END]" << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cv::waitKey();
        #endif
        NbFrame++;
    }

    void Detector::draw( cv::Mat frame ) {
        // Draw features (BBox, Label, etc)
        if( this->bBBox ) {
            for(std::vector<sdcv::Blob>::iterator it = blobs.begin(); it != blobs.end(); ++it) {
                cv::rectangle(frame, it->getBBox(), cv::Scalar(0,255,255), 1);
                cv::Mat rec = frame(it->getBBox());
                cv::Mat color(rec.size(), CV_8UC3, cv::Scalar(0,255,255));
                cv::addWeighted(color, 0.2, rec, 1.0, 0.0, rec);
                if( this->bCentroid ) cv::circle(frame, cv::Point(it->getCentroid()), 2, cv::Scalar(255,0,0));
            }

        }

        cv::line(frame, roi.getLineDetection().at(0), roi.getLineDetection().at(1), cv::Scalar(0,255,0), 2);
        cv::circle(frame, roi.getCenterLineDetection(), 2, cv::Scalar(255,0,0), -1);

    }


    // Destructor
    Detector::~Detector(){}


    void Detector::getBlobs(cv::InputArray mask, cv::OutputArray blobMask) {
        std::vector< std::vector<cv::Point> > contours;
        std::vector<sdcv::Blob> blobs;
        cv::Mat maskTmp;

        this->blobs.clear();
        mask.copyTo( maskTmp );

        cv::findContours(maskTmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        cv::Mat ForegroundMask = cv::Mat::zeros(maskTmp.size(), CV_8UC1);

        for (size_t i = 0; i < contours.size(); i++)
        {
            unsigned int Area = (unsigned int)cv::contourArea( contours[i] );

            if (Area > MinimumBlobArea && Area < MaximumBlobArea) {
                cv::drawContours(ForegroundMask, contours, (int)i, CV_RGB(255, 255, 255), CV_FILLED);
                this->blobs.push_back( contours[i] );
            }

        }

        ForegroundMask.copyTo( blobMask );
    }



    //#define OCCLUSION_DEBUG		// Uncomment this line to debug this method
    void Detector::oclussionHandling(cv::InputArray mask, cv::OutputArray maskOclussion) {
        int flag = 0;
        int NbBlobs = (int)blobs.size();
        unsigned int ByteLaneLines = 0;

        DivLaneLine_t LaneData = roi.getLaneData();
        cv::Mat foreground;
        mask.copyTo(foreground);

        // DEBUG
        #ifdef OCCLUSION_DEBUG
        cv::Mat foregroundRGB;
        cv::cvtColor(foreground, foregroundRGB, cv::COLOR_GRAY2RGB);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        std::cout << "[OCLUSSION DETECTOR]" << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cv::imshow("mask", mask);
        int NbBlob = 1;
        #endif
        // DEBUG END

        for(std::vector<sdcv::Blob>::iterator it = blobs.begin(); it != blobs.end(); ++it) {
            double overlapRatio;
            NormArea_t NormArea = normalizeArea(LaneData, it);


            if (NbBlobs > 1 && it < blobs.end() - 1) {
                std::vector<sdcv::Blob>::iterator blobNext = it + 1;

                int totalArea = it->getBBox().area() + blobNext->getBBox().area();
                overlapRatio = (double)cv::Rect(it->getBBox() & blobNext->getBBox()).area() / (double)totalArea;

            } else  overlapRatio = 0;

            // Test whether the vehicle is completly inside ROI
            bool in1 = it->getBBox().y > roi.getBbox().y + roi.getBbox().height;

            // Test whether the vehicle is before detection line
            bool in2 = it->getCentroid().y < roi.getCenterLineDetection().y;

            bool c1 = ((it->getBBox().width / (double)NormArea.laneWidth) > oclussionParams.at(0)) && (NormArea.normArea < oclussionParams.at(1)) && in1;
            bool c2 = in2 && ((double)(it->getBBox().width / (double)NormArea.laneWidth) > oclussionParams.at(2));


            #ifdef OCCLUSION_DEBUG
            cv::putText(foregroundRGB, ItoS(NbBlob), cv::Point(it->getCentroid()), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0));
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            std::cout << "......................................................." << std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cv::imshow("Label", foregroundRGB);

            std::cout << "Label: " << NbBlob << std::endl;
            std::cout << "<<<<< Olcusion Params: " << std::endl;
            std::cout << "\t1. " << oclussionParams.at(0) << std::endl;
            std::cout << "\t2. " << oclussionParams.at(1) << std::endl;
            std::cout << "\t3. " << oclussionParams.at(2) << std::endl;
            std::cout << "\t4. " << oclussionParams.at(3) << std::endl << std::endl;
            it->print();
            std::cout << "Lane line: " << NormArea.i << std::endl;
            std::cout << "Lane Width: " << NormArea.laneWidth << std::endl;
            std::cout << "overlap Ratio: " << overlapRatio << std::endl;
            std::cout << "Vehicle inside ROI? " << (in1 ? "true" : "false") << std::endl;
            std::cout << "Vehicle before Line Detection? " << (in2 ? "true" : "false") << std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            std::cout << "C1: " << (it->getBBox().width / (double)NormArea.laneWidth) << " > " << oclussionParams.at(0);
            std::cout << " && " << NormArea.normArea << " < " << oclussionParams.at(1) << std::endl;
            std::cout << "Condition 1: " << (c1 ? "true" : "false") << std::endl;
            std::cout << "C2: " << it->getBBox().width / (double)NormArea.laneWidth << " > " << oclussionParams.at(2) << "?" << std::endl;
            std::cout << "Condition 2: " << (c2 ? "true" : "false") << std::endl << std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cv::waitKey();
            #endif

            //
            if ( c1 || c2 || (overlapRatio > oclussionParams.at(3))) /*|| (areaN > 4)) */ {
                cv::Point2d dist(it->getCentroid().x - NormArea.x_DL1, NormArea.x_DL2 - it->getCentroid().x);
                cv::Mat foregroundOclussion;

                    if ( (dist.x < dist.y) && (NormArea.i  != 0) ) {
                        // DEBUG
                        #ifdef OCCLUSION_DEBUG
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                        std::cout << "Oclussion by Blob: " << NbBlob << " at first condition on frame: " << NbFrame << std::endl;
                        std::cout << "Number of lane's line: " << NormArea.i+1 << "/" << roi.getNumLanes() << std::endl;
                        it->print();
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        cv::Mat Fore3L;
                        cv::cvtColor(foreground, Fore3L, cv::COLOR_GRAY2RGB);
                        cv::Point pt1 = cv::Point(LaneData.lineLane.at<short>(NormArea.i, 0), LaneData.lineLane.at<short>(NormArea.i, 1));
                        cv::Point pt2 = cv::Point(LaneData.lineLane.at<short>(NormArea.i, 2), LaneData.lineLane.at<short>(NormArea.i, 3));
                        cv::imshow("OcludedMask", foreground);
                        cv::imshow("GreenMask", Fore3L);
                        #endif
                        // DEBUG END

                        flag++;
                        foreground.copyTo(foregroundOclussion, roi.getDivLaneMask( NormArea.i ));
                        foregroundOclussion.copyTo(foreground);

                        #ifdef OCCLUSION_DEBUG
                        cv::imshow("DeocludedMask", foreground);
                        cv::waitKey();
                        #endif

                    } else if ( (dist.x > dist.y ) && ( (NormArea.i + 1) < roi.getNumLanes() - 1)) {
                        // DEBUG
                        #ifdef OCCLUSION_DEBUG
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                        std::cout << "line: " << NormArea.i << std::endl;
                        std::cout << "Oclussion by Blob: " << NbBlob << " at second condition on frame: " << NbFrame << std::endl;
                        std::cout << "Number of lane's line: " << NormArea.i+2 << "/" << roi.getNumLanes() << std::endl;
                        it->print();
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                        cv::Mat Fore3L;
                        cv::cvtColor(foreground, Fore3L, cv::COLOR_GRAY2RGB);
                        cv::Point pt1 = cv::Point(LaneData.lineLane.at<short>(NormArea.i+1, 0), LaneData.lineLane.at<short>(NormArea.i+1, 1));
                        cv::Point pt2 = cv::Point(LaneData.lineLane.at<short>(NormArea.i+1, 2), LaneData.lineLane.at<short>(NormArea.i+1, 3));
                        cv::line(Fore3L, pt1, pt2, cv::Scalar(255, 0, 0), 2);
                        cv::imshow("OcludedMask", foreground);
                        cv::imshow("GreenMask", Fore3L);
                        #endif
                        // DEBUG END

                        flag++;
                        foreground.copyTo(foregroundOclussion, roi.getDivLaneMask(NormArea.i + 1));
                        foregroundOclussion.copyTo(foreground);

                        #ifdef OCCLUSION_DEBUG
                        cv::imshow("DeocludedMask", foreground);
                        cv::waitKey();
                        #endif
                    }
                #ifdef OCCLUSION_DEBUG
                else std::cout << "Number of lane's line: " << NormArea.i+1 << "/" << roi.getNumLanes() << "or " << NormArea.i+2 << "/" << roi.getNumLanes() << " could have already been setted" << std::endl;
                #endif

            }
            #ifdef OCCLUSION_DEBUG
            NbBlob++;
            #endif

        }

        foreground.copyTo( maskOclussion );

        // Update Blobs
        if ( flag > 0 ) {
            #ifdef OCCLUSION_DEBUG
            std::cout << "\nOclusion Handling Count: " << flag << std::endl;
            #endif

            cv::Mat ForegroundMask;
            this->getBlobs(foreground, ForegroundMask);
            ForegroundMask.copyTo( maskOclussion );

            // DEBUG
            #ifdef OCCLUSION_DEBUG
            std::cout << "[Blob List]" << std::endl << "{" << std::endl;
            std::cout << "Blobs Count: " << blobs.size() << std::endl << std::endl;
            int iBlob = 1;
            cv::Mat frameXColor;
            cv::cvtColor(ForegroundMask, frameXColor, cv::COLOR_GRAY2RGB);
            #endif
            // DEBUG END

            for(std::vector<sdcv::Blob>::iterator it = blobs.begin(); it != blobs.end(); ++it) {
                normalizeArea(LaneData, it);

                // DEBUG
                #ifdef OCCLUSION_DEBUG
                cv::putText(frameXColor, ItoS(iBlob), cv::Point(it->getCentroid()), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255));
                cv::imshow("Label", frameXColor);
                std::cout << "Blob #" << iBlob << std::endl;
                it->print();
                iBlob++;
                #endif
                // DEBUG END
            }

            // DEBUG
            #ifdef OCCLUSION_DEBUG
            std::cout << "}" << std::endl;
            #endif
            // DEBUG END
        }

        // DEBUG
        #ifdef OCCLUSION_DEBUG
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        std::cout << std::endl << "[OCCLUSION DETECTOR END]" << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cv::imshow("mask", maskOclussion);
        cv::waitKey();
        #endif
        // DEBUG END
    }

    // --------------------------------------------------------------------------
    NormArea_t normalizeArea(DivLaneLine_t DivLaneLine, std::vector<sdcv::Blob>::iterator blob) {
        NormArea_t NormArea;

        NormArea.laneWidth = 0;
        NormArea.i = DivLaneLine.NbLineLanes - 2;

        for (int i = 0; i < DivLaneLine.NbLineLanes - 2; i++) {
            NormArea.x_DL1 = (blob->getCentroid().y - DivLaneLine.b_lineLanes.at(i)) / (double)DivLaneLine.m_lineLanes.at(i);
            NormArea.x_DL2 = (blob->getCentroid().y - DivLaneLine.b_lineLanes.at(i+1)) / (double)DivLaneLine.m_lineLanes.at(i+1);

            if (NormArea.x_DL2 > (double)blob->getCentroid().x) {
                NormArea.laneWidth = abs(NormArea.x_DL1 - NormArea.x_DL2);
                NormArea.i = i;
                break;
            }
        }

        NormArea.normArea = blob->getArea() / (double)(NormArea.laneWidth * NormArea.laneWidth);
        blob->setNormArea( NormArea.normArea );

        return( NormArea );
    }
};
