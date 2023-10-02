set(desktop_MOC_HDRS
    AlbumListWidget.h
    AlbumWidget.h
    PictureDelegate.h
    PictureWidget.h
    GalleryWidget.h
    MainWindow.h)

set(desktop_HDRS
    ${desktop_MOC_HDRS}
    ThumbnailProxyModel.h)

set(desktop_SRCS
    AlbumListWidget.cpp
    AlbumWidget.cpp
    ThumbnailProxyModel.cpp
    PictureDelegate.cpp
    PictureWidget.cpp
    GalleryWidget.cpp
    MainWindow.cpp
    main.cpp)

set(desktop_UI
    MainWindow.ui
    AlbumListWidget.ui
    AlbumWidget.ui
    PictureWidget.ui
    GalleryWidget.ui)

qt5_wrap_ui(desktop_UI_GENERATED_FILES ${desktop_UI} )
qt5_wrap_cpp(desktop_gui_MOC_SRCS ${desktop_MOC_HDRS} ) 

# WIN32 is needed to disable console poping up in GUI
# It adds linker options /SUBSYSTEM:windows /ENTRY:mainCRTStartup
add_executable(desktop WIN32
    ${desktop_HDRS}
    ${desktop_SRCS}
    ${desktop_UI}
    ${desktop_UI_GENERATED_FILES}
    ${desktop_gui_MOC_SRCS}
    resources.qrc
)

# Hack to fix errors with include of the ui*.h files
target_include_directories(desktop PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(desktop core Qt5::Widgets)

if (WIN32)
    set(desktop_PATH "PATH=%PATH%" "$ENV{Qt5_PATH}")
    set_target_properties(desktop PROPERTIES VS_DEBUGGER_ENVIRONMENT "${desktop_PATH}")
endif()
