#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <player.h>
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int StoI(std::string str);
    bool file_exist(std::string filename);

private slots:
    void on_action_Open_video_triggered();
    void on_actionStart_triggered();
    void updatePlayerUI(QImage img);

private:
    Ui::MainWindow *ui;
    Player* myPlayer;
};

#endif // MAINWINDOW_H
