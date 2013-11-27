/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *mainLayout;
    QVBoxLayout *titleLayout;
    QLabel *titleLabel;
    QLabel *authorLabel;
    QLabel *dateLabel;
    QFrame *line_2;
    QHBoxLayout *infoLayout;
    QVBoxLayout *imgAcqMethodLayout;
    QLabel *imgAcqMethodLabel;
    QComboBox *imgAcqMethodSelector;
    QHBoxLayout *resolutionLayout;
    QLabel *widthLabel;
    QPlainTextEdit *widthTextEdit;
    QLabel *heightLabel;
    QPlainTextEdit *heightEditText;
    QHBoxLayout *rBDeviceLayout;
    QRadioButton *rB1Device;
    QRadioButton *rB2Devices;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *fileMethodLayout;
    QPlainTextEdit *imgAcqMethodPathEditText;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *imgAcqMethodFileName1EditText;
    QPlainTextEdit *imgAcqMethodFileName2EditText;
    QVBoxLayout *deviceMethodLayout;
    QHBoxLayout *spinDeviceLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label1Device;
    QSpinBox *spin1Device;
    QVBoxLayout *verticalLayout_3;
    QLabel *label2Devices;
    QSpinBox *spin2Devices;
    QPushButton *testDevicesButton;
    QFrame *line;
    QVBoxLayout *infoVerticalLayout;
    QVBoxLayout *posAcqMethodLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *cameraInfoLabel;
    QPlainTextEdit *cameraInfoPathEditTest;
    QFrame *line_6;
    QLabel *posAcqMethodLabel;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *posAcqMethodSelector;
    QCheckBox *fixCamCheckBox;
    QPlainTextEdit *posAcqMethodEditText;
    QFrame *line_3;
    QVBoxLayout *segMethodLayout;
    QLabel *segMethodLabel;
    QComboBox *segMethodSelector;
    QFrame *line_5;
    QVBoxLayout *posReconAlgLayout;
    QLabel *posReconAlgLabel;
    QComboBox *posReconAlgorithmSelector;
    QHBoxLayout *thresholdLayout;
    QLabel *thresholdLabel;
    QTextEdit *thresholdTextEdit;
    QFrame *line_4;
    QHBoxLayout *buttonLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(879, 603);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 853, 451));
        mainLayout = new QVBoxLayout(layoutWidget);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        titleLayout = new QVBoxLayout();
        titleLayout->setSpacing(6);
        titleLayout->setObjectName(QStringLiteral("titleLayout"));
        titleLabel = new QLabel(layoutWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setMinimumSize(QSize(700, 0));
        titleLabel->setMaximumSize(QSize(700, 16777215));
        titleLabel->setStyleSheet(QLatin1String("font: 45pt \"Palatino Linotype\";\n"
""));
        titleLabel->setTextFormat(Qt::PlainText);

        titleLayout->addWidget(titleLabel);

        authorLabel = new QLabel(layoutWidget);
        authorLabel->setObjectName(QStringLiteral("authorLabel"));
        authorLabel->setMinimumSize(QSize(700, 0));
        authorLabel->setMaximumSize(QSize(700, 16777215));
        authorLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        titleLayout->addWidget(authorLabel);

        dateLabel = new QLabel(layoutWidget);
        dateLabel->setObjectName(QStringLiteral("dateLabel"));
        dateLabel->setMinimumSize(QSize(700, 0));
        dateLabel->setMaximumSize(QSize(700, 16777215));
        dateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        titleLayout->addWidget(dateLabel);


        mainLayout->addLayout(titleLayout);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        mainLayout->addWidget(line_2);

        infoLayout = new QHBoxLayout();
        infoLayout->setSpacing(6);
        infoLayout->setObjectName(QStringLiteral("infoLayout"));
        infoLayout->setContentsMargins(-1, -1, -1, 0);
        imgAcqMethodLayout = new QVBoxLayout();
        imgAcqMethodLayout->setSpacing(6);
        imgAcqMethodLayout->setObjectName(QStringLiteral("imgAcqMethodLayout"));
        imgAcqMethodLabel = new QLabel(layoutWidget);
        imgAcqMethodLabel->setObjectName(QStringLiteral("imgAcqMethodLabel"));
        imgAcqMethodLabel->setMaximumSize(QSize(400, 16777215));

        imgAcqMethodLayout->addWidget(imgAcqMethodLabel);

        imgAcqMethodSelector = new QComboBox(layoutWidget);
        imgAcqMethodSelector->setObjectName(QStringLiteral("imgAcqMethodSelector"));
        imgAcqMethodSelector->setMinimumSize(QSize(400, 20));
        imgAcqMethodSelector->setMaximumSize(QSize(400, 16777215));

        imgAcqMethodLayout->addWidget(imgAcqMethodSelector);

        resolutionLayout = new QHBoxLayout();
        resolutionLayout->setSpacing(6);
        resolutionLayout->setObjectName(QStringLiteral("resolutionLayout"));
        resolutionLayout->setContentsMargins(-1, -1, -1, 0);
        widthLabel = new QLabel(layoutWidget);
        widthLabel->setObjectName(QStringLiteral("widthLabel"));
        widthLabel->setMinimumSize(QSize(100, 25));
        widthLabel->setMaximumSize(QSize(100, 16777215));

        resolutionLayout->addWidget(widthLabel);

        widthTextEdit = new QPlainTextEdit(layoutWidget);
        widthTextEdit->setObjectName(QStringLiteral("widthTextEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widthTextEdit->sizePolicy().hasHeightForWidth());
        widthTextEdit->setSizePolicy(sizePolicy);
        widthTextEdit->setMinimumSize(QSize(100, 25));
        widthTextEdit->setMaximumSize(QSize(100, 25));

        resolutionLayout->addWidget(widthTextEdit);

        heightLabel = new QLabel(layoutWidget);
        heightLabel->setObjectName(QStringLiteral("heightLabel"));
        heightLabel->setMinimumSize(QSize(100, 25));
        heightLabel->setMaximumSize(QSize(100, 16777215));

        resolutionLayout->addWidget(heightLabel);

        heightEditText = new QPlainTextEdit(layoutWidget);
        heightEditText->setObjectName(QStringLiteral("heightEditText"));
        sizePolicy.setHeightForWidth(heightEditText->sizePolicy().hasHeightForWidth());
        heightEditText->setSizePolicy(sizePolicy);
        heightEditText->setMinimumSize(QSize(100, 25));
        heightEditText->setMaximumSize(QSize(100, 25));

        resolutionLayout->addWidget(heightEditText);


        imgAcqMethodLayout->addLayout(resolutionLayout);

        rBDeviceLayout = new QHBoxLayout();
        rBDeviceLayout->setSpacing(6);
        rBDeviceLayout->setObjectName(QStringLiteral("rBDeviceLayout"));
        rBDeviceLayout->setContentsMargins(-1, -1, -1, 0);
        rB1Device = new QRadioButton(layoutWidget);
        rB1Device->setObjectName(QStringLiteral("rB1Device"));
        rB1Device->setMinimumSize(QSize(200, 20));
        rB1Device->setMaximumSize(QSize(200, 16777215));
        rB1Device->setChecked(true);

        rBDeviceLayout->addWidget(rB1Device);

        rB2Devices = new QRadioButton(layoutWidget);
        rB2Devices->setObjectName(QStringLiteral("rB2Devices"));
        rB2Devices->setMinimumSize(QSize(200, 20));
        rB2Devices->setMaximumSize(QSize(200, 16777215));

        rBDeviceLayout->addWidget(rB2Devices);


        imgAcqMethodLayout->addLayout(rBDeviceLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        fileMethodLayout = new QHBoxLayout();
        fileMethodLayout->setSpacing(6);
        fileMethodLayout->setObjectName(QStringLiteral("fileMethodLayout"));
        fileMethodLayout->setContentsMargins(-1, -1, 0, 0);
        imgAcqMethodPathEditText = new QPlainTextEdit(layoutWidget);
        imgAcqMethodPathEditText->setObjectName(QStringLiteral("imgAcqMethodPathEditText"));
        imgAcqMethodPathEditText->setEnabled(false);
        sizePolicy.setHeightForWidth(imgAcqMethodPathEditText->sizePolicy().hasHeightForWidth());
        imgAcqMethodPathEditText->setSizePolicy(sizePolicy);
        imgAcqMethodPathEditText->setMaximumSize(QSize(400, 25));

        fileMethodLayout->addWidget(imgAcqMethodPathEditText);


        verticalLayout_2->addLayout(fileMethodLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        imgAcqMethodFileName1EditText = new QPlainTextEdit(layoutWidget);
        imgAcqMethodFileName1EditText->setObjectName(QStringLiteral("imgAcqMethodFileName1EditText"));
        imgAcqMethodFileName1EditText->setEnabled(false);
        imgAcqMethodFileName1EditText->setMinimumSize(QSize(200, 25));
        imgAcqMethodFileName1EditText->setMaximumSize(QSize(200, 25));

        horizontalLayout->addWidget(imgAcqMethodFileName1EditText);

        imgAcqMethodFileName2EditText = new QPlainTextEdit(layoutWidget);
        imgAcqMethodFileName2EditText->setObjectName(QStringLiteral("imgAcqMethodFileName2EditText"));
        imgAcqMethodFileName2EditText->setEnabled(false);
        sizePolicy.setHeightForWidth(imgAcqMethodFileName2EditText->sizePolicy().hasHeightForWidth());
        imgAcqMethodFileName2EditText->setSizePolicy(sizePolicy);
        imgAcqMethodFileName2EditText->setMinimumSize(QSize(200, 25));
        imgAcqMethodFileName2EditText->setMaximumSize(QSize(200, 25));

        horizontalLayout->addWidget(imgAcqMethodFileName2EditText);


        verticalLayout_2->addLayout(horizontalLayout);


        imgAcqMethodLayout->addLayout(verticalLayout_2);

        deviceMethodLayout = new QVBoxLayout();
        deviceMethodLayout->setSpacing(6);
        deviceMethodLayout->setObjectName(QStringLiteral("deviceMethodLayout"));
        deviceMethodLayout->setContentsMargins(-1, -1, -1, 0);
        spinDeviceLayout = new QHBoxLayout();
        spinDeviceLayout->setSpacing(6);
        spinDeviceLayout->setObjectName(QStringLiteral("spinDeviceLayout"));
        spinDeviceLayout->setContentsMargins(-1, 0, -1, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label1Device = new QLabel(layoutWidget);
        label1Device->setObjectName(QStringLiteral("label1Device"));
        label1Device->setMinimumSize(QSize(200, 20));
        label1Device->setMaximumSize(QSize(200, 25));

        verticalLayout->addWidget(label1Device);

        spin1Device = new QSpinBox(layoutWidget);
        spin1Device->setObjectName(QStringLiteral("spin1Device"));
        spin1Device->setMinimumSize(QSize(200, 20));
        spin1Device->setMaximumSize(QSize(200, 25));

        verticalLayout->addWidget(spin1Device);


        spinDeviceLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label2Devices = new QLabel(layoutWidget);
        label2Devices->setObjectName(QStringLiteral("label2Devices"));
        label2Devices->setMinimumSize(QSize(200, 20));
        label2Devices->setMaximumSize(QSize(200, 25));

        verticalLayout_3->addWidget(label2Devices);

        spin2Devices = new QSpinBox(layoutWidget);
        spin2Devices->setObjectName(QStringLiteral("spin2Devices"));
        spin2Devices->setMinimumSize(QSize(200, 20));
        spin2Devices->setMaximumSize(QSize(200, 25));

        verticalLayout_3->addWidget(spin2Devices);


        spinDeviceLayout->addLayout(verticalLayout_3);


        deviceMethodLayout->addLayout(spinDeviceLayout);

        testDevicesButton = new QPushButton(layoutWidget);
        testDevicesButton->setObjectName(QStringLiteral("testDevicesButton"));
        testDevicesButton->setMinimumSize(QSize(400, 25));
        testDevicesButton->setMaximumSize(QSize(16777215, 400));

        deviceMethodLayout->addWidget(testDevicesButton);


        imgAcqMethodLayout->addLayout(deviceMethodLayout);


        infoLayout->addLayout(imgAcqMethodLayout);

        line = new QFrame(layoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        infoLayout->addWidget(line);

        infoVerticalLayout = new QVBoxLayout();
        infoVerticalLayout->setSpacing(6);
        infoVerticalLayout->setObjectName(QStringLiteral("infoVerticalLayout"));
        infoVerticalLayout->setContentsMargins(0, -1, -1, -1);
        posAcqMethodLayout = new QVBoxLayout();
        posAcqMethodLayout->setSpacing(0);
        posAcqMethodLayout->setObjectName(QStringLiteral("posAcqMethodLayout"));
        posAcqMethodLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 10);
        cameraInfoLabel = new QLabel(layoutWidget);
        cameraInfoLabel->setObjectName(QStringLiteral("cameraInfoLabel"));

        verticalLayout_4->addWidget(cameraInfoLabel);

        cameraInfoPathEditTest = new QPlainTextEdit(layoutWidget);
        cameraInfoPathEditTest->setObjectName(QStringLiteral("cameraInfoPathEditTest"));
        cameraInfoPathEditTest->setMinimumSize(QSize(400, 25));
        cameraInfoPathEditTest->setMaximumSize(QSize(400, 25));

        verticalLayout_4->addWidget(cameraInfoPathEditTest);


        posAcqMethodLayout->addLayout(verticalLayout_4);

        line_6 = new QFrame(layoutWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        posAcqMethodLayout->addWidget(line_6);

        posAcqMethodLabel = new QLabel(layoutWidget);
        posAcqMethodLabel->setObjectName(QStringLiteral("posAcqMethodLabel"));
        posAcqMethodLabel->setMinimumSize(QSize(300, 20));
        posAcqMethodLabel->setMaximumSize(QSize(300, 20));

        posAcqMethodLayout->addWidget(posAcqMethodLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        posAcqMethodSelector = new QComboBox(layoutWidget);
        posAcqMethodSelector->setObjectName(QStringLiteral("posAcqMethodSelector"));
        posAcqMethodSelector->setMinimumSize(QSize(200, 20));
        posAcqMethodSelector->setMaximumSize(QSize(200, 20));

        horizontalLayout_2->addWidget(posAcqMethodSelector);

        fixCamCheckBox = new QCheckBox(layoutWidget);
        fixCamCheckBox->setObjectName(QStringLiteral("fixCamCheckBox"));
        fixCamCheckBox->setMinimumSize(QSize(200, 0));
        fixCamCheckBox->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_2->addWidget(fixCamCheckBox);


        posAcqMethodLayout->addLayout(horizontalLayout_2);

        posAcqMethodEditText = new QPlainTextEdit(layoutWidget);
        posAcqMethodEditText->setObjectName(QStringLiteral("posAcqMethodEditText"));
        sizePolicy.setHeightForWidth(posAcqMethodEditText->sizePolicy().hasHeightForWidth());
        posAcqMethodEditText->setSizePolicy(sizePolicy);
        posAcqMethodEditText->setMinimumSize(QSize(400, 25));
        posAcqMethodEditText->setMaximumSize(QSize(300, 20));

        posAcqMethodLayout->addWidget(posAcqMethodEditText);


        infoVerticalLayout->addLayout(posAcqMethodLayout);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        infoVerticalLayout->addWidget(line_3);

        segMethodLayout = new QVBoxLayout();
        segMethodLayout->setSpacing(6);
        segMethodLayout->setObjectName(QStringLiteral("segMethodLayout"));
        segMethodLabel = new QLabel(layoutWidget);
        segMethodLabel->setObjectName(QStringLiteral("segMethodLabel"));
        segMethodLabel->setMinimumSize(QSize(400, 20));
        segMethodLabel->setMaximumSize(QSize(400, 20));

        segMethodLayout->addWidget(segMethodLabel);

        segMethodSelector = new QComboBox(layoutWidget);
        segMethodSelector->setObjectName(QStringLiteral("segMethodSelector"));
        segMethodSelector->setMinimumSize(QSize(400, 20));
        segMethodSelector->setMaximumSize(QSize(40, 20));

        segMethodLayout->addWidget(segMethodSelector);


        infoVerticalLayout->addLayout(segMethodLayout);

        line_5 = new QFrame(layoutWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        infoVerticalLayout->addWidget(line_5);

        posReconAlgLayout = new QVBoxLayout();
        posReconAlgLayout->setSpacing(6);
        posReconAlgLayout->setObjectName(QStringLiteral("posReconAlgLayout"));
        posReconAlgLabel = new QLabel(layoutWidget);
        posReconAlgLabel->setObjectName(QStringLiteral("posReconAlgLabel"));
        posReconAlgLabel->setMinimumSize(QSize(300, 20));
        posReconAlgLabel->setMaximumSize(QSize(300, 20));

        posReconAlgLayout->addWidget(posReconAlgLabel);

        posReconAlgorithmSelector = new QComboBox(layoutWidget);
        posReconAlgorithmSelector->setObjectName(QStringLiteral("posReconAlgorithmSelector"));
        posReconAlgorithmSelector->setMinimumSize(QSize(400, 20));
        posReconAlgorithmSelector->setMaximumSize(QSize(400, 20));

        posReconAlgLayout->addWidget(posReconAlgorithmSelector);

        thresholdLayout = new QHBoxLayout();
        thresholdLayout->setSpacing(6);
        thresholdLayout->setObjectName(QStringLiteral("thresholdLayout"));
        thresholdLayout->setSizeConstraint(QLayout::SetMinimumSize);
        thresholdLayout->setContentsMargins(-1, -1, -1, 0);
        thresholdLabel = new QLabel(layoutWidget);
        thresholdLabel->setObjectName(QStringLiteral("thresholdLabel"));
        sizePolicy.setHeightForWidth(thresholdLabel->sizePolicy().hasHeightForWidth());
        thresholdLabel->setSizePolicy(sizePolicy);
        thresholdLabel->setMinimumSize(QSize(200, 20));
        thresholdLabel->setMaximumSize(QSize(200, 20));

        thresholdLayout->addWidget(thresholdLabel);

        thresholdTextEdit = new QTextEdit(layoutWidget);
        thresholdTextEdit->setObjectName(QStringLiteral("thresholdTextEdit"));
        sizePolicy.setHeightForWidth(thresholdTextEdit->sizePolicy().hasHeightForWidth());
        thresholdTextEdit->setSizePolicy(sizePolicy);
        thresholdTextEdit->setMinimumSize(QSize(200, 20));
        thresholdTextEdit->setMaximumSize(QSize(200, 20));

        thresholdLayout->addWidget(thresholdTextEdit);


        posReconAlgLayout->addLayout(thresholdLayout);


        infoVerticalLayout->addLayout(posReconAlgLayout);


        infoLayout->addLayout(infoVerticalLayout);


        mainLayout->addLayout(infoLayout);

        line_4 = new QFrame(layoutWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        mainLayout->addWidget(line_4);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(6);
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        buttonLayout->setContentsMargins(-1, -1, -1, 10);
        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy1);
        startButton->setMinimumSize(QSize(400, 20));
        startButton->setMaximumSize(QSize(400, 25));

        buttonLayout->addWidget(startButton);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        sizePolicy1.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy1);
        stopButton->setMinimumSize(QSize(400, 20));
        stopButton->setMaximumSize(QSize(400, 25));

        buttonLayout->addWidget(stopButton);


        mainLayout->addLayout(buttonLayout);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 879, 21));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0));
#ifndef QT_NO_TOOLTIP
        titleLabel->setToolTip(QApplication::translate("MainWindowClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt;\">Visual Tracking UI</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        titleLabel->setText(QApplication::translate("MainWindowClass", "Visual Tracking UI", 0));
        authorLabel->setText(QApplication::translate("MainWindowClass", "Author: Pablo Ram\303\263n Soria", 0));
        dateLabel->setText(QApplication::translate("MainWindowClass", "Date: 2013/11/17", 0));
        imgAcqMethodLabel->setText(QApplication::translate("MainWindowClass", "Image Acquisition Method:", 0));
        imgAcqMethodSelector->clear();
        imgAcqMethodSelector->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "Device/s", 0)
         << QApplication::translate("MainWindowClass", "Images", 0)
         << QApplication::translate("MainWindowClass", "Video", 0)
        );
        widthLabel->setText(QApplication::translate("MainWindowClass", "Width: ", 0));
        widthTextEdit->setPlainText(QApplication::translate("MainWindowClass", "320", 0));
        heightLabel->setText(QApplication::translate("MainWindowClass", "Height: ", 0));
        heightEditText->setPlainText(QApplication::translate("MainWindowClass", "240", 0));
        rB1Device->setText(QApplication::translate("MainWindowClass", "1 Device", 0));
        rB2Devices->setText(QApplication::translate("MainWindowClass", "2 Devices", 0));
        imgAcqMethodPathEditText->setPlainText(QApplication::translate("MainWindowClass", "C:/Programming/Imagenes Stereo Tracking/P1_640x480/Images/", 0));
        imgAcqMethodFileName1EditText->setPlainText(QApplication::translate("MainWindowClass", "img%d_cam1.jpg", 0));
        imgAcqMethodFileName2EditText->setPlainText(QApplication::translate("MainWindowClass", "img%d_cam2.jpg", 0));
        label1Device->setText(QApplication::translate("MainWindowClass", "Device 1:", 0));
        label2Devices->setText(QApplication::translate("MainWindowClass", "Device 2:", 0));
        testDevicesButton->setText(QApplication::translate("MainWindowClass", "Test Devices", 0));
        cameraInfoLabel->setText(QApplication::translate("MainWindowClass", "Camera Info", 0));
        cameraInfoPathEditTest->setPlainText(QApplication::translate("MainWindowClass", "C:/Programming/Imagenes Stereo Tracking/P1_640x480/cameraInfo.txt", 0));
        posAcqMethodLabel->setText(QApplication::translate("MainWindowClass", "Position Acquisition Method:", 0));
        posAcqMethodSelector->clear();
        posAcqMethodSelector->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "File", 0)
         << QApplication::translate("MainWindowClass", "Vicon", 0)
        );
        fixCamCheckBox->setText(QApplication::translate("MainWindowClass", "Fixed Cameras", 0));
        posAcqMethodEditText->setPlainText(QApplication::translate("MainWindowClass", "C:/Programming/Imagenes Stereo Tracking/P1_640x480/ViconData2.txt", 0));
        segMethodLabel->setText(QApplication::translate("MainWindowClass", "Segmentation Method:", 0));
        segMethodSelector->clear();
        segMethodSelector->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "Color Cluster Segmentation", 0)
        );
        posReconAlgLabel->setText(QApplication::translate("MainWindowClass", "Position Reconstructor Algorithm:", 0));
        posReconAlgorithmSelector->clear();
        posReconAlgorithmSelector->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "Single Camera Ground Tracking", 0)
         << QApplication::translate("MainWindowClass", "Stereo Tracking", 0)
        );
        thresholdLabel->setText(QApplication::translate("MainWindowClass", "Threshold", 0));
        startButton->setText(QApplication::translate("MainWindowClass", "Start", 0));
        stopButton->setText(QApplication::translate("MainWindowClass", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
