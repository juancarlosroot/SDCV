#ifndef PLAYER_H
#define PLAYER_H

#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#elif defined(__gnu_linux__) || defined(__linux__)
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define KEY_ESC		27
#define KEY_SPACE	32
#define KEY_0		49
#define KEY_1		50
#define KEY_2		51
#define MIN_BLOB_AREA	100

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
#include <QString>
#include <QString>
#include <QTextStream>
#include <string>
#include <iostream>
#include <stdint.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>


#include "controller/blob.h"
#include "controller/roi.h"
#include "controller/drawing.h"
#include "controller/detector.h"
#include "controller/tracker.h"

using namespace cv;
class Player : public QThread
{
    Q_OBJECT

 private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture capture;
    Mat RGBframe;
    QImage img;
    int key, NbFrame;
    String s_filename;
    int fps;
    sdcv::ROI roi;
    sdcv::Detector detector;
    sdcv::Classifier classifier;
    std::vector<std::string> names;
    std::vector<double> thresVals;
    sdcv::Tracker tracker;
    void initAllROI();

 signals:
 //Signal to output frame to be displayed
      void processedImage(const QImage &image);
 protected:
     void run();
     void msleep(int ms);
 public:
    //Constructor
    Player(QObject *parent = 0);
    //Destructor
    ~Player();
    //Load a video from memory
    bool loadVideo(String filename);
    //Play the video
    void Play();
    //Stop the video
    void Stop();
    //check if the player has been stopped
    bool isStopped() const;
    std::string ItoS(int Number);
    int StoI(std::string str);
    bool file_exist(std::string filename);
};
#endif // VIDEOPLAYER_H
