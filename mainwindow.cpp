#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>

/* ---------------------------*/
/*       Library Include       */
/* ---------------------------*/
#include <opencv2/opencv.hpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    menuBar()->setNativeMenuBar(false);
    QImage image(":/Frame1945.bmp");
    ui->label_5->setPixmap(QPixmap::fromImage(image));

    QImage imageMask(":/Fore2325.bmp");
    ui->label_6->setPixmap(QPixmap::fromImage(imageMask));

    myPlayer = new Player();
    connect(
                myPlayer,
                SIGNAL(processedImage(QImage)),
                this,
                SLOT(updatePlayerUI(QImage))
    );

//    while( 1 ) {
        

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
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
}

void MainWindow::on_action_Open_video_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                          tr("Open Video"), ".",
                                          tr("Video Files (*.avi *.mpg *.mp4)"));
    if (!filename.isEmpty()){
        if (!myPlayer->loadVideo(filename.toStdString().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
    }
}

void MainWindow::on_actionStart_triggered()
{
    if (myPlayer->isStopped())
    {
        myPlayer->Play();
    }else
    {
        myPlayer->Stop();
    }
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->label_5->setAlignment(Qt::AlignCenter);
        ui->label_5->setPixmap(
                    QPixmap::fromImage(img).scaled(
                        ui->label_5->width(),
                        ui->label_5->height(),
                        Qt::IgnoreAspectRatio,
                        Qt::FastTransformation
                    )
        );
    }
}

int MainWindow::StoI(std::string str) {

    return 0;
}


bool MainWindow::file_exist(std::string filename) {
    std::ifstream file( filename );

    bool bExist = file.is_open();

    file.close();

    return( bExist );



}
