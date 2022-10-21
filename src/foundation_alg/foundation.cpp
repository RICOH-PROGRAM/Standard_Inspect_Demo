#include "foundation.h"

#include <iostream>

#include "logger.h"
namespace smartmore
{
    class Alg_Foundation::Impl : public basealgo::IBaseAlg
    {
    public:
        Impl()
        {
        }

        ~Impl()
        {
        }

        int Alg_Foundation::Impl::doing(smartmore::SingleMat& data) { return -1; }

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