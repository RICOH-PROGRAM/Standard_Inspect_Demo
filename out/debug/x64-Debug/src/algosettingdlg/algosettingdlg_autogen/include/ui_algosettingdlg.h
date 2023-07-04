/********************************************************************************
** Form generated from reading UI file 'algosettingdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGOSETTINGDLG_H
#define UI_ALGOSETTINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include "mygraphicsview.h"
#include "qmytreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_algosettingdlg
{
public:
    QHBoxLayout *horizontalLayout;
    QMyTreeWidget *treewidget;
    MyGraphicsView *gV_ShowImg;

    void setupUi(QDialog *algosettingdlg)
    {
        if (algosettingdlg->objectName().isEmpty())
            algosettingdlg->setObjectName(QString::fromUtf8("algosettingdlg"));
        algosettingdlg->setWindowModality(Qt::WindowModal);
        algosettingdlg->setEnabled(true);
        algosettingdlg->resize(1586, 903);
        horizontalLayout = new QHBoxLayout(algosettingdlg);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treewidget = new QMyTreeWidget(algosettingdlg);
        treewidget->setObjectName(QString::fromUtf8("treewidget"));

        horizontalLayout->addWidget(treewidget);

        gV_ShowImg = new MyGraphicsView(algosettingdlg);
        gV_ShowImg->setObjectName(QString::fromUtf8("gV_ShowImg"));

        horizontalLayout->addWidget(gV_ShowImg);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        retranslateUi(algosettingdlg);

        QMetaObject::connectSlotsByName(algosettingdlg);
    } // setupUi

    void retranslateUi(QDialog *algosettingdlg)
    {
        (void)algosettingdlg;
    } // retranslateUi

};

namespace Ui {
    class algosettingdlg: public Ui_algosettingdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGOSETTINGDLG_H
