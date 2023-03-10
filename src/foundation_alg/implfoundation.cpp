#include "foundation.h"
#include <iostream>
#include <QSettings>
#include <QCoreapplication>
#include "implfoundation.h"
#include "logger.h"
#include <functional>
#include <future>
#include <fstream>
#include <CppAlgFunc.h>
namespace wikky_algo
{
	void Alg_Foundation::Impl::updateparamfromdlg(CheckParam _param)
	{
		m_checkparam = _param;
	}
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
			algosettingdlg->UpdatetoalgoImpl(std::bind(&Alg_Foundation::Impl::updateparamfromdlg, this, std::placeholders::_1));
		}

		algosettingdlg->SetLastImage(lastimg);
		algosettingdlg->SetLastParam(m_yamlparams);
		algosettingdlg.get()->show();
		LOGW("popCameraDlg successfully");
		return false;
	}

	bool Alg_Foundation::Impl::readAlgoParam()
	{
		//QSettings algsetting(qApp->applicationDirPath() + "/defaultModel/" + m_scamserial.c_str() + ".ini", QSettings::IniFormat);
		//m_checkparam._iThread = algsetting.value("Default1/_Thread", 100).toInt();
		QString str = QString("%1/defaultModel/%2.yaml").arg(qApp->applicationDirPath()).arg(m_scamserial.c_str());
		m_yamlparams = YAML::LoadFile(str.toStdString());

		Node2Param(m_checkparam, m_yamlparams);

		LOGW("initAlgoparam successfully");
		return true;
	}

	bool Alg_Foundation::Impl::saveAlgoParam()
	{
		//QSettings algsetting(qApp->applicationDirPath() + "/defaultModel/" + m_scamserial.c_str() + ".ini", QSettings::IniFormat);
		//algsetting.setValue("Default1/_Thread", m_checkparam._iThread);

		QString str = QString("%1/defaultModel/%2.yaml").arg(qApp->applicationDirPath()).arg(m_scamserial.c_str());
		std::ofstream fout(str.toStdString().c_str());

		Param2Node(m_checkparam, m_yamlparams);

		try
		{
			fout << m_yamlparams;

			fout.close();
		}	
		catch (YAML::ParserException e)
		{
		}
		catch (YAML::RepresentationException e)
		{
		}
		catch (YAML::Exception e)
		{
		}
		return false;
	}

	int Alg_Foundation::Impl::doing(wikky_algo::SingleMat& data, wikky_algo::CheckParam* _checkparam)
	{
		lastimg = data.imgori.clone();
		cv::Mat gray;
		cv::Mat RED = cv::Mat(lastimg.size(), CV_8UC3, cv::Scalar(255, 0, 0));
		cv::Mat GREEN = cv::Mat(lastimg.size(), CV_8UC3, cv::Scalar(0, 255, 0));
		cv::Mat BLUE = cv::Mat(lastimg.size(), CV_8UC3, cv::Scalar(0, 0, 255));
		cv::cvtColor(lastimg, gray, cv::COLOR_BGR2GRAY);
		cv::threshold(gray, gray, _checkparam ? _checkparam->_iThreadY: m_checkparam._iThreadY, 255, cv::THRESH_BINARY);

		cv::findContours(gray.clone(), condidat1, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

		wikky_Dll::SelectContour(condidat1, contours_Selected, "height", "and", 75, 90);
		RED.copyTo(data.imgrst, gray);
		//cv::putText(data.imgrst, buf, cv::Point(100, 100), 2, 1.0, cv::Scalar(0, 255, 255));
		return -1;
	}

};
