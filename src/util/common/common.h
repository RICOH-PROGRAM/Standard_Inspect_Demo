#ifndef CORE_COMMON
#define CORE_COMMON
#include <opencv2/opencv.hpp>
namespace wikky_algo
{
#define DLLINTERFACE "1.2"		//add sn_fromscanner
	struct SingleMat
	{
		int camPos = -1;
		std::chrono::steady_clock::time_point starttime;
		cv::Mat imgori;
		cv::Mat imgrst;
		size_t index;
		int groupsize;
		bool bresult;
		bool _bshow = true;
		std::string sn_fromscanner;
		std::string cam_serial;
		std::vector<std::string> error_message;
	};
	struct CheckParam
	{
		std::string cam_serial;
		float th_conf = 0.7;
		float th_nms = 0.45;
		float th_obj = 0.7;

		float R_ratio = 0;
		float G_ratio = 0;
		float B_ratio = 1.0;
		float GrayValueThld = 100;
		float AreaThld = 100;

		int roi_x = 145;
		int roi_y = 320;
		int roi_w = 2133;
		int roi_h = 1453;

		float defectAreaThreshold = 900;
		float defectLengethThreshold = 30;
		float fluorescenceOp = 0;
		float fluorescenceOp1Threshold = 100;
		float fluorescenceOp2Threshold = 100;
	};


	using TestCallback = std::function<int(SingleMat&, CheckParam*)>;
	using UpdateParam = std::function<void(CheckParam&)>;
}

#endif // !CORE_COMMON