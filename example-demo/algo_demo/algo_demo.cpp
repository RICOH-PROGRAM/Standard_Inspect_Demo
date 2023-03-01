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
#include "logger.h"

using namespace std;
using namespace std::placeholders;


Qtalgo_demo::Qtalgo_demo(QWidget* parent) : QMainWindow(parent)
{ 
	ui.setupUi(this);
	QueryPerformanceFrequency(&nFreq);
	AppPath = qApp->applicationDirPath();//exe所在目录
	configIniRead = new QSettings(AppPath + "/OffLineLog.ini", QSettings::IniFormat);
	configIniRead->setIniCodec("utf-8");
	QString st = configIniRead->value("ProgramSet/LastPath").toString();
	m_sImageListPath = st;
	initImageLS(m_sImageListPath);

	onUpdateAlgo();
	connectsignal();
};

void resizeByNN(uchar* input, uchar* output, int height_in, int width_in, int channels, int height_out, int width_out) {
	uchar* data_source = input;
	uchar* data_half = output;

	int bpl_source = width_in * 3;
	int bpl_dst = width_out * 3;

	int pos = 0;
	int sep = 0;
	uchar* sr = nullptr;
	uchar* hr = nullptr;
	float step = 0.0;
	float step_x = float(width_in) / float(width_out);
	float step_y = float(height_in) / float(height_out);

	for (int i = 0; i < height_out; i++) {
		for (int j = 0; j < width_out; j++) {
			sep = int(step_y * i);
			step = int(j * step_x);
			sr = data_source + sep * bpl_source;
			hr = data_half + i * bpl_dst + j * channels;
			pos = step * channels;
			memcpy(hr, sr + pos, channels);
		}
	}
	return;
}


void Qtalgo_demo::resizeEvent(QResizeEvent* event)
{
	//QSize sz = ui.label_Show->size();
	//m_tempshow = cv::Mat(sz.height() - ui.label_Show->frameWidth() * 3, sz.width() - ui.label_Show->frameWidth() * 2, CV_8UC3);
	//LOGI("resizeEvent   width:{}, height:{}", sz.width(), sz.height());
}
void Qtalgo_demo::showEvent(QShowEvent* event)
{
	//QSize sz = ui.label_Show->size();
	//m_tempshow = cv::Mat(sz.height() - ui.label_Show->frameWidth() * 3, sz.width() - ui.label_Show->frameWidth() * 2, CV_8UC3);

	//LOGI("showEvent   width:{}, height:{}", sz.width(), sz.height());
}
void Qtalgo_demo::ShowMatToLabel(cv::Mat img)
{
	char* d;

	//resizeByNN(img.data, m_tempshow.data, img.rows, img.cols, img.channels(), m_tempshow.rows, m_tempshow.cols);
	//LOGI("image size   width:{}, height:{}", m_tempshow.cols, m_tempshow.rows);
	//cv::cvtColor(m_tempshow, m_tempRGB, cv::COLOR_RGB2BGR);
	m_tempRGB = img.clone();
	QSize sz = ui.label_Show->size();
	sz.setHeight(sz.height() - ui.label_Show->frameWidth() * 2);
	sz.setWidth(sz.width() - ui.label_Show->frameWidth() * 2);
	disImage = QImage((const unsigned char*)(m_tempRGB.data), m_tempRGB.cols, m_tempRGB.rows, m_tempRGB.step, QImage::Format_RGB888);
	ui.label_Show->setPixmap(QPixmap::fromImage(disImage).scaled(sz,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	ui.label_Show->show();
	QThread::msleep(1);
}

Qtalgo_demo::~Qtalgo_demo()
{
	configIniRead->setValue("ProgramSet/LastPath", m_sImageListPath);
	configIniRead->sync();

	if (_CheckClass)
	{
		DeleteCamera(_CheckClass);
		_CheckClass = nullptr;
	}
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

void Qtalgo_demo::onInitAlgo()
{
	if (_CheckClass)
	{
		DeleteCamera(_CheckClass);
		_CheckClass = nullptr;
	}
	QLibrary* LocalFileDLL = new QLibrary(qApp->applicationDirPath() + "/"+ui.comboBox->currentText());
	CreateLocalCamera =
		(wikky_algo::pExportALG)(LocalFileDLL->resolve("CreateExportAlgObj"));
	DeleteCamera =
		(wikky_algo::pDeleteALG)(LocalFileDLL->resolve("DeleteExportAlgObj"));
	_CheckClass = CreateLocalCamera();
	_CheckClass->initAlgoparam(QString("local_camera").toStdString());
}

void Qtalgo_demo::onUpdateAlgo()
{
	QDir dir(AppPath);
	if (!dir.exists())
	{
		return;
	}
	dir.setFilter(QDir::Files);
	QFileInfoList list = dir.entryInfoList();

	int file_count = list.count();
	if (file_count <= 0)
	{
		return;
	}

	QStringList string_list;
	for (int i = 0; i < file_count; i++)
	{
		QFileInfo file_info = list.at(i);
		QString suffix = file_info.fileName();
		if (suffix.contains("Algo.dll"))
		{
			QString file_name = file_info.fileName();
			string_list.append(file_name);
		}
	}
	ui.comboBox->addItems(string_list);
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

void Qtalgo_demo::connectsignal()
{
	QObject::connect(ui.lw_ImageList, &QListWidget::currentItemChanged, this, &Qtalgo_demo::onSelectImageList);
	QObject::connect(ui.lw_ImageList, &QListWidget::itemDoubleClicked, [=](QListWidgetItem* item)
		{
			QString sSelectItem = item->text();
			if (sSelectItem == ".")
			{
				m_sImageListPath = "";
				initImageLS(sSelectItem);
				return;
			}
			if (sSelectItem == "..")
			{
				if (m_sImageListPath.length() == 3)
				{
					m_sImageListPath = "";
					initImageLS(".");
					return;
				}
				QString newPath = m_sImageListPath.left(m_sImageListPath.lastIndexOf("/"));
				if (m_sImageListPath.split("/").size() < 2)
				{
					// only allow user to access the data in dataPath
					m_sImageListPath = ".";
				}
				else//exe所在的根目录
					if (newPath.length() >= 2)
					{
						// only allow user to access the data in dataPath
						m_sImageListPath = newPath;
					}

				if (newPath.length() == 2)
				{
					// only allow user to access the data in dataPath
					m_sImageListPath += "/";
				}
				initImageLS(m_sImageListPath);
				ui.lineEdit->setText(m_sImageListPath);
				return;
			}

			QString pathselect;
			int x = m_sImageListPath.lastIndexOf('/');
			if (m_sImageListPath == ".")
			{
				pathselect = sSelectItem;
			}
			else
			{
				if (m_sImageListPath.lastIndexOf('/') == m_sImageListPath.length() - 1)
				{
					pathselect = m_sImageListPath + sSelectItem;
				}
				else
				{
					pathselect = m_sImageListPath + "/" + sSelectItem;
				}
			}
			QFileInfo file(pathselect);
			if (!file.isFile())
			{
				m_sImageListPath = pathselect;
				initImageLS(m_sImageListPath + "/");
			}
			else
			{
				ui.lineEdit->setText(pathselect);
			}
			if (configIniRead)
			{
				configIniRead->setValue("ProgramSet/LastPath", m_sImageListPath);
			}
		});
	QObject::connect(ui.pB_initAlgo, &QPushButton::released, [=]()
		{
			onInitAlgo();
			ui.lw_ImageList->setEnabled(true);
		});
	QObject::connect(ui.pB_SetDlg, &QPushButton::released, [=]()
		{
			if (_CheckClass)
				_CheckClass->popCameraDlg(nullptr);

		});

}
cv::Mat Qtalgo_demo::ReadImage(QString file)
{
	cv::Mat img;
	cvtColor(cv::imread(file.toLocal8Bit().toStdString().c_str()), img, cv::COLOR_BGR2RGB);
	return img;
}

void Qtalgo_demo::onSelectImageList(QListWidgetItem* item, QListWidgetItem* it)
{
	QString sSelectItem = item->text();

	QString pathselect;
	int x = m_sImageListPath.lastIndexOf('/');
	if (m_sImageListPath.lastIndexOf('/') == m_sImageListPath.length() - 1)
	{
		pathselect = m_sImageListPath + sSelectItem;
	}
	else
	{
		pathselect = m_sImageListPath + "/" + sSelectItem;
	}
	QFileInfo file(pathselect);
	if (file.isFile())
	{
		ui.lineEdit->setText(QString::fromLocal8Bit(pathselect.toLocal8Bit()));
		ImgRead = ReadImage(pathselect);
		if (m_w != ImgRead.cols || m_h != ImgRead.cols|| !_CheckClass)
		{
			m_w = ImgRead.cols;
			m_h = ImgRead.rows;
			m_c = 3;
		}
		wikky_algo::SingleMat singleMat;
		singleMat.imgori = ImgRead.clone();
		LARGE_INTEGER t1, t2;
		QueryPerformanceCounter(&t1);

		if(_CheckClass)
			_CheckClass->doing(singleMat);
		QueryPerformanceCounter(&t2);
		float s = (t2.QuadPart - t1.QuadPart) / (float)nFreq.QuadPart * 1000;
		fInterval += s;
		m_ichecktimes++;
		ui.lineEdit->setText(QString::number(s));

		ShowMatToLabel(singleMat.imgrst);

		//emit CHECKRESULT(QStringList(QString::fromLocal8Bit(strResult.error_type)));
		//if ((strResult._bResultNGOK && m_bOKSTOP)
		//	|| (!strResult._bResultNGOK && m_bNGSTOP))
		//{
		//	ui.Button_Start->setChecked(false);
		//	ui.lineEdit->setText(QString::number(fInterval / m_ichecktimes));
		//	return;
		//}
		//if (m_bContinueCheck)
		//{
		//	ti->start(10);
		//}
	}
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
