#include "ibasealgorithm.h"
#include "algosettingdlg.h"

namespace smartmore
{
    class Alg_Foundation::Impl : public basealgo::IBaseAlg
    {
    private:
        std::thread::id tid;
        _Thrd_t t;
        char* buf = new char[10];
        cv::Mat lastimg;
        std::shared_ptr<Qtalgosettingdlg> algosettingdlg = nullptr;
    public:
        Impl();
        ~Impl();
        bool initAlgoparam(std::string& camserial);
        bool popCameraDlg(void* parent);
        bool saveAlgoParam();

        int doing(smartmore::SingleMat& data);

    };
}  // namespace smartmore
