#include "algosettingdlg.h"
#include "ui_algosettingdlg.h"
#include "logger.h"
#include <QCheckBox>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <functional>
#include <future>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <fstream>


using namespace std;
using namespace std::placeholders;

bool Node2Param(wikky_algo::CheckParam& checkparam, YAML::Node& _param)
{
	checkparam._iThread = getValue<int>(_param, QString("Param_AxisMask"), QString("X"), "5");
	return true;
}

bool Param2Node(wikky_algo::CheckParam& checkparam, YAML::Node& _param)
{
	_param[QString("Param_AxisMask").toStdString().c_str()][QString("X").toStdString().c_str()]["value"] = checkparam._iThread;
	_param[QString("Param_AxisMask").toStdString().c_str()][QString("Y").toStdString().c_str()]["value"] = checkparam._iThread;
	return true;
}

Qtalgosettingdlg::Qtalgosettingdlg(QWidget* parent)
	: QDialog(parent), ui(new Ui::algosettingdlg)
{
	ui->setupUi(this);
	this->installEventFilter(this);
	ui->gV_ShowImg->installEventFilter(this);
};

Qtalgosettingdlg::~Qtalgosettingdlg()
{
}

void Qtalgosettingdlg::SetLastParam(YAML::Node _param)
{
	//m_checkparam = _param;
	ui->treewidget->LoadYAMLFile(_param);
}

void Qtalgosettingdlg::SetTestCallback(wikky_algo::TestCallback func)
{
	_testcallback = func;
}

void Qtalgosettingdlg::SetLastImage(cv::Mat img)
{
	_lastimg = img.clone();
	_Qmap = QPixmap::fromImage(QImage((const uchar*)(_lastimg.data), _lastimg.cols, _lastimg.rows, _lastimg.cols * _lastimg.channels(), _lastimg.channels() == 3 ? QImage::Format_RGB888 : QImage::Format_Indexed8));
	ui->gV_ShowImg->SetImage(_Qmap.toImage());
}

bool Qtalgosettingdlg::eventFilter(QObject* watched, QEvent* e)
{
	if (QEvent::Show == e->type()||(QEvent::MouseButtonDblClick == e->type()))
	{
		ui->gV_ShowImg->SetImage(_Qmap.toImage());
	}
	if (QEvent::MouseButtonPress == e->type()&&Qt::RightButton == ((QMouseEvent*)e)->button())
	{
		if (_testcallback)
		{
			wikky_algo::SingleMat singlemat;
			singlemat.imgori = _lastimg.clone();
			_testcallback(singlemat, &m_checkparam);
			ui->gV_ShowImg->SetImage(QImage((const uchar*)(singlemat.imgrst.data), singlemat.imgrst.cols, singlemat.imgrst.rows, singlemat.imgrst.cols * singlemat.imgrst.channels(), singlemat.imgrst.channels() == 3 ? QImage::Format_RGB888 : QImage::Format_Indexed8));
		}
	}
	return QDialog::eventFilter(watched, e);
}