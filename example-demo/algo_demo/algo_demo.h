#pragma once

#include <intsafe.h>

#include <QDir>
#include <QHeaderView>
#include <QSettings>
#include "ui_algo_demo.h"
#include <intsafe.h>
#include "opencv2/opencv.hpp"
#include <QMetaType>
#include "windows.h"
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
    LARGE_INTEGER nFreq;
    cv::Mat ImgRead, m_matCheck, m_tempshow, m_tempRGB;
    QImage disImage;
    int m_w, m_h, m_c;
    float fInterval;
    int m_ichecktimes;
    bool m_bContinueCheck = false;
    bool m_bNGSTOP = false;
    bool m_bOKSTOP = false;
   public:
    Qtalgo_demo(QWidget* parent = Q_NULLPTR);
    void connectsignal();
    cv::Mat ReadImage(QString);
    basealgo::IBaseAlg* _CheckClass = nullptr;
    void ShowMatToLabel(cv::Mat);
    void resizeEvent(QResizeEvent*);
    void showEvent(QShowEvent*);
    ~Qtalgo_demo();
   private:
    Ui::algo_demo ui;
    void initImageLS(QString str);
    bool containImages(QDir&);
    bool isImage(QFileInfo& info);
public slots:
    void onSelectImageList(QListWidgetItem* item, QListWidgetItem* it);
    void onInitAlgo();
    void onUpdateAlgo();
};
