#include "roi.h"

namespace sdcv {
    /* PUBLIC METHODS */
    // Constructor
    ROI::ROI(){
        this->name = "ROIdata";
        this->NbLineLanes = 0;
        this->NbRegions = 0;
    }
    ROI::ROI( cv::String name ) {
        this->name = name;
        this->NbLineLanes = 0;
        this->NbRegions = 0;
    }


    // Get methods
    cv::Rect ROI::getBbox( void ) { return bbox; }
    std::vector<cv::Point> ROI::getVertices( void ) { return vertices; }
    cv::Mat ROI::getMask( void ) { return( this->mask ); }
    int ROI::getArea(void){ return area; }

    //cv::Mat ROI::getLanesLine( void ) { return this->lineLane; }
    //int ROI::getNumberLineLanes( void ) { return this->NbLineLanes; }
    DivLaneLine_t ROI::getLaneData( void ) {
        DivLaneLine_t DivLaneLines;

        DivLaneLines.lineLane = this->lineLane;
        DivLaneLines.b_lineLanes = this->b_lineLanes;
        DivLaneLines.m_lineLanes = this->m_lineLanes;
        DivLaneLines.DL_mask = this->DL_mask;
        DivLaneLines.NbLineLanes = this->NbLineLanes;

        return DivLaneLines;
    }
    int ROI::getNumLanes( void ) { return(this->NbLineLanes); }
    cv::Mat ROI::getDivLineLane( void ) { return(this->lineLane); }
    std::vector< double > ROI::getSlopeLane( void ) { return(this->m_lineLanes); }
    std::vector< double > ROI::getIntersecLane( void ) { return(this->b_lineLanes); }
    cv::Mat ROI::getDivLaneMask(int Nb) {
        CV_Assert( Nb < (int)this->DL_mask.size() );
        return(this->DL_mask.at(Nb));
    }
    std::vector< cv::Mat > ROI::getDivLaneMask( void ) { return(this->DL_mask); }

    std::vector< cv::Point > ROI::getLineDetection( void ) { return(this->lineDetection); }
    cv::Point2f ROI::getCenterLineDetection( void ) { return(this->cLineDetection); }

    // Set methods
    void ROI::setVertices(std::vector<cv::Point> vertices) { this->vertices = vertices; }

    void ROI::setName(cv::String name) { this->name = name; }


    // Action methods
    void ROI::create(cv::String videonamePath, int NbDivLines, bool bLoad) {
        if( bLoad && load()) return;

        // Video objects define
        cv::VideoCapture video(videonamePath);
        cv::Mat frame;

        // Load a frame from video
        CV_Assert( video.isOpened() );
        video.read(frame);
        video.release();
        cv::namedWindow("ROI", CV_GUI_EXPANDED);
        cv::imshow("ROI", frame);

        // Setting ROI coordinates
        getRoiPoly( frame );
        CV_Assert( !this->mask.empty() );


        // Setting lanes's division lines
        this->NbLineLanes = NbDivLines;
        cv::Mat laneTmp = cv::Mat::zeros(cv::Size(NbDivLines, 4), CV_64F);

        for (int i = 0; i < NbDivLines; i++) {
            std::vector<cv::Point> lineTmp = imLine(frame, "ROI", cv::Point(-1, -1));
            CV_Assert(lineTmp.size() == 2);

            cv::line(frame, lineTmp.at(0), lineTmp.at(1), cv::Scalar(0, 0, 255), 2); // Draw line
            cv::imshow("ROI", frame);

            // y_major to y_minor
            if (lineTmp.at(0).y < lineTmp.at(1).y) {
                cv::Point pointTemp = lineTmp.at(0);
                lineTmp.at(0) = lineTmp.at(1);
                lineTmp.at(1) = pointTemp;
            }

            laneTmp.at<double>(i, 0) = lineTmp.at(0).x;
            laneTmp.at<double>(i, 1) = lineTmp.at(0).y;
            laneTmp.at<double>(i, 2) = lineTmp.at(1).x;
            laneTmp.at<double>(i, 3) = lineTmp.at(1).y;

            double dblAuxVar = (lineTmp.at(0).y - lineTmp.at(1).y) / (double)(lineTmp.at(0).x - lineTmp.at(1).x); // m = (y2 - y1)/(x2 - x1)
            this->m_lineLanes.push_back( dblAuxVar );

            dblAuxVar = (lineTmp.at(0).y - (double)(dblAuxVar * lineTmp.at(0).x)); // b = y1 - m*x1
            this->b_lineLanes.push_back( dblAuxVar );
        }
        laneTmp.convertTo(this->lineLane, CV_16S);

        for(int i = 0; i < this->lineLane.rows; i++) {
            cv::Mat laneMask = cv::Mat::zeros(this->mask.size(), this->mask.type());

            laneMask.setTo(cv::Scalar(255, 255, 255));

            cv::Point pt1 = cv::Point(this->lineLane.at<short>(i, 0), this->lineLane.at<short>(i, 1));
            cv::Point pt2 = cv::Point(this->lineLane.at<short>(i, 2), this->lineLane.at<short>(i, 3));
            cv::line(laneMask, pt1, pt2, cv::Scalar(0, 0, 0), 2);

            DL_mask.push_back( laneMask );
        }

        std::cout << "lanePosition = " << std::endl;
        std::cout << this->lineLane << std::endl;
        std::cout << "m_lineLanes = " << std::endl;
        std::cout << cv::format(this->m_lineLanes, 0) << std::endl;
        std::cout << "b_lineLanes = " << std::endl;
        std::cout << cv::format(this->b_lineLanes, 0) << std::endl;

        /* Setting line detection */
        std::vector<cv::Point> linePts = imLine(frame, "ROI", cv::Point(-1, -1));

        CV_Assert(linePts.size() == 2);
        cv::line(frame, linePts.at(0), linePts.at(1), cv::Scalar(255, 0, 0), 2);
        cv::imshow("ROI", frame);

        this->lineDetection = linePts;

        // x_minor to x_major
        if( lineDetection.at(0).x > lineDetection.at(1).x ) {
            cv::Point pt = this->lineDetection.at(0);

            this->lineDetection.at(0) = this->lineDetection.at(1);
            this->lineDetection.at(1) = pt;
        }

        this->cLineDetection = cv::Point2f((this->lineDetection.at(0).x + this->lineDetection.at(1).x) /(float)2, (this->lineDetection.at(0).y + this->lineDetection.at(1).y) /(float)2);
        std::cout << "linePosition = [" << this->lineDetection.at(0).x << ", " << this->lineDetection.at(0).y << ", " << this->lineDetection.at(1).x << ", " << this->lineDetection.at(1).y << "]" << std::endl << std::endl;

        // Debugging
        cv::imwrite(name + ".bmp", this->mask);
        cv::waitKey(0);
        cv::destroyAllWindows();

        save();

    }

    void ROI::save( void ) {
        std::string filename = name + ".yml";

        cv::FileStorage fs(name + ".yml", cv::FileStorage::WRITE);

        fs << "vertices"			<< this->vertices;
        fs << "area"				<< this->area;
        fs << "bbox"				<< this->bbox;
        fs << "mask"				<< this->mask;

        fs << "NbDivLines"			<< this->NbLineLanes;
        fs << "lanePosition"		<< this->lineLane;
        fs << "slopeDivLines"		<< this->m_lineLanes;
        fs << "interceptDivLines"	<< this->b_lineLanes;
        fs << "LaneMask"			<< this->DL_mask;

        fs << "linePosition"		<< this->lineDetection;
        fs << "cDivLines"			<< this->cLineDetection;
        fs << "LineArea"			<< this->LineArea;

        fs << "NbRegions"			<< this->NbRegions;
    }

    bool ROI::load( void ) {
        cv::FileStorage fs(this->name + ".yml", cv::FileStorage::READ);
        bool exitSuccess = false;

        if( fs.isOpened() ) {
            exitSuccess = true;
            fs["vertices"]			>> this->vertices;
            fs["area"]				>> this->area;
            fs["bbox"]				>> this->bbox;
            fs["mask"]				>> this->mask;

            fs["NbDivLines"]		>> this->NbLineLanes;
            fs["lanePosition"]		>> this->lineLane;
            fs["slopeDivLines"]		>> this->m_lineLanes;
            fs["interceptDivLines"]	>> this->b_lineLanes;
            fs["LaneMask"]			>> this->DL_mask;

            fs["linePosition"]		>> this->lineDetection;
            fs["cDivLines"]			>> this->cLineDetection;
            fs["LineArea"]			>> this->LineArea;

            fs["NbRegions"]			>> this->NbRegions;

        }

        return( exitSuccess );
    }


    void ROI::apply(cv::InputArray frame, cv::OutputArray image) {
        CV_Assert( !this->mask.empty() );
        CV_Assert( !frame.empty() );

        frame.copyTo(image, this->mask);
    }

    // Testing methods
    void ROI::testing(eROItest en2Test, cv::Mat frame, std::vector<cv::Point> input) {
        cv::Mat aux, aux1;
        std::vector< std::vector<cv::Point> > contours;
        std::vector<cv::Point> approxPolygon;
        int NbLanes;
        bool bInit = true;
        std::cout << std::endl << std::endl << "[TESTING]: ROI {" << std::endl << std::endl;
        std::cout << "\tModule: ";

        switch( en2Test ) {
            case ROI_TEST_VERTEX:
                CV_Assert( input.size() == 4 );
                std::cout << "Vertices" << std::endl;

                vertices2polygon(input, frame.size(), aux);
                cv::findContours(aux, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
                cv::approxPolyDP(contours[0], approxPolygon, 1.0, true); // Ramer-Douglas-Peucker algorithm

//                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                std::cout << "[\tRUN\t]\t";
//                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                std::cout << "Trapezoidal region" << std::endl;

                if(approxPolygon.size() > 5 || approxPolygon.size() < 4) {
//                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    std::cout << "[\tFAILED\t]\t";
                } else {
//                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    std::cout << "[\tPASSED\t]\t";
                    this->getRoiPoly(frame, input);
                }
//                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 );
                std::cout << "Size:" << approxPolygon.size() << std::endl;
            break;

            case ROI_TEST_DIV_LINES:
                CV_Assert( input.size() > 0 );
                NbLanes = input.at(0).x;
                std::cout << "Divided Lane's Line" << std::endl;


                if( input.size() - 1  != NbLanes) bInit = false;
//                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                std::cout << "[\tRUN\t]\t";
//                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                std::cout << "Lines" << std::endl;
//                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bInit ? FOREGROUND_GREEN:FOREGROUND_RED);
                if( !bInit ) std::cout << "[\tFAILED\t]\t";
                else std::cout << "[\tPASSED\t]\t";
//                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 );
                std::cout << input.size() - 1 << "\\" << NbLanes << std::endl;


            break;

            case ROI_TEST_LINE_DETECTION:

            break;
        }

        std::cout << std::endl << "}" << std::endl << std::endl;
        std::cin.get();

    }


    // Destructor
    ROI::~ROI( void ) {

    }

    /* PROTECTED METHODS */
    void ROI::getRoiPoly( cv::OutputArray frame, std::vector<cv::Point> vertex) {
        unsigned int NbLines = 4, idx = 0;
        cv::Point initialCondition(-1, -1);
        cv::Mat frameTmp;

        frame.copyTo( frameTmp );

        // Get ROI vertices
        if( vertex.size() == 0 ) {
            while ( NbLines ) {
                bool validPoint = true;
                std::vector<cv::Point> pt  = imLine(frame, "ROI", initialCondition);
                CV_Assert(pt.size() == 2);

                cv::Rect r(pt.at(0) - cv::Point(15,15), cv::Size(30, 30));
                if( pt.at(1).inside(r) ) validPoint = false;
                std::cout << "Rec = " << r << std::endl;
                std::cout << "Point: " << pt.at(1) << std::endl;

                if( validPoint ) {
                    cv::line(frameTmp, pt.at(0), pt.at(1), cv::Scalar(0, 255, 0, 0.8), 2); // Draw line
                    cv::rectangle(frameTmp, cv::Point(pt.at(0).x - 5, pt.at(0).y - 5), cv::Point(pt.at(0).x + 5, pt.at(0).y + 5), cv::Scalar(255, 0, 30, 0.8));

                    this->vertices.push_back( pt.at(0) );

                    NbLines--;

                    initialCondition = pt.at(1);

                    cv::imshow("ROI", frameTmp);
                } else {
                    cv::Mat tmp;
                    frameTmp.copyTo( tmp );
                    cv::line(tmp, pt.at(0), pt.at(1), cv::Scalar(0, 0, 255), 2); // Draw line
                    cv::imshow("ROI", tmp);
                    cv::waitKey(1000);
                    cv::imshow("ROI", frameTmp);
                }

            }
            frameTmp.copyTo( frame );
        } else {
            this->vertices.clear();
            for(int i = 0; i < vertex.size(); i++) {
                this->vertices.push_back( vertex.at(i) );
            }
        }

        // Vertices to ROI
        CV_Assert( this->vertices.size() == 4 );
        vertices2polygon(this->vertices, frame.size(), this->mask);

        std::vector< std::vector<cv::Point> > contours;
        cv::Mat RoiMask;
        this->mask.copyTo( RoiMask );
        cv::findContours(RoiMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        CV_Assert(contours.size() == 1);

        std::vector<cv::Point> approxPolygon;
        cv::approxPolyDP(contours[0], approxPolygon, 1.0, true); // Ramer-Douglas-Peucker algorithm

        CV_Assert( approxPolygon.size() == 4 || approxPolygon.size() == 5 );

        frame.copyTo( frameTmp );
        cv::Mat img, imgtmp;
        frame.copyTo(img);
        frameTmp.copyTo(imgtmp, this->mask);
        cv::drawContours(imgtmp, contours, 0, cv::Scalar(0, 255, 0), CV_FILLED);
        cv::addWeighted(imgtmp, 0.1, img, 1, 0, img, -1);
        cv::imshow("ROI", img);

        Blob blob( contours[0] );
        this->area = blob.getArea();
        this->bbox = blob.getBBox();

        img.copyTo(frame);
    }
};
