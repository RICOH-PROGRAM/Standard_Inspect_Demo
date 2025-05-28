#ifndef CORE_COMMON
#define CORE_COMMON
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
namespace wikky_algo
{
#define DLLINTERFACE "4.0"		
#define FORMATMONO	1000
#define FORMATBGR	1001
#define FORMATDEPTH	1002
#define FORMATBAYER 1003

	struct SingleMat
	{
		int camPos = -1;
		std::chrono::steady_clock::time_point starttime;
		int w, h, format;
		char* imgori = nullptr;
		cv::Mat imgrst;
		size_t index;
		int groupsize;
		int _iresult;
		bool _bshow = true;
		std::string sn_fromscanner;
		std::string cam_serial;
		std::vector<std::string> error_message;
		~SingleMat()
		{
			if (imgori)
			{
				delete[] imgori;
				imgori = nullptr;
			}
		}
	};
	struct CheckParam
	{
		std::string cam_serial;

		int _iThreadX = 145;
		int _iThreadY = 320;
		int _iThreadZ = 2133;
	};

	template <typename T>
	T getValue(YAML::Node _param, std::string errortype, std::string errorparam, T defaultvalue)
	{
		T val;
		try
		{
			val = _param[errortype][errorparam]["value"].as<T>();
		}
		catch (YAML::Exception e)
		{
			return defaultvalue;
		}
		return val;
	}
	CheckParam _Node2Param(YAML::Node node);
	YAML::Node _Param2Node(CheckParam , YAML::Node);
	using TestCallback = std::function<int(SingleMat&, CheckParam*)>;
	using UpdateParam = std::function<void(CheckParam&)>;
}

#endif // !CORE_COMMON