#include "foundation.h"
#include "implfoundation.h"

#include <iostream>
#include "logger.h"
namespace smartmore
{

    Alg_Foundation::Alg_Foundation() : impl_(std::make_unique<Impl>()) {}

    Alg_Foundation::~Alg_Foundation() {}

    bool Alg_Foundation::initAlgoparam(std::string& camserial)
    {
        return impl_->initAlgoparam(camserial);
    }

    bool Alg_Foundation::popCameraDlg(void* parent, void* layout)
    {
        return impl_->popCameraDlg(parent, layout);
    }

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