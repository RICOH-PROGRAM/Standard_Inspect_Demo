#ifndef CORE_COMMON
#define CORE_COMMON
#include <opencv2/opencv.hpp>
namespace wikky_algo
{
#define DLLINTERFACE "1.1"
	struct SingleMat
	{
		int camPos = -1;
		std::chrono::steady_clock::time_point starttime;
		cv::Mat imgori;
		cv::Mat imgrst;
		size_t index;
		int groupsize;
		bool bresult;
		std::string sn_fromscanner;
		std::string cam_serial;
		std::vector<std::string> error_message;
	};
	struct CheckParam
	{
		std::string cam_serial;
		int _iThreadX = 0;
		int _iThreadY = 0;
		int _iThreadZ = 0;
	};


	using TestCallback = std::function<int(SingleMat&, CheckParam*)>;
	using UpdateParam = std::function<void(CheckParam&)>;
}

#endif // !CORE_COMMON