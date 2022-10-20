#ifndef CORE_COMMON
#define CORE_COMMON
#include <opencv2/opencv.hpp>
namespace smartmore
{
	struct DeviceStatus
	{
		int error_status;
		float pos_x;
		float pos_y;
		float pos_z;
		float width;
		bool board_ready;
		bool motion_state;
		bool signal_light_red;
		bool signal_light_yellow;
		bool signal_light_green;
		bool signal_buzzer_alarm;
	};

	struct _camInfo
	{
		std::string CameraBrand;
		std::string CameraSerialNumber;

	};
	struct _saveInfo
	{
		std::string FilePath;
		int SaveNumber;
	};
	struct _systemInfo
	{
		std::vector<_saveInfo> SaveInfo;
	};
	struct InitCoreServce
	{
		// camera
		std::vector<_camInfo> CameraInfo;

		// PLC
		std::string IPPlC;
		int PortPlC;

		// Light
		std::string ComLight;

		// Power
		std::string ComPower;
	};
	struct GrabPositionInfo
	{
		std::string device;
		unsigned int serial_num;
		float x;
		float y;
	};
	struct SingleMat
	{
		cv::Mat imgori;
		cv::Mat imgrst;
		size_t index;
		bool bresult;
		std::string cam_serial;
		std::vector<std::string> error_message;
	};


	using DataCallback = std::function<void(SingleMat&)>;

	enum class MoveDirection
	{
		kStop = 0,
		kUp,
		kDown,
		kRight,
		kLeft,
	};

	struct CameraInfo
	{
		int cam_width;
		int cam_height;
		float pix_size;
	};
}
#endif // !CORE_COMMON