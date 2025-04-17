#include "ibasealgorithm.h"
#include "algosettingdlg.h"
#include "yaml-cpp/yaml.h"

namespace wikky_algo
{
    class Alg_Foundation::Impl : public wikky_algo::IBaseAlg
    {
    private:
        std::thread::id tid;
        _Thrd_t t;
        char* buf = new char[10];
        char* _lastimgdata =nullptr;
        cv::Mat lastimg;
        int _width, _height;
        int _depth, _channel;
        std::shared_ptr<Qtalgosettingdlg> algosettingdlg = nullptr;
        std::string m_scamserial;

        double SMALL_AREA_THRESHOLD = 2.3e+06;
        double LARGE_AREA_THRESHOLD = 2.7e+06;

        // checkparam
        CheckParam m_checkparam;
        YAML::Node m_yamlparams;
        void updateparamfromdlg(CheckParam _param);
    /// <summary>
        std::vector<std::vector<cv::Point>>contours, con_temp, contours_Selected, condidat1, condidat2;
    /// </summary>
    public:
        Impl();
        ~Impl();
        bool initAlgoparam(std::string& camserial);
        bool popCameraDlg(void* parent);
        bool readAlgoParam();
        bool saveAlgoParam();
        bool setLogLevel(int);
        int doing(wikky_algo::SingleMat& data, wikky_algo::CheckParam* m_checkparam = nullptr);

    };
}  // namespace wikky_algo
