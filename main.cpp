#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



//Intento de correr todo en consola (sin GUI)

//    int key = 0, NbFrame = 0;
//    cv::String videoname = "/Users/juancarlosroot/Desktop/VIDEOS/V01-2016-07-10";

//    // Video Reader
//    cv::VideoCapture video(videoname + ".mp4");
//    int fps = (int)video.get(cv::CAP_PROP_FPS);

//    // ROI
//    sdcv::ROI roi(videoname);
//    roi.create(videoname + ".mp4", 4, true);

//    // DETECTOR
//    sdcv::Detector detector(100, -1, true, true);
//    detector.setROI(roi);
//    detector.setOclussion(true);

//    // TRACKER
//    sdcv::Tracker tracker(8, 10, fps, roi);

//    // CLASSIFIER
//    std::vector<double> thresVals;
//    thresVals.push_back(.12);
//    thresVals.push_back(1.2);
//    thresVals.push_back(100);
//    thresVals.push_back(0);

//    std::vector<std::string> names;
//    names.push_back("Small");
//    names.push_back("Midsize");
//    names.push_back("Large");
//    names.push_back("falsePositive");

//    sdcv::Classifier classifier(4, thresVals, names);
//    while( 1 ) {
//        cv::Mat frame, Roi, mask;

//        if( !video.read(frame) ) break;		// Video end

//        detector.detect(frame, mask);
//        detector.draw( frame );

//        if( NbFrame > 1 ) tracker.run(detector.getBlobList(), classifier);
//        cv::imshow("frame", frame);
//        cv::imshow("mask", mask);
//        NbFrame++;

//        key = cv::waitKey(fps);
//        if( key == KEY_SPACE) cv::waitKey();
//        else if( key == KEY_ESC ) break;
//    }
//    cv::waitKey();

    return a.exec();
}
