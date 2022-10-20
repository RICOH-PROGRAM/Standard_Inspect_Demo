#include "ibasealgorithm.h"

namespace smartmore
{
class Alg_Foundation : public basealgo::IBaseAlg
{
   public:
       Alg_Foundation();
       ~Alg_Foundation();
    class Impl;

   private:
    std::shared_ptr<Impl> impl_;

};

}  // namespace smartmore
extern "C" __declspec(dllexport) basealgo::IBaseAlg * __stdcall CreateExportCameraObj();
extern "C" __declspec(dllexport) void __stdcall DeleteExportCameraObj(
    basealgo::IBaseAlg*);