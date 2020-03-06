#include "sysinfo.h"

#include <QtGlobal>

#ifdef Q_OS_WIN
    #include "sysinfowindowsimpl.h"
#elif defined(Q_OS_LINUX)
    #include  "sysinfolinuximpl.h"
#endif

SysInfo::SysInfo()
{

}

SysInfo::~SysInfo()
{

}

SysInfo& SysInfo::instance()
{
    #ifdef Q_OS_WIN
        // thread safe instatiation be the compiler
        static SysInfoWindowsImpl singleton;
    #elif defined(Q_OS_LINUX)
        static SysInfoLinuxImpl singleton;
    #endif

    return singleton;
}
