#include "ibasealgorithm.h"

namespace smartmore
{
class Alg_Foundation : public basealgo::IBaseAlg
{
   public:
       Alg_Foundation();
       ~Alg_Foundation();


       int doing(smartmore::SingleMat&);

   private:
       class Impl;
       std::shared_ptr<Impl> impl_;

};
    
}  // namespace smartmore
extern "C" __declspec(dllexport) basealgo::IBaseAlg * __stdcall CreateExportAlgObj();
extern "C" __declspec(dllexport) void __stdcall DeleteExportAlgObj(
    basealgo::IBaseAlg*);