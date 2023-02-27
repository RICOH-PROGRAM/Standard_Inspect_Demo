#include "foundation.h"
#include "algosettingdlg.h"
#include <iostream>
#include <QSettings>
#include <QCoreapplication>
#include "implfoundation.h"
#include "logger.h"
namespace smartmore
{
	Alg_Foundation::Impl::Impl()
	{
		tid = std::this_thread::get_id();
		t = *(_Thrd_t*)(char*)&tid;
		unsigned int nId = t._Id;
		itoa(nId, buf, 10);
	}

	Alg_Foundation::Impl::~Impl()
	{
		saveAlgoParam();
	}
	bool Alg_Foundation::Impl::initAlgoparam(std::string& camserial)
	{
		QSettings algsetting(qApp->applicationDirPath() + "/defaultModel/" + camserial.c_str() + ".ini", QSettings::IniFormat);




		LOGW("initAlgoparam successfully");
		return true;
	}

	bool Alg_Foundation::Impl::popCameraDlg(void* parent, void* layout)
	{

		LOGW("popCameraDlg successfully");
		return false;
	}

	bool Alg_Foundation::Impl::saveAlgoParam()
	{
		return false;
	}

	int Alg_Foundation::Impl::doing(smartmore::SingleMat& data)
	{
		lastimg = data.imgori.clone();
		cv::Mat gray;
		cv::cvtColor(lastimg, gray, cv::COLOR_BGR2GRAY);
		cv::threshold(gray, gray, 50, 255, cv::THRESH_BINARY);
		cv::Mat RED = cv::Mat(gray.size(), CV_8UC3, cv::Scalar(255, 0, 0));
		RED.copyTo(data.imgrst, gray);
		//cv::putText(data.imgrst, buf, cv::Point(100, 100), 2, 1.0, cv::Scalar(0, 255, 255));
		return -1;
	}

};
