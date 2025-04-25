#include "foundation.h"
#include <iostream>
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
		LOGSET(SPDLOG_LEVEL_TRACE);
		LOGT("DLLInterface:{}", DLLINTERFACE);
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

		//QString str = QString("%1/defaultModel/%2.yaml").arg(qApp->applicationDirPath()).arg(_scamserial.c_str());
		//try
		//{
		//	m_yamlparams = YAML::LoadFile(str.toStdString());
		//}
		//catch(const std::exception& e)
		//{
		//	std::cerr << e.what() << '\n';
		//}
		//Node2Param(m_checkparam, m_yamlparams);

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

		//QString str = QString("%1/defaultModel/%2.yaml").arg(qApp->applicationDirPath()).arg(_scamserial.c_str());
		//std::ofstream fout(str.toStdString().c_str());

		//Param2Node(m_checkparam, m_yamlparams);

		try
		{
			//fout << m_yamlparams;

			//fout.close();
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
		if (nullptr == _lastimgdata)
		{
			switch (data.format)
			{
			case FORMATDEPTH:
				_channel = 1;
				_depth = sizeof(double);
				break;
			case FORMATBAYER:
			case FORMATMONO:
				_channel = 1;
				_depth = sizeof(uchar);
				break;
			case FORMATBGR:
				_channel = 3;
				_depth = sizeof(uchar);
				break;
			default:
				LOGE("ERROR FORMAT");
			}
			_width = data.w;
			_height = data.h;
			_lastimgdata = new char[_width * _height * _depth * _channel];
			lastimg = cv::Mat(cv::Size(_width, _height), CV_MAKETYPE(_depth == 8 ? CV_64F : CV_8U, _channel), _channel);
		}
		memcpy(_lastimgdata, (void*)data.imgori, _width * _height * _depth * _channel);
		memcpy(lastimg.data, _lastimgdata, _width * _height * _depth * _channel);
		cv::Mat bgr;
		if (data.format == FORMATBAYER)
		{
			cv::cvtColor(lastimg, bgr, cv::COLOR_BayerRG2RGB);
			cv::cvtColor(lastimg, data.imgrst, cv::COLOR_BayerRG2RGB);
		}
		else
		{
			if (lastimg.channels() == 1)
				cv::cvtColor(lastimg, data.imgrst, cv::COLOR_GRAY2BGR);
			else
				data.imgrst = lastimg.clone();
		}
		int _rand = rand() % 5;
		std::string st = "OK";
		switch ( _rand)
		{
		case 0:
			st = "NG0";
			break;
		case 1:
			st = "NG1";
			break;
		default:
			break;
		}
		cv::putText(data.imgrst, st.c_str(), cv::Point(100, 200), 1, 5.0, cv::Scalar(0, 255, 255), 3);
		data.error_message.push_back(st);

		//data.error_message.push_back(QString::number(_rand).toStdString());
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
