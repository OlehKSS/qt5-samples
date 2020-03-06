#ifndef SYSINFO_H
#define SYSINFO_H


class SysInfo
{
public:
    // make it a singleton
    static SysInfo& instance();
    // to ensure that any deletion of an instance of a derived class (from a base
    // class pointer) will call the derived class destructor and not only the base
    // class destructor
    virtual ~SysInfo();

    virtual void init() = 0;
    virtual double cpuLoadAverage() = 0;
    virtual double memoryUsed() = 0;

protected:
    // hide constructor from the outer world, but keep it for children
    explicit SysInfo();

private:
    // hide everything else
    SysInfo(const SysInfo& rhs);
    SysInfo& operator=(const SysInfo& rhs);
    // or this functions may be declared delelted
    // as 'myFunction() = delete'
};

#endif // SYSINFO_H
