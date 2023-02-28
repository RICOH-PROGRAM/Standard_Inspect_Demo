#include "foundation.h"
#include <iostream>
#include <QSettings>
#include <QCoreapplication>
#include "implfoundation.h"
#include "logger.h"
#include <functional>
#include <future>
namespace wikky_algo
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
	bool Alg_Foundation::Impl::initAlgoparam(std::string& _camserial)
	{
		m_scamserial = _camserial;
		readAlgoParam();
		return true;
	}

	bool Alg_Foundation::Impl::popCameraDlg(void* parent)
	{
		if (nullptr == algosettingdlg)
		{
			algosettingdlg = std::make_shared<Qtalgosettingdlg>((QWidget*)parent);
			algosettingdlg->SetTestCallback(std::bind(&Alg_Foundation::Impl::doing, this, std::placeholders::_1, std::placeholders::_2));
		}

		algosettingdlg->SetLastImage(lastimg);
		algosettingdlg->SetLastParam(m_checkparam);
		algosettingdlg.get()->show();
		LOGW("popCameraDlg successfully");
		return false;
	}

	bool Alg_Foundation::Impl::readAlgoParam()
	{
		QSettings algsetting(qApp->applicationDirPath() + "/defaultModel/" + m_scamserial.c_str() + ".ini", QSettings::IniFormat);
		m_checkparam._iThread = algsetting.value("Default1/_Thread", 100).toInt();



		LOGW("initAlgoparam successfully");
		return true;
	}

	bool Alg_Foundation::Impl::saveAlgoParam()
	{
		QSettings algsetting(qApp->applicationDirPath() + "/defaultModel/" + m_scamserial.c_str() + ".ini", QSettings::IniFormat);
		algsetting.setValue("Default1/_Thread", m_checkparam._iThread);
		return false;
	}

	int Alg_Foundation::Impl::doing(wikky_algo::SingleMat& data, wikky_algo::CheckParam* m_checkparam)
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
