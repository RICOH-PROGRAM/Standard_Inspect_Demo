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

    };

    Alg_Foundation::Alg_Foundation() : impl_(std::make_unique<Impl>()) {}

    Alg_Foundation::~Alg_Foundation() {}
}

extern "C" __declspec(dllexport) basealgo::IBaseAlg * __stdcall CreateExportCameraObj()
{
    return new smartmore::Alg_Foundation();
};
extern "C" __declspec(dllexport) void __stdcall DeleteExportCameraObj(
    basealgo::IBaseAlg * p)
{
    delete p;
    p = nullptr;
};