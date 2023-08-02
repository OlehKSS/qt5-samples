cmake_minimum_required(VERSION 3.22.0)

project(sysinfo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

if (WIN32)
    set(sysinfo_HDRS 
        SysInfoMainWindow.h
        SysInfoWidget.h
        CpuWidget.h
        MemoryWidget.h
        SysInfo.h
        SysInfoWindowsImpl.h)

    set(sysinfo_SRC main.cpp
        SysInfoMainWindow.cpp
        SysInfoWidget.cpp
        CpuWidget.cpp
        MemoryWidget.cpp
        SysInfo.cpp
        SysInfoWindowsImpl.cpp)
else()
    set(sysinfo_HDRS 
        SysInfoMainWindow.h
        SysInfoWidget.h
        CpuWidget.h
        MemoryWidget.h
        SysInfo.h
        SysInfoLinuxImpl.h)
    
    set(sysinfo_SRC main.cpp
        SysInfoMainWindow.cpp
        SysInfoWidget.cpp
        CpuWidget.cpp
        MemoryWidget.cpp
        SysInfo.cpp
        SysInfoLinuxImpl.cpp)
endif()

set(sysinfo_UI SysInfoMain.ui)

# WIN32 is needed to disable console poping up in GUI
# It adds linker options /SUBSYSTEM:windows /ENTRY:mainCRTStartup
add_executable(sysinfo WIN32
    ${sysinfo_HDRS}
    ${sysinfo_SRC}
    ${sysinfo_UI}
    resources.qrc
)

target_link_libraries(sysinfo Qt5::Widgets Qt5::Charts)

if (WIN32)
    set(sysinfo_PATH "PATH=%PATH%" "$ENV{Qt5_PATH}")
    set_target_properties(sysinfo PROPERTIES VS_DEBUGGER_ENVIRONMENT "${sysinfo_PATH}")
endif()
