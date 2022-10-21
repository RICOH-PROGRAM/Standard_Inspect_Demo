#include "algo_demo.h"
#include "windows.h"
#pragma comment(lib, "version")

//#include "logger.h"
#include <QCheckBox>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QSettings>
#include <functional>
#include <future>
#include <QLibrary>

using namespace std;
using namespace std::placeholders;


Qtalgo_demo::Qtalgo_demo(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	AppPath = qApp->applicationDirPath();//exe所在目录
	configIniRead = new QSettings(AppPath + "/OffLineLog.ini", QSettings::IniFormat);
	configIniRead->setIniCodec("utf-8");
	QString st = configIniRead->value("ProgramSet/LastPath").toString();
	m_sImageListPath = st;
	initImageLS(m_sImageListPath);

	QLibrary* LocalFileDLL = new QLibrary(qApp->applicationDirPath() + "/Alg_foundation.dll");
    CreateLocalCamera =
        (basealgo::pExportALG)(LocalFileDLL->resolve("CreateExportAlgObj"));
    DeleteCamera =
        (basealgo::pDeleteALG)(LocalFileDLL->resolve("DeleteExportAlgObj"));
};

Qtalgo_demo::~Qtalgo_demo()
{
}

bool Qtalgo_demo::isImage(QFileInfo& info)
{
	QString filename = info.fileName();
	if (filename == "." || filename == "..")
		return false;

	if (filename.contains("def") || filename.contains(".csv"))
		return false;

	return filename.contains(".bmp") || filename.contains(".BMP") ||
		filename.contains(".jpg") || filename.contains(".JPG") ||
		filename.contains(".jpeg") || filename.contains(".JPEG") ||
		filename.contains(".png") || filename.contains(".PNG") ||
		filename.contains(".tif") || filename.contains(".TIF");
}

bool Qtalgo_demo::containImages(QDir& dir)
{
	foreach(QFileInfo entry, dir.entryInfoList(QDir::Dirs | QDir::Files)) {
		QString filename = entry.fileName();
		if (filename == "." || filename == "..")
			continue;

		if (entry.isDir() && containImages(QDir(entry.absoluteFilePath())))
			return true;

		if (entry.isFile() && isImage(entry))
			return true;
	}
	return false;
}

void Qtalgo_demo::initImageLS(QString str)
{
	ui.lw_ImageList->blockSignals(true);
	ui.lw_ImageList->clear();
	if (str == ".")
	{
		BOOL fResult;
		// 遍历磁盘
		for (wchar_t d = 'A'; d <= 'Z'; d++)
		{
			TCHAR szTemp[3] = { d, ':', '\0' };
			// 获取磁盘类型
			UINT uType = GetDriveType(szTemp);
			// DRIVE_UNKNOWN  无法确定驱动器类型。
			// DRIVE_NO_ROOT_DIR 根路径无效; 例如，指定路径上没有安装卷。
			// DRIVE_REMOVABLE 驱动器有可移动介质; 例如，软盘驱动器，拇指驱动器或闪存卡读卡器。
			// DRIVE_FIXED 驱动器有固定的媒体; 例如，硬盘驱动器或闪存驱动器。
			// DRIVE_REMOTE 该驱动器是远程（网络）驱动器。
			// DRIVE_CDROM 该驱动器是一个CD-ROM驱动器。
			// DRIVE_RAMDISK 驱动器是RAM磁盘。
			switch (uType)
			{
			case DRIVE_FIXED:
			{
				ui.lw_ImageList->addItem(QString(d) + ":");
			}
			default:
			{
				continue;
			}
			}
		}
		ui.lw_ImageList->blockSignals(false);
		return;
	}
	QDir dir(str);
	ui.lw_ImageList->addItem(".");
	ui.lw_ImageList->addItem("..");
	ui.lw_ImageList->setSortingEnabled(true);
	foreach(QFileInfo mfi, dir.entryInfoList(QDir::Dirs | QDir::Files, QDir::Time))
	{
		if (mfi.fileName() == "." || mfi.fileName() == "..")
			continue;

		if (mfi.isDir()) {
			if (containImages(QDir(mfi.absoluteFilePath())))
				ui.lw_ImageList->addItem(mfi.fileName());
			continue;
		}

		if (mfi.isFile() && isImage(mfi))
			ui.lw_ImageList->addItem(mfi.fileName());
	}
	ui.lw_ImageList->blockSignals(false);
}
