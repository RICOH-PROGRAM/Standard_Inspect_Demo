#pragma once

#include <intsafe.h>

#include <QDir>
#include <QHeaderView>
#include <QSettings>
#include "ui_algo_demo.h"
#include <intsafe.h>
#include "opencv2/opencv.hpp"
#include <QMetaType>
#include "ibasealgorithm.h"


class Qtalgo_demo : public QMainWindow
{
    Q_OBJECT

private:
    basealgo::pExportALG CreateLocalCamera;
    basealgo::pDeleteALG DeleteCamera;
    QString AppPath;
    QString m_sImageListPath;
    QSettings* configIniRead = nullptr;
   public:
    Qtalgo_demo(QWidget* parent = Q_NULLPTR);
    ~Qtalgo_demo();
   private:
    Ui::algo_demo ui;
    void initImageLS(QString str);
    bool containImages(QDir&);
    bool isImage(QFileInfo& info);
};
