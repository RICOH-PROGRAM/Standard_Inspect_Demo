/********************************************************************************
** Form generated from reading UI file 'algo_demo.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGO_DEMO_H
#define UI_ALGO_DEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_algo_demo
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Show;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pB_initAlgo;
    QListWidget *lw_ImageList;
    QLineEdit *lineEdit;
    QGridLayout *gridLayout;
    QPushButton *pB_Start;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QPushButton *pB_SetDlg;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *algo_demo)
    {
        if (algo_demo->objectName().isEmpty())
            algo_demo->setObjectName(QString::fromUtf8("algo_demo"));
        algo_demo->resize(908, 648);
        algo_demo->setAnimated(false);
        centralWidget = new QWidget(algo_demo);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_Show = new QLabel(centralWidget);
        label_Show->setObjectName(QString::fromUtf8("label_Show"));
        label_Show->setFrameShape(QFrame::Box);
        label_Show->setLineWidth(2);

        horizontalLayout->addWidget(label_Show);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        pB_initAlgo = new QPushButton(centralWidget);
        pB_initAlgo->setObjectName(QString::fromUtf8("pB_initAlgo"));

        verticalLayout->addWidget(pB_initAlgo);

        lw_ImageList = new QListWidget(centralWidget);
        lw_ImageList->setObjectName(QString::fromUtf8("lw_ImageList"));
        lw_ImageList->setEnabled(false);

        verticalLayout->addWidget(lw_ImageList);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pB_Start = new QPushButton(centralWidget);
        pB_Start->setObjectName(QString::fromUtf8("pB_Start"));

        gridLayout->addWidget(pB_Start, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout_3->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout_3->addWidget(checkBox_2, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 1, 2, 1);

        pB_SetDlg = new QPushButton(centralWidget);
        pB_SetDlg->setObjectName(QString::fromUtf8("pB_SetDlg"));

        gridLayout->addWidget(pB_SetDlg, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);
        algo_demo->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(algo_demo);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 908, 22));
        algo_demo->setMenuBar(menuBar);
        mainToolBar = new QToolBar(algo_demo);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        algo_demo->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(algo_demo);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        algo_demo->setStatusBar(statusBar);

        retranslateUi(algo_demo);

        QMetaObject::connectSlotsByName(algo_demo);
    } // setupUi

    void retranslateUi(QMainWindow *algo_demo)
    {
        algo_demo->setWindowTitle(QCoreApplication::translate("algo_demo", "QtCameraTest", nullptr));
        label_Show->setText(QCoreApplication::translate("algo_demo", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("algo_demo", "Alg_Dll:", nullptr));
        pB_initAlgo->setText(QCoreApplication::translate("algo_demo", "Init_Algo", nullptr));
        pB_Start->setText(QCoreApplication::translate("algo_demo", "Start", nullptr));
        groupBox->setTitle(QCoreApplication::translate("algo_demo", "\345\201\234\346\255\242\346\235\241\344\273\266", nullptr));
        checkBox->setText(QCoreApplication::translate("algo_demo", "OK", nullptr));
        checkBox_2->setText(QCoreApplication::translate("algo_demo", "NG", nullptr));
        pB_SetDlg->setText(QCoreApplication::translate("algo_demo", "SetDlg", nullptr));
    } // retranslateUi

};

namespace Ui {
    class algo_demo: public Ui_algo_demo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGO_DEMO_H
