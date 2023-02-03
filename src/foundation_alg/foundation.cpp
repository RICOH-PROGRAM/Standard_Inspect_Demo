#include "foundation.h"

#include <iostream>

#include "logger.h"
namespace smartmore
{
    class Alg_Foundation::Impl : public basealgo::IBaseAlg
    {
    private:
        std::thread::id tid;
        _Thrd_t t;
        char* buf = new char[10];
    public:
        Impl()
        {
            tid = std::this_thread::get_id();
            t = *(_Thrd_t*)(char*)&tid;
            unsigned int nId = t._Id;
            itoa(nId, buf, 10);
        }

        ~Impl()
        {
        }

        int Alg_Foundation::Impl::doing(smartmore::SingleMat& data) 
        { 
            data.imgrst = data.imgori.clone();
            cv::putText(data.imgrst, buf, cv::Point(100, 100), 2, 1.0, cv::Scalar(0, 255, 255));
            return -1;
        }

    };

    Alg_Foundation::Alg_Foundation() : impl_(std::make_unique<Impl>()) {}

    Alg_Foundation::~Alg_Foundation() {}

    int Alg_Foundation::doing(smartmore::SingleMat& data)
    {
        return impl_->doing(data);
    }

}

extern "C" __declspec(dllexport) basealgo::IBaseAlg * __stdcall CreateExportAlgObj()
{
    return new smartmore::Alg_Foundation();
};
extern "C" __declspec(dllexport) void __stdcall DeleteExportAlgObj(
    basealgo::IBaseAlg * p)
{
    delete p;
    p = nullptr;
};