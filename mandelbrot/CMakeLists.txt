cmake_minimum_required(VERSION 3.22.0)

project(mandelbrot VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(mandelbrot_HDRS JobResult.h Job.h MandelbrotCalculator.h MandelbrotWidget.h MandelbrotMainWindow.h)

set(mandelbrot_SRC Job.cpp MandelbrotCalculator.cpp MandelbrotWidget.cpp MandelbrotMainWindow.cpp main.cpp)

set(mandelbrot_UI MandelbrotMainWindow.ui)

qt5_wrap_ui(mandelbrot_UI_GENERATED_FILES ${mandelbrot_UI} )
qt5_wrap_cpp(mandelbrot_HDRS_SRCS ${mandelbrot_HDRS} ) 

# WIN32 is needed to disable console poping up in GUI
# It adds linker options /SUBSYSTEM:windows /ENTRY:mainCRTStartup
add_executable(mandelbrot WIN32
    ${mandelbrot_HDRS}
    ${mandelbrot_SRC}
    ${mandelbrot_UI}
    ${mandelbrot_UI_GENERATED_FILES}
    ${mandelbrot_HDRS_SRCS}
    resources.qrc
)

# Hack to fix errors with include of the ui*.h files
target_include_directories(mandelbrot PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(mandelbrot Qt5::Widgets)

if (WIN32)
    set(mandelbrot_PATH "PATH=%PATH%" "$ENV{Qt5_PATH}")
    set_target_properties(mandelbrot PROPERTIES VS_DEBUGGER_ENVIRONMENT "${mandelbrot_PATH}")
endif()
