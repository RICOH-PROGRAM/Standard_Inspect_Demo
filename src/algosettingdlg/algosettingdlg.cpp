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


using namespace std;
using namespace std::placeholders;

Qtalgosettingdlg::Qtalgosettingdlg(QWidget* parent)
	: QDialog(parent), ui(new Ui::algosettingdlg)
{
	ui->setupUi(this);
	this->installEventFilter(this);
};

Qtalgosettingdlg::~Qtalgosettingdlg()
{
}

void Qtalgosettingdlg::SetLastImage(cv::Mat img)
{
	_lastimg = img.clone();
	_Qmap = QPixmap::fromImage(QImage((const uchar*)(img.data), img.cols, img.rows, img.cols * img.channels(), img.channels() == 3 ? QImage::Format_RGB888 : QImage::Format_Indexed8));
}

bool Qtalgosettingdlg::eventFilter(QObject* watched, QEvent* e)
{
	if (QEvent::Show == e->type())
	{
		QGraphicsScene* scene = new QGraphicsScene;
		scene->addPixmap(_Qmap);
		ui->gV_ShowImg->setScene(scene);
	}
	return QDialog::eventFilter(watched, e);
}