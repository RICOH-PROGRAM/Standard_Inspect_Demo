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
#include "common.h"
#include "yaml-cpp/yaml.h"

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
	void SetLastParam(YAML::Node);
	void SetTestCallback(wikky_algo::TestCallback func);
protected:
	bool eventFilter(QObject* watched, QEvent* e);
private:
	Ui::algosettingdlg* ui;
	cv::Mat _lastimg;
	QPixmap _Qmap;
	YAML::Node m_node;
	wikky_algo::CheckParam m_checkparam;
	wikky_algo::TestCallback _testcallback = nullptr;
};
