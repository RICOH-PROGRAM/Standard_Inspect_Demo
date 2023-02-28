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


using namespace std;
using namespace std::placeholders;

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

void Qtalgosettingdlg::SetLastParam(wikky_algo::CheckParam _param)
{
	m_checkparam = _param;
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