#pragma once

#include <intsafe.h>

#include <QDir>
#include <QHeaderView>
#include "ui_algo_demo.h"
#include <intsafe.h>
#include "opencv2/opencv.hpp"
#include <QMetaType>


class Qtalgo_demo : public QMainWindow
{
    Q_OBJECT

   public:
    Qtalgo_demo(QWidget* parent = Q_NULLPTR);
    ~Qtalgo_demo();
   private:
    Ui::algo_demo ui;
};
