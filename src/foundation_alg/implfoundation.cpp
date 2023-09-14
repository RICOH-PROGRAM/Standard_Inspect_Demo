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
		std::replace(m_scamserial.begin(), m_scamserial.end(), '/', '_');
		std::replace(m_scamserial.begin(), m_scamserial.end(), ':', '_');

		QString str = QString("%1/defaultModel/%2.yaml").arg(qApp->applicationDirPath()).arg(m_scamserial.c_str());
		try
		{
			m_yamlparams = YAML::LoadFile(str.toStdString());
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
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
		data.imgrst = data.imgori.clone();
		cv::Mat gray;
		cv::Mat RED = cv::Mat(lastimg.size(), CV_8UC3, cv::Scalar(255, 0, 0));
		cv::Mat GREEN = cv::Mat(lastimg.size(), CV_8UC3, cv::Scalar(0, 255, 0));
		cv::Mat BLUE = cv::Mat(lastimg.size(), CV_8UC3, cv::Scalar(0, 0, 255));
		cv::cvtColor(lastimg, gray, cv::COLOR_BGR2GRAY);
		//二值化
		cv::threshold(gray, gray, 90, 255, cv::THRESH_BINARY);//_checkparam ? _checkparam->_iThreadY: m_checkparam._iThreadY
		
		//找轮廓
		cv::findContours(gray.clone(), condidat1, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		
		//找最大轮廓（外圆环）
		std::sort(condidat1.begin(), condidat1.end(), [](const std::vector<cv::Point>& c1, const std::vector<cv::Point>& c2) {
			return cv::contourArea(c1) > cv::contourArea(c2);
			});

		// 计算外圆环的直径和面积
		double outerDiameter = 0.0;
		double outerArea = 0.0;

		if (!condidat1.empty()) {
			cv::RotatedRect outerRect = cv::minAreaRect(condidat1[0]);

			outerDiameter = (std::max)(outerRect.size.width, outerRect.size.height);
			outerArea = cv::contourArea(condidat1[0]);
		}

		// 定义面积阈值
		const double SMALL_AREA_THRESHOLD = 2.3e+06;
		const double LARGE_AREA_THRESHOLD = 2.7e+06;

		// 根据面积大小进行分类
		QString category;
		if (outerArea < SMALL_AREA_THRESHOLD) {
			category = QString::fromLocal8Bit("Small");
		}
		else if (outerArea >= SMALL_AREA_THRESHOLD && outerArea < LARGE_AREA_THRESHOLD) {
			category = QString::fromLocal8Bit("Broke");
		}
		else {
			category = QString::fromLocal8Bit("Big");
		}

		//wikky_Dll::SelectContour(condidat1, contours_Selected, "area", "and", 1, _checkparam ? _checkparam->_iThreadZ : m_checkparam._iThreadZ);
		//if (_checkparam)
		//{
		cv::drawContours(data.imgrst, condidat1, 0, cv::Scalar(0, 0, 255), 25, 8);
		//	cv::drawContours(data.imgrst, contours_Selected, -1, cv::Scalar(255, 0, 0), 5, 8);
		//}
		strcpy(buf, category.toLocal8Bit());
		cv::putText(data.imgrst, buf, cv::Point(100, 200), 1, 5.0, cv::Scalar(0, 255, 255),3);
		return -1;
	}

};
