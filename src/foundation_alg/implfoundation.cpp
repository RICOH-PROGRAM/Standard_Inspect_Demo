#include "foundation.h"
#include <iostream>
#include <QSettings>
#include <QCoreapplication>
#include "implfoundation.h"
#include "logger.h"
#include <functional>
#include <future>
#include <fstream>
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

		std::string _scamserial = m_scamserial;
		std::replace(_scamserial.begin(), _scamserial.end(), '/', '_');
		std::replace(_scamserial.begin(), _scamserial.end(), ':', '_');

		QString str = QString("%1/defaultModel/%2.yaml").arg(qApp->applicationDirPath()).arg(_scamserial.c_str());
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

		std::string _scamserial = m_scamserial;
		std::replace(_scamserial.begin(), _scamserial.end(), '/', '_');
		std::replace(_scamserial.begin(), _scamserial.end(), ':', '_');

		QString str = QString("%1/defaultModel/%2.yaml").arg(qApp->applicationDirPath()).arg(_scamserial.c_str());
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
	bool Alg_Foundation::Impl::setLogLevel(int _i)
	{
		LOGSET(_i);
		return true;
	}

	int Alg_Foundation::Impl::doing(wikky_algo::SingleMat& data, wikky_algo::CheckParam* _checkparam)
	{
		lastimg = data.imgori.clone();
		data.imgrst = data.imgori.clone();

		cv::putText(data.imgrst, buf, cv::Point(100, 200), 1, 5.0, cv::Scalar(0, 255, 255),3);
		data.error_message.push_back("OK");

		data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//if (m_scamserial == "D:/image1")
		//{
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//}
		//if (m_scamserial == "D:/image2")
		//{
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//	data.error_message.push_back(QString::number(rand() % 2 + 1).toStdString());
		//}

		

			
		return -1;
	}

};
