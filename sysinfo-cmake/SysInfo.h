#pragma once

// Strategy pattern
// SysInfo is singleton
class SysInfo
{
public:
    static SysInfo& instance();
    virtual ~SysInfo() = default;
    SysInfo(const SysInfo& rhs) = delete;
    SysInfo& operator=(const SysInfo& rhs) = delete;

    virtual void init() = 0;
    virtual double cpuLoadAverage() = 0;
    virtual double memoryUsed() = 0;

protected:
    explicit SysInfo() = default;
};
