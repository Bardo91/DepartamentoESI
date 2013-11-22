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
    QVBoxLayout *imgAcqMethodLayout;
    QLabel *imgAcqMethodLabel;
    QComboBox *imgAcqMethodSelector;
    QHBoxLayout *resolutionLayout;
    QLabel *widthLabel;
    QPlainTextEdit *widthTextEdit;
    QLabel *heightLabel;
    QPlainTextEdit *heightEditText;
    QHBoxLayout *fileMethodLayout;
    QPlainTextEdit *imgAcqMethodPathEditText;
    QPlainTextEdit *imgAcqMethodFileNameEditText;
    QVBoxLayout *deviceMethodLayout;
    QHBoxLayout *rBDeviceLayout;
    QRadioButton *rB1Device;
    QRadioButton *rB2Devices;
    QHBoxLayout *spinDeviceLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label1Device;
    QSpinBox *spin1Device;
    QVBoxLayout *verticalLayout_3;
    QLabel *label2Devices;
    QSpinBox *spin2Devices;
    QPushButton *testDevicesButton;
    QFrame *line_2;
    QVBoxLayout *segMethodLayout;
    QLabel *segMethodLabel;
    QComboBox *segMethodSelector;
    QFrame *line_3;
    QVBoxLayout *posAcqMethodLayout;
    QLabel *posAcqMethodLabel;
    QComboBox *posAcqMethodSelector;
    QPlainTextEdit *posAcqMethodEditText;
    QFrame *line_4;
    QVBoxLayout *posReconAlgLayout;
    QLabel *posReconAlgLabel;
    QComboBox *posReconAlgorithmSelector;
    QHBoxLayout *thresholdLayout;
    QLabel *thresholdLabel;
    QPlainTextEdit *thresholdTextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(571, 848);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 61, 528, 788));
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
        titleLabel->setStyleSheet(QLatin1String("font: 45pt \"Palatino Linotype\";\n"
""));
        titleLabel->setTextFormat(Qt::PlainText);

        titleLayout->addWidget(titleLabel);

        authorLabel = new QLabel(layoutWidget);
        authorLabel->setObjectName(QStringLiteral("authorLabel"));
        authorLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        titleLayout->addWidget(authorLabel);

        dateLabel = new QLabel(layoutWidget);
        dateLabel->setObjectName(QStringLiteral("dateLabel"));
        dateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        titleLayout->addWidget(dateLabel);


        mainLayout->addLayout(titleLayout);

        imgAcqMethodLayout = new QVBoxLayout();
        imgAcqMethodLayout->setSpacing(6);
        imgAcqMethodLayout->setObjectName(QStringLiteral("imgAcqMethodLayout"));
        imgAcqMethodLabel = new QLabel(layoutWidget);
        imgAcqMethodLabel->setObjectName(QStringLiteral("imgAcqMethodLabel"));

        imgAcqMethodLayout->addWidget(imgAcqMethodLabel);

        imgAcqMethodSelector = new QComboBox(layoutWidget);
        imgAcqMethodSelector->setObjectName(QStringLiteral("imgAcqMethodSelector"));

        imgAcqMethodLayout->addWidget(imgAcqMethodSelector);

        resolutionLayout = new QHBoxLayout();
        resolutionLayout->setSpacing(6);
        resolutionLayout->setObjectName(QStringLiteral("resolutionLayout"));
        resolutionLayout->setContentsMargins(-1, -1, -1, 0);
        widthLabel = new QLabel(layoutWidget);
        widthLabel->setObjectName(QStringLiteral("widthLabel"));

        resolutionLayout->addWidget(widthLabel);

        widthTextEdit = new QPlainTextEdit(layoutWidget);
        widthTextEdit->setObjectName(QStringLiteral("widthTextEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widthTextEdit->sizePolicy().hasHeightForWidth());
        widthTextEdit->setSizePolicy(sizePolicy);
        widthTextEdit->setMaximumSize(QSize(16777215, 25));

        resolutionLayout->addWidget(widthTextEdit);

        heightLabel = new QLabel(layoutWidget);
        heightLabel->setObjectName(QStringLiteral("heightLabel"));

        resolutionLayout->addWidget(heightLabel);

        heightEditText = new QPlainTextEdit(layoutWidget);
        heightEditText->setObjectName(QStringLiteral("heightEditText"));
        heightEditText->setMaximumSize(QSize(16777215, 25));

        resolutionLayout->addWidget(heightEditText);


        imgAcqMethodLayout->addLayout(resolutionLayout);

        fileMethodLayout = new QHBoxLayout();
        fileMethodLayout->setSpacing(6);
        fileMethodLayout->setObjectName(QStringLiteral("fileMethodLayout"));
        fileMethodLayout->setContentsMargins(-1, -1, -1, 0);
        imgAcqMethodPathEditText = new QPlainTextEdit(layoutWidget);
        imgAcqMethodPathEditText->setObjectName(QStringLiteral("imgAcqMethodPathEditText"));
        imgAcqMethodPathEditText->setEnabled(false);
        imgAcqMethodPathEditText->setMaximumSize(QSize(16777215, 25));

        fileMethodLayout->addWidget(imgAcqMethodPathEditText);

        imgAcqMethodFileNameEditText = new QPlainTextEdit(layoutWidget);
        imgAcqMethodFileNameEditText->setObjectName(QStringLiteral("imgAcqMethodFileNameEditText"));
        imgAcqMethodFileNameEditText->setEnabled(false);
        imgAcqMethodFileNameEditText->setMaximumSize(QSize(150, 25));

        fileMethodLayout->addWidget(imgAcqMethodFileNameEditText);


        imgAcqMethodLayout->addLayout(fileMethodLayout);

        deviceMethodLayout = new QVBoxLayout();
        deviceMethodLayout->setSpacing(6);
        deviceMethodLayout->setObjectName(QStringLiteral("deviceMethodLayout"));
        deviceMethodLayout->setContentsMargins(-1, -1, -1, 0);
        rBDeviceLayout = new QHBoxLayout();
        rBDeviceLayout->setSpacing(6);
        rBDeviceLayout->setObjectName(QStringLiteral("rBDeviceLayout"));
        rBDeviceLayout->setContentsMargins(-1, -1, -1, 0);
        rB1Device = new QRadioButton(layoutWidget);
        rB1Device->setObjectName(QStringLiteral("rB1Device"));
        rB1Device->setChecked(true);

        rBDeviceLayout->addWidget(rB1Device);

        rB2Devices = new QRadioButton(layoutWidget);
        rB2Devices->setObjectName(QStringLiteral("rB2Devices"));

        rBDeviceLayout->addWidget(rB2Devices);


        deviceMethodLayout->addLayout(rBDeviceLayout);

        spinDeviceLayout = new QHBoxLayout();
        spinDeviceLayout->setSpacing(6);
        spinDeviceLayout->setObjectName(QStringLiteral("spinDeviceLayout"));
        spinDeviceLayout->setContentsMargins(-1, 0, -1, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label1Device = new QLabel(layoutWidget);
        label1Device->setObjectName(QStringLiteral("label1Device"));

        verticalLayout->addWidget(label1Device);

        spin1Device = new QSpinBox(layoutWidget);
        spin1Device->setObjectName(QStringLiteral("spin1Device"));

        verticalLayout->addWidget(spin1Device);


        spinDeviceLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label2Devices = new QLabel(layoutWidget);
        label2Devices->setObjectName(QStringLiteral("label2Devices"));

        verticalLayout_3->addWidget(label2Devices);

        spin2Devices = new QSpinBox(layoutWidget);
        spin2Devices->setObjectName(QStringLiteral("spin2Devices"));

        verticalLayout_3->addWidget(spin2Devices);


        spinDeviceLayout->addLayout(verticalLayout_3);


        deviceMethodLayout->addLayout(spinDeviceLayout);

        testDevicesButton = new QPushButton(layoutWidget);
        testDevicesButton->setObjectName(QStringLiteral("testDevicesButton"));

        deviceMethodLayout->addWidget(testDevicesButton);


        imgAcqMethodLayout->addLayout(deviceMethodLayout);


        mainLayout->addLayout(imgAcqMethodLayout);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        mainLayout->addWidget(line_2);

        segMethodLayout = new QVBoxLayout();
        segMethodLayout->setSpacing(6);
        segMethodLayout->setObjectName(QStringLiteral("segMethodLayout"));
        segMethodLabel = new QLabel(layoutWidget);
        segMethodLabel->setObjectName(QStringLiteral("segMethodLabel"));

        segMethodLayout->addWidget(segMethodLabel);

        segMethodSelector = new QComboBox(layoutWidget);
        segMethodSelector->setObjectName(QStringLiteral("segMethodSelector"));

        segMethodLayout->addWidget(segMethodSelector);


        mainLayout->addLayout(segMethodLayout);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        mainLayout->addWidget(line_3);

        posAcqMethodLayout = new QVBoxLayout();
        posAcqMethodLayout->setSpacing(6);
        posAcqMethodLayout->setObjectName(QStringLiteral("posAcqMethodLayout"));
        posAcqMethodLayout->setSizeConstraint(QLayout::SetMinimumSize);
        posAcqMethodLabel = new QLabel(layoutWidget);
        posAcqMethodLabel->setObjectName(QStringLiteral("posAcqMethodLabel"));
        posAcqMethodLabel->setMaximumSize(QSize(16777215, 25));

        posAcqMethodLayout->addWidget(posAcqMethodLabel);

        posAcqMethodSelector = new QComboBox(layoutWidget);
        posAcqMethodSelector->setObjectName(QStringLiteral("posAcqMethodSelector"));
        posAcqMethodSelector->setMaximumSize(QSize(16777215, 25));

        posAcqMethodLayout->addWidget(posAcqMethodSelector);

        posAcqMethodEditText = new QPlainTextEdit(layoutWidget);
        posAcqMethodEditText->setObjectName(QStringLiteral("posAcqMethodEditText"));
        posAcqMethodEditText->setMaximumSize(QSize(16777215, 25));

        posAcqMethodLayout->addWidget(posAcqMethodEditText);


        mainLayout->addLayout(posAcqMethodLayout);

        line_4 = new QFrame(layoutWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        mainLayout->addWidget(line_4);

        posReconAlgLayout = new QVBoxLayout();
        posReconAlgLayout->setSpacing(6);
        posReconAlgLayout->setObjectName(QStringLiteral("posReconAlgLayout"));
        posReconAlgLabel = new QLabel(layoutWidget);
        posReconAlgLabel->setObjectName(QStringLiteral("posReconAlgLabel"));

        posReconAlgLayout->addWidget(posReconAlgLabel);

        posReconAlgorithmSelector = new QComboBox(layoutWidget);
        posReconAlgorithmSelector->setObjectName(QStringLiteral("posReconAlgorithmSelector"));

        posReconAlgLayout->addWidget(posReconAlgorithmSelector);

        thresholdLayout = new QHBoxLayout();
        thresholdLayout->setSpacing(6);
        thresholdLayout->setObjectName(QStringLiteral("thresholdLayout"));
        thresholdLayout->setSizeConstraint(QLayout::SetMinimumSize);
        thresholdLayout->setContentsMargins(-1, -1, -1, 0);
        thresholdLabel = new QLabel(layoutWidget);
        thresholdLabel->setObjectName(QStringLiteral("thresholdLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(thresholdLabel->sizePolicy().hasHeightForWidth());
        thresholdLabel->setSizePolicy(sizePolicy1);
        thresholdLabel->setMaximumSize(QSize(16777215, 25));

        thresholdLayout->addWidget(thresholdLabel);

        thresholdTextEdit = new QPlainTextEdit(layoutWidget);
        thresholdTextEdit->setObjectName(QStringLiteral("thresholdTextEdit"));
        sizePolicy.setHeightForWidth(thresholdTextEdit->sizePolicy().hasHeightForWidth());
        thresholdTextEdit->setSizePolicy(sizePolicy);
        thresholdTextEdit->setMaximumSize(QSize(100, 25));

        thresholdLayout->addWidget(thresholdTextEdit);


        posReconAlgLayout->addLayout(thresholdLayout);


        mainLayout->addLayout(posReconAlgLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 10);
        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setMaximumSize(QSize(2000, 2000));

        horizontalLayout->addWidget(startButton);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        horizontalLayout->addWidget(stopButton);


        mainLayout->addLayout(horizontalLayout);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 571, 21));
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
        titleLabel->setToolTip(QApplication::translate("MainWindowClass", "<html><head/><body><p><span style=\" font-size:36pt;\">Visual Tracking UI</span></p></body></html>", 0));
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
        label1Device->setText(QApplication::translate("MainWindowClass", "Device 1:", 0));
        label2Devices->setText(QApplication::translate("MainWindowClass", "Device 2:", 0));
        testDevicesButton->setText(QApplication::translate("MainWindowClass", "Test Devices", 0));
        segMethodLabel->setText(QApplication::translate("MainWindowClass", "Segmentation Method:", 0));
        segMethodSelector->clear();
        segMethodSelector->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "Color Cluster Segmentation", 0)
        );
        posAcqMethodLabel->setText(QApplication::translate("MainWindowClass", "Position Acquisition Method:", 0));
        posAcqMethodSelector->clear();
        posAcqMethodSelector->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "File", 0)
         << QApplication::translate("MainWindowClass", "Vicon", 0)
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
