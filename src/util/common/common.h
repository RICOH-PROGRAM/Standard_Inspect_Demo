#ifndef CORE_COMMON
#define CORE_COMMON
#include <opencv2/opencv.hpp>
namespace smartmore
{
	struct SingleMat
	{
		int camPos = -1;
		cv::Mat imgori;
		cv::Mat imgrst;
		size_t index;
		bool bresult;
		std::string cam_serial;
		std::vector<std::string> error_message;
	};


	using DataCallback = std::function<void(SingleMat&)>;
}
#endif // !CORE_COMMON