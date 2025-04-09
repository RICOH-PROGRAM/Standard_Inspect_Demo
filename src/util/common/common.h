#ifndef CORE_COMMON
#define CORE_COMMON
#include <opencv2/opencv.hpp>
namespace wikky_algo
{
#define DLLINTERFACE "2.0"		//change imgori to charptr and add w,h,c,ch;
	struct SingleMat
	{
		int camPos = -1;
		std::chrono::steady_clock::time_point starttime;
		int w, h, _channel, _depth;
		char* imgori;
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


	using TestCallback = std::function<int(SingleMat&, CheckParam*)>;
	using UpdateParam = std::function<void(CheckParam&)>;
}

#endif // !CORE_COMMON