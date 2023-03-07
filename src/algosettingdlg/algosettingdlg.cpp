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
	checkparam._iThreadX = getValue<int>(_param, QString("Param_AxisMask"), QString("X"), "5");
	checkparam._iThreadY = getValue<int>(_param, QString("Param_AxisMask"), QString("Y"), "10");
	checkparam._iThreadZ = getValue<int>(_param, QString("Param_AxisMask"), QString("Z"), "101");
	return true;
}

bool Param2Node(wikky_algo::CheckParam& checkparam, YAML::Node& _param)
{
	_param[QString("Param_AxisMask").toStdString().c_str()][QString("X").toStdString().c_str()]["value"] = checkparam._iThreadX;
	_param[QString("Param_AxisMask").toStdString().c_str()][QString("Y").toStdString().c_str()]["value"] = checkparam._iThreadY;
	_param[QString("Param_AxisMask").toStdString().c_str()][QString("Y").toStdString().c_str()]["value"] = checkparam._iThreadZ;
	return true;
}

Qtalgosettingdlg::Qtalgosettingdlg(QWidget* parent)
	: QDialog(parent), ui(new Ui::algosettingdlg)
{
	ui->setupUi(this);
	this->installEventFilter(this);
	ui->gV_ShowImg->installEventFilter(this);
	connect(ui->treewidget, &QMyTreeWidget::TempSave, [=](QString objname, QString ves)
		{
			Node2Param(_tempparam, ui->treewidget->_mparam);

			//m_bChanged = true;
			//ui.pB_Save->setEnabled(true);
		});
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