#include "foundation.h"
#include <iostream>
#include "implfoundation.h"
#include "logger.h"
#include <functional>
#include <future>
#include <fstream>
#include <format>
#include  <direct.h>  
namespace wikky_algo
{
	void Alg_Foundation::Impl::updateparamfromdlg(CheckParam _param)
	{
		m_checkparam = _param;
	}
	CheckParam Alg_Foundation::Impl::Node2Param(YAML::Node node)
	{
		CheckParam _param  = _Node2Param(node);
		return _param;
	}
	YAML::Node Alg_Foundation::Impl::Param2Node(CheckParam checkparam, YAML::Node _node)
	{
        YAML::Node _param = _Param2Node(checkparam, _node);
        return _param;
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

	bool Alg_Foundation::Impl::GetParam(void* parent)
	{
		*(YAML::Node*)parent = m_yamlparams;
		return true;
	}

	bool Alg_Foundation::Impl::SetParam(void* parent)
	{
		m_yamlparams = *(YAML::Node*)parent;

		std::cout<< "GetParam" << std::endl;
		std::cout<<m_yamlparams<<std::endl;
		std::cout<< "GetParam" << std::endl;
		m_checkparam = Node2Param(m_yamlparams);

		m_yamlparams = Param2Node(m_checkparam,m_yamlparams);
		std::cout << "GetParam" << std::endl;
		std::cout << m_yamlparams << std::endl;
		std::cout << "GetParam" << std::endl;
		return true;
	}

	bool Alg_Foundation::Impl::SaveParam()
	{
		saveAlgoParam();
		return true;
	}


	bool Alg_Foundation::Impl::readAlgoParam()
	{
		char   buffer[MAX_PATH];
		getcwd(buffer, MAX_PATH);
		std::string sts = buffer;
		std::string _scamserial = m_scamserial;
		std::replace(_scamserial.begin(), _scamserial.end(), '/', '_');
		std::replace(_scamserial.begin(), _scamserial.end(), ':', '_');

		std::string _path = std::format("{}/defaultModel/{}.yaml", sts ,_scamserial);
		try
		{
			m_yamlparams = YAML::LoadFile(_path);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		m_checkparam = Node2Param(m_yamlparams);

		LOGW("initAlgoparam successfully");
		return true;
	}

	bool Alg_Foundation::Impl::saveAlgoParam()
	{
		char   buffer[MAX_PATH];
		getcwd(buffer, MAX_PATH);
		std::string sts = buffer;
		std::string _scamserial = m_scamserial;
		std::replace(_scamserial.begin(), _scamserial.end(), '/', '_');
		std::replace(_scamserial.begin(), _scamserial.end(), ':', '_');

		std::string _path = std::format("{}/defaultModel/{}.yaml", sts, _scamserial);
		std::ofstream fout(_path);

		m_yamlparams = Param2Node(m_checkparam,m_yamlparams);

		try
		{
			fout << m_yamlparams;
			fout.close();
		}	
		catch (YAML::ParserException e)
		{
			return false;
		}
		catch (YAML::RepresentationException e)
		{
			return false;
		}
		catch (YAML::Exception e)
		{
			return false;
		}
		return true;
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
			cv::cvtColor(lastimg, bgr, cv::COLOR_BayerRG2BGR);
			cv::cvtColor(lastimg, data.imgrst, cv::COLOR_BayerRG2RGB);
		}
		else
		{
			if (lastimg.channels() == 1)
			{
				cv::cvtColor(lastimg, data.imgrst, cv::COLOR_GRAY2BGR);
				cv::cvtColor(lastimg, bgr, cv::COLOR_GRAY2BGR);
			}
			else
			{
				data.imgrst = lastimg.clone();
				bgr = lastimg.clone();
			}
		}
		int _rand = rand() % 10;
		std::string st = "OK";
		switch ( _rand)
		{
		case 0:
			st = "a1";
			data._iresult = 2;
			break;
		case 1:
			st = "a2";
			data._iresult = 2;
			break;
		case 2:
			st = "a3";
			data._iresult = 2;
			break;
		case 3:
			st = "a4";
			data._iresult = 2;
			break;
		case 4:
			st = "a5";
			data._iresult = 2;
			break;
		default:
			data._iresult = 1;
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
