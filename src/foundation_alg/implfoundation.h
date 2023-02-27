#include "ibasealgorithm.h"

namespace smartmore
{
    class Alg_Foundation::Impl : public basealgo::IBaseAlg
    {
    private:
        std::thread::id tid;
        _Thrd_t t;
        char* buf = new char[10];
        cv::Mat lastimg;
    public:
        Impl();
        ~Impl();
        bool initAlgoparam(std::string& camserial);
        bool popCameraDlg(void* parent, void* layout);
        bool saveAlgoParam();

        int doing(smartmore::SingleMat& data);

    };
}  // namespace smartmore
