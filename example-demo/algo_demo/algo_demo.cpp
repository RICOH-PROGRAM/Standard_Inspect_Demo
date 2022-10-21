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

	AppPath = qApp->applicationDirPath();//exe����Ŀ¼
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
		// ��������
		for (wchar_t d = 'A'; d <= 'Z'; d++)
		{
			TCHAR szTemp[3] = { d, ':', '\0' };
			// ��ȡ��������
			UINT uType = GetDriveType(szTemp);
			// DRIVE_UNKNOWN  �޷�ȷ�����������͡�
			// DRIVE_NO_ROOT_DIR ��·����Ч; ���磬ָ��·����û�а�װ��
			// DRIVE_REMOVABLE �������п��ƶ�����; ���磬������������Ĵָ�����������濨��������
			// DRIVE_FIXED �������й̶���ý��; ���磬Ӳ����������������������
			// DRIVE_REMOTE ����������Զ�̣����磩��������
			// DRIVE_CDROM ����������һ��CD-ROM��������
			// DRIVE_RAMDISK ��������RAM���̡�
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
