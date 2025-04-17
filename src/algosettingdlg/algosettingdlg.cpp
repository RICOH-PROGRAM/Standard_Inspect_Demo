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
	checkparam._iThreadX = getValue<int>(_param, QString("Param_AxisMask"), QString("X"), 5);
	checkparam._iThreadY = getValue<int>(_param, QString("Param_AxisMask"), QString("Y"), 10);
	checkparam._iThreadZ = getValue<int>(_param, QString("Param_AxisMask"), QString("Z"), 101);
	return true;
}

bool Param2Node(wikky_algo::CheckParam& checkparam, YAML::Node& _param)
{
	_param[QString("Param_AxisMask").toStdString().c_str()][QString("X").toStdString().c_str()]["value"] = checkparam._iThreadX;
	_param[QString("Param_AxisMask").toStdString().c_str()][QString("Y").toStdString().c_str()]["value"] = checkparam._iThreadY;
	_param[QString("Param_AxisMask").toStdString().c_str()][QString("Z").toStdString().c_str()]["value"] = checkparam._iThreadZ;
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
			wikky_algo::SingleMat singlemat;
			int _depth;
			switch (_lastimg.depth())
			{
                case CV_8U:
					_depth = sizeof(uchar);
					break;
				case CV_64F:
					_depth = sizeof(double);
					break;
				default:
					break;
			}
			memcpy(singlemat.imgori, (void*)_lastimg.data, _lastimg.cols * _lastimg.rows * _depth * _lastimg.channels());
			_testcallback(singlemat, &_tempparam);
			ui->gV_ShowImg->SetImage(singlemat.imgrst,false);
			m_bChanged = true;
			//ui.pB_Save->setEnabled(true);
		});
};

Qtalgosettingdlg::~Qtalgosettingdlg()
{
}

void Qtalgosettingdlg::SetLastParam(YAML::Node _param)
{
	ui->treewidget->LoadYAMLFile(_param);
}

void Qtalgosettingdlg::SetTestCallback(wikky_algo::TestCallback func)
{
	_testcallback = func;
}

void Qtalgosettingdlg::UpdatetoalgoImpl(wikky_algo::UpdateParam func)
{
	_testupdateparam = func;
}

void Qtalgosettingdlg::SetLastImage(cv::Mat img)
{
	_lastimg = img.clone();
	//_Qmap = QPixmap::fromImage(QImage((const uchar*)(_lastimg.data), _lastimg.cols, _lastimg.rows, _lastimg.cols * _lastimg.channels(), _lastimg.channels() == 3 ? QImage::Format_RGB888 : QImage::Format_Indexed8));
	//ui->gV_ShowImg->SetImage(_Qmap.toImage());
}

bool Qtalgosettingdlg::eventFilter(QObject* watched, QEvent* e)
{
	if (QEvent::Show == e->type()&& watched==this)
	{
		ui->gV_ShowImg->SetImage(_lastimg,true);
		return false;
	}
	if(QEvent::MouseButtonDblClick == e->type())
	{
		ui->gV_ShowImg->SetImage(_lastimg);
		return false;
	}
	if (QEvent::MouseButtonPress == e->type()&&Qt::RightButton == ((QMouseEvent*)e)->button())
	{
		if (_testcallback)
		{
			wikky_algo::SingleMat singlemat;
			int _depth;
			switch (_lastimg.depth())
			{
			case CV_8U:
				_depth = sizeof(uchar);
				break;
			case CV_64F:
				_depth = sizeof(double);
				break;
			default:
				break;
			}
			memcpy(singlemat.imgori, (void*)_lastimg.data, _lastimg.cols * _lastimg.rows * _depth * _lastimg.channels());
			Node2Param(_tempparam, ui->treewidget->_mparam);
			_testcallback(singlemat, &_tempparam);
			ui->gV_ShowImg->SetImage(singlemat.imgrst, false);
		}
		return false;
	}
	if (QEvent::Close == e->type())
	{
		if (m_bChanged && _testupdateparam)
		{
			if(QMessageBox::Yes == QMessageBox::warning(nullptr, "Param change warning", "Should save the param?", QMessageBox::Yes, QMessageBox::No))
				_testupdateparam(_tempparam);
		}
		return false;

	}
	return QDialog::eventFilter(watched, e);
}