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
        cv::Mat lastimg;
        std::shared_ptr<Qtalgosettingdlg> algosettingdlg = nullptr;
        std::string m_scamserial;

        // checkparam
        CheckParam m_checkparam;
        YAML::Node m_yamlparams;
        void updateparamfromdlg(CheckParam _param);
    public:
        Impl();
        ~Impl();
        bool initAlgoparam(std::string& camserial);
        bool popCameraDlg(void* parent);
        bool readAlgoParam();
        bool saveAlgoParam();

        int doing(wikky_algo::SingleMat& data, wikky_algo::CheckParam* m_checkparam = nullptr);

    };
}  // namespace wikky_algo
