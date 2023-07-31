#pragma once

#include "SysInfo.h"

#include <QtGlobal>
#include <QVector>

// can be moved to the cpp file
typedef struct _FILETIME FILETIME;

class SysInfoWindowsImpl: public SysInfo
{
public:
    SysInfoWindowsImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<qulonglong> cpuRawData();
    qulonglong convertFileTime(const FILETIME& filetime) const;

    QVector<qulonglong> mCpuLoadLastValues;
};