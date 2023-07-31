#include "SysInfoWindowsImpl.h"

#include "Windows.h"

SysInfoWindowsImpl::SysInfoWindowsImpl()
    : SysInfo()
{

}

void SysInfoWindowsImpl::init()
{
    mCpuLoadLastValues = cpuRawData();
}

QVector<qulonglong> SysInfoWindowsImpl::cpuRawData()
{
    FILETIME idleTime,
        kernelTime,
        userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    QVector<qulonglong> rawData{ convertFileTime(idleTime), convertFileTime(kernelTime), convertFileTime(userTime) };

    return rawData;
}

qulonglong SysInfoWindowsImpl::convertFileTime(const FILETIME& filetime) const
{
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart = filetime.dwLowDateTime;
    largeInteger.HighPart = filetime.dwHighDateTime;
    return largeInteger.QuadPart;
}

double SysInfoWindowsImpl::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = mCpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    mCpuLoadLastValues = secondSample;

    auto currentIdle = secondSample[0] - firstSample[0];
    auto currentKernel = secondSample[1] - firstSample[1];
    auto currentUser = secondSample[2] - firstSample[2];
    auto currentSystem = currentKernel + currentUser;

    auto percent = (currentSystem - currentIdle) * 100.0 / currentSystem;
    return qBound(0.0, percent, 100.0);
}

double SysInfoWindowsImpl::memoryUsed()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);

    qulonglong memoryPhysicalUsed = memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;
    return static_cast<double>(memoryPhysicalUsed) / static_cast<double>(memoryStatus.ullTotalPhys) * 100;
}