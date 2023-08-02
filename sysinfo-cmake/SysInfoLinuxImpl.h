
#pragma once
#include <QtGlobal>
#include <QVector>

#include "SysInfo.h"


class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<qulonglong> mCpuLoadLastValues;

    QVector<qulonglong> cpuRawData();
};
