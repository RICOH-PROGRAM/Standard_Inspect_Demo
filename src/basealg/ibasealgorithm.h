#pragma once

#include <condition_variable>
#include <memory>
#include <string>
#include <list>
#include <stdint.h>
#include <thread>
#include <chrono>
#include <future>
#include <functional>
#include <intsafe.h>
#include "common.h"

namespace basealgo
{
class IBaseAlg
{
public:
    virtual ~IBaseAlg() {}
    virtual bool initAlgoparam(std::string&) = 0;
    virtual bool popCameraDlg(void* parent, void* layout) = 0;
    virtual int doing(smartmore::SingleMat&) = 0;
};

typedef IBaseAlg* (__stdcall* pExportALG)();
typedef void (__stdcall* pDeleteALG)(IBaseAlg*);
}  // namespace cameramanager

