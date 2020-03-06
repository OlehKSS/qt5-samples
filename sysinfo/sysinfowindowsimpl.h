#ifndef SYSINFOWINDOWSIMPL_H
#define SYSINFOWINDOWSIMPL_H

#include <QtGlobal>
#include <QVector>

#include "sysinfo.h"

typedef struct _FILETIME FILETIME;

class SysInfoWindowsImpl : public SysInfo
{
public:
    SysInfoWindowsImpl();
    // override ensures that the function is declared as virtual in the base class
    // otherwise a compile error occurs
    void init() override;
    double memoryUsed() override;
    double cpuLoadAverage() override;

private:
    QVector<qulonglong> mCpuLoadLastValues;
    QVector<qulonglong> cpuRawData();
    qulonglong convertFileTime(const FILETIME& filetime) const;
};

#endif // SYSINFOWINDOWSIMPL_H
