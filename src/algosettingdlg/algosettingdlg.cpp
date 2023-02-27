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


using namespace std;
using namespace std::placeholders;

Qtalgosettingdlg::Qtalgosettingdlg(QWidget* parent, void* coreservice)
	: QDialog(parent), ui(new Ui::algosettingdlg)
{
	setWindowFlags(Qt::FramelessWindowHint); 
	ui->setupUi(this);

};

Qtalgosettingdlg::~Qtalgosettingdlg()
{
}
