/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_New;
    QAction *action_Open_video;
    QAction *action_Close;
    QAction *action_Video_Information;
    QAction *action_Set_ROI;
    QAction *actionStart;
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionVehicle_Trajectory;
    QAction *action_Save_to_Excel;
    QAction *actionAbout;
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_View;
    QMenu *menu_Tools;
    QMenu *menu_Help;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(973, 638);
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QStringLiteral("action_New"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/ic_insert_drive_file_black_48dp/android/drawable-xxxhdpi/ic_insert_drive_file_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_New->setIcon(icon);
        action_Open_video = new QAction(MainWindow);
        action_Open_video->setObjectName(QStringLiteral("action_Open_video"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/ic_video_call_black_48dp/android/drawable-xxxhdpi/ic_video_call_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open_video->setIcon(icon1);
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName(QStringLiteral("action_Close"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/ic_close_black_64dp/web/ic_close_black_64dp_2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Close->setIcon(icon2);
        action_Video_Information = new QAction(MainWindow);
        action_Video_Information->setObjectName(QStringLiteral("action_Video_Information"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/ic_announcement_black_18dp/android/drawable-xxxhdpi/ic_announcement_black_18dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Video_Information->setIcon(icon3);
        action_Set_ROI = new QAction(MainWindow);
        action_Set_ROI->setObjectName(QStringLiteral("action_Set_ROI"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/ic_panorama_vertical_black_48dp/android/drawable-xxxhdpi/ic_panorama_vertical_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Set_ROI->setIcon(icon4);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/ic_play_arrow_black_48dp/android/drawable-xxxhdpi/ic_play_arrow_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon5);
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/ic_pause_black_48dp/android/drawable-xxxhdpi/ic_pause_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon6);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/ic_stop_black_48dp/android/drawable-xxxhdpi/ic_stop_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon7);
        actionVehicle_Trajectory = new QAction(MainWindow);
        actionVehicle_Trajectory->setObjectName(QStringLiteral("actionVehicle_Trajectory"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/ic_directions_car_black_48dp/android/drawable-xxxhdpi/ic_directions_car_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionVehicle_Trajectory->setIcon(icon8);
        action_Save_to_Excel = new QAction(MainWindow);
        action_Save_to_Excel->setObjectName(QStringLiteral("action_Save_to_Excel"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/ic_assessment_black_48dp/android/drawable-xxxhdpi/ic_assessment_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Save_to_Excel->setIcon(icon9);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/ic_info_black_48dp/android/drawable-xxxhdpi/ic_info_black_48dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon10);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(2, 3, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setItem(3, 1, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setItem(3, 3, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setItem(4, 2, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setItem(4, 3, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setItem(5, 0, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setItem(5, 1, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget->setItem(5, 2, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget->setItem(5, 3, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget->setItem(6, 0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setItem(6, 1, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget->setItem(6, 2, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget->setItem(6, 3, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget->setItem(7, 0, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget->setItem(7, 1, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget->setItem(7, 2, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget->setItem(7, 3, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget->setItem(8, 0, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget->setItem(8, 1, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget->setItem(8, 2, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget->setItem(8, 3, __qtablewidgetitem50);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(450, 40, 511, 531));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 10, 431, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 30, 431, 281));
        label_5->setStyleSheet(QStringLiteral("Background-color: #000;"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 320, 431, 241));
        label_6->setStyleSheet(QStringLiteral("Background-color: #000;"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(448, 10, 511, 23));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEdit_3 = new QLineEdit(layoutWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout->addWidget(lineEdit_3);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setMaximumSize(QSize(1000, 26));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 973, 22));
        sizePolicy.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy);
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QStringLiteral("menu_View"));
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QStringLiteral("menu_Tools"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QStringLiteral("menu_Help"));
        MainWindow->setMenuBar(menuBar);

        mainToolBar->addAction(action_New);
        mainToolBar->addAction(action_Set_ROI);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionStart);
        mainToolBar->addAction(actionPause);
        mainToolBar->addAction(actionStop);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionVehicle_Trajectory);
        mainToolBar->addAction(action_Save_to_Excel);
        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menuBar->addAction(menu_Tools->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_New);
        menu_File->addAction(action_Open_video);
        menu_File->addSeparator();
        menu_File->addAction(action_Close);
        menu_View->addAction(action_Video_Information);
        menu_Tools->addAction(action_Set_ROI);
        menu_Tools->addSeparator();
        menu_Tools->addAction(actionStart);
        menu_Tools->addAction(actionPause);
        menu_Tools->addAction(actionStop);
        menu_Tools->addSeparator();
        menu_Tools->addAction(actionVehicle_Trajectory);
        menu_Tools->addAction(action_Save_to_Excel);
        menu_Help->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_New->setText(QApplication::translate("MainWindow", "&New", 0));
        action_Open_video->setText(QApplication::translate("MainWindow", "&Open video", 0));
        action_Close->setText(QApplication::translate("MainWindow", "&Close", 0));
        action_Video_Information->setText(QApplication::translate("MainWindow", "&Video Information", 0));
        action_Set_ROI->setText(QApplication::translate("MainWindow", "&Set ROI", 0));
        actionStart->setText(QApplication::translate("MainWindow", "&Start", 0));
        actionPause->setText(QApplication::translate("MainWindow", "&Pause", 0));
        actionStop->setText(QApplication::translate("MainWindow", "&Stop", 0));
        actionVehicle_Trajectory->setText(QApplication::translate("MainWindow", "&Vehicle Trajectory", 0));
        action_Save_to_Excel->setText(QApplication::translate("MainWindow", "&Save to Excel", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Time", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Estimated Area", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Frames Count", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Visible Count", 0));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 0);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 1);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "1", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 2);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 3);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "3", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 4);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "2", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(1, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(1, 1);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "3", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(1, 2);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(1, 3);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "5", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(2, 0);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(2, 1);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "4", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(2, 2);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(2, 3);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "6", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(3, 0);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(3, 1);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "6", 0));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(3, 2);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(3, 3);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "8", 0));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(4, 0);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(4, 1);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "8", 0));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(4, 2);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(4, 3);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "1", 0));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(5, 0);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->item(5, 1);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "11", 0));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->item(5, 2);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->item(5, 3);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "3", 0));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->item(6, 0);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->item(6, 1);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "13", 0));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->item(6, 2);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->item(6, 3);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "4", 0));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->item(7, 0);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->item(7, 1);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "54", 0));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->item(7, 2);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->item(7, 3);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "4", 0));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget->item(8, 0);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "3452", 0));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget->item(8, 1);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "65", 0));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget->item(8, 2);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "423", 0));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget->item(8, 3);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "5", 0));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label_4->setText(QApplication::translate("MainWindow", "Resolution: 240 x 420", 0));
        label_5->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_6->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label->setText(QApplication::translate("MainWindow", "Small", 0));
        label_2->setText(QApplication::translate("MainWindow", "Mid size", 0));
        label_3->setText(QApplication::translate("MainWindow", "Large", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menu_View->setTitle(QApplication::translate("MainWindow", "&View", 0));
        menu_Tools->setTitle(QApplication::translate("MainWindow", "&Tools", 0));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
