#pragma once

#include <intsafe.h>

#include <QDir>
#include <QHeaderView>
#include <QComboBox>
#include <QEventLoop>
#include <QDialog>
#include <intsafe.h>
#include <QMetaType>
#include "opencv2/core.hpp"

namespace Ui
{
	class algosettingdlg;
}


class Qtalgosettingdlg : public QDialog
{
	Q_OBJECT

public:
	Qtalgosettingdlg(QWidget* parent = Q_NULLPTR);
	~Qtalgosettingdlg();

	void SetLastImage(cv::Mat img);
protected:
	bool eventFilter(QObject* watched, QEvent* e);
private:
	Ui::algosettingdlg* ui;
	cv::Mat _lastimg;
	QPixmap _Qmap;
};
