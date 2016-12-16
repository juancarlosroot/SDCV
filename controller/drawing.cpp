#include "drawing.h"


namespace sdcv {
    static void lineOnMouseCallback(int event, int X, int Y, int flags, void* pvUserDat);


    std::vector<cv::Point> imLine(cv::OutputArray frame, cv::String WindowName, cv::Point initialConditions) {
            int imLineUserData = 0;
            std::vector<cv::Point> linePoints;

            // Initial conditions
            if (initialConditions.x >= 0 || initialConditions.y >= 0) {
                linePoints.push_back(initialConditions);
            }

            // Set mouse callback
            cv::setMouseCallback(WindowName, lineOnMouseCallback, (void *)&linePoints);

            // Wait until line be setted
            while (cv::getWindowProperty(WindowName, 0) >= 0 && linePoints.size() < 2) {

                cv::waitKey(10);

            }

            // Unset mouse callback
            cv::setMouseCallback(WindowName, NULL, NULL);

            return( linePoints );
    }


    void vertices2polygon(std::vector<cv::Point> vertices, cv::Size frameSize, cv::OutputArray polygon) {
        cv::Mat tmp = cv::Mat::zeros(frameSize, CV_8UC1);

        // Create a polygon from vertices
        std::vector<cv::Point> approxPolygon;
        cv::approxPolyDP(vertices, approxPolygon, 1.0, true); // Ramer-Douglas-Peucker algorithm
        cv::fillConvexPoly(tmp, &approxPolygon[0], (int)approxPolygon.size(), 255, 8, 0); // Fill polygon white

        tmp.copyTo(polygon);
    }




    static void lineOnMouseCallback(int event, int X, int Y, int flags, void* pvUserDat) {
        std::vector<cv::Point> *linePoints = (std::vector<cv::Point> *)pvUserDat;
        cv::Point pt;

        switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            linePoints->push_back( cv::Point(X,Y) );
        break;

        case cv::EVENT_LBUTTONUP:

            break;

        case cv::EVENT_MOUSEMOVE:

            break;
        }
    }

}
