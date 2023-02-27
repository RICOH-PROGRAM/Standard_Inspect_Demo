#pragma once

#include <intsafe.h>

#include <QDir>
#include <QHeaderView>
#include <QComboBox>
#include <QEventLoop>
#include <QDialog>
#include <intsafe.h>
#include <QMetaType>

namespace Ui
{
    class algosettingdlg;
}


class Qtalgosettingdlg : public QDialog
{
    Q_OBJECT

   public:
    Qtalgosettingdlg(QWidget* parent = Q_NULLPTR,void* coreservice = nullptr);
    ~Qtalgosettingdlg();
private:
    Ui::algosettingdlg* ui;
};
