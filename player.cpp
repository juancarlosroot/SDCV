#include "player.h"



Player::Player(QObject *parent)
 : QThread(parent)
{
    stop = true;
    key = 0;
    NbFrame = 0;
}
Player::~Player()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Player::Stop()
{
    stop = true;
}

void Player::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

bool Player::isStopped() const{
    return this->stop;
}

bool Player::loadVideo(String filename) {

    QString str = filename.c_str();
    QStringList query = str.split(".");
    QString m_String = query.at(0);
    s_filename = m_String.toStdString();// just name

    cv::VideoCapture video(filename);
    capture = video;
    fps = (int)capture.get(cv::CAP_PROP_FPS);

    qDebug()<< str;

    initAllROI();


    return true;
}

void Player::initAllROI()
{

    // ROI
    sdcv::ROI roiT(s_filename);
    roi = roiT;

    roi.create(s_filename + ".mp4" , 5, true);// Crear ROI false para crear archivo(sobreescribir)

    // DETECTOR
    sdcv::Detector detectorT(100, -1, true, true);
    detector = detectorT;
    detector.setROI(roi);
    detector.setOclussion(true);

    // TRACKER
    sdcv::Tracker trackerT(8, 10, fps, roi);
    tracker = trackerT;

    // CLASSIFIER
    thresVals.push_back(.12);
    thresVals.push_back(1.2);
    thresVals.push_back(100);
    thresVals.push_back(0);

    names.push_back("Small");
    names.push_back("Midsize");
    names.push_back("Large");
    names.push_back("falsePositive");

    sdcv::Classifier classifierT(4, thresVals, names);
    classifier = classifierT;
    // Hasta aquí todo bien
    //debug en lo siguiente

}

void Player::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void Player::run()
{
    if(!stop){
        int delay = 15;
        while( 1 ) {
            cv::Mat frame, Roi, mask;

            if( !capture.read(frame) ) break;		// Video end

            detector.detect(frame, mask);
            detector.draw( frame );

            if( NbFrame > 1 ) tracker.run(detector.getBlobList(), classifier);
//            cv::imshow("frame", frame);
//            cv::imshow("mask", mask);

            if (frame.channels()== 3){
                cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBframe.data),
                                  RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
            }
            else
            {
                img = QImage((const unsigned char*)(frame.data),
                                     frame.cols,frame.rows,QImage::Format_Indexed8);
            }
            emit processedImage(img);
            this->msleep(delay);

            NbFrame++;

            key = cv::waitKey(fps);
            if( key == KEY_SPACE) cv::waitKey();
            else if( key == KEY_ESC ) break;
        }
        cv::waitKey();
    }
}



/***********************************************************************/
/*                R E F E R E N C E   F U N C T I O N S                */
/***********************************************************************/
std::string ItoS(int Number) {
    std::string str;          // string which will contain the result

    std::ostringstream bridge;   // stream used for the conversion

    bridge << Number;      // insert the textual representation of 'Number' in the characters in the stream

    str = bridge.str(); // set 'Result' to the contents of the stream

    return( str );
}

int StoI(std::string str) {

    return 0;
}


bool file_exist(std::string filename) {
    std::ifstream file( filename );

    bool bExist = file.is_open();

    file.close();

    return( bExist );



}
