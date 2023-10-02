
set(core_HDRS
    exports.h
    Album.h
    AlbumDao.h
    AlbumModel.h
    DatabaseManager.h
    Picture.h
    PictureDao.h
    PictureModel.h
)

set(core_SRC
    Album.cpp
    AlbumDao.cpp
    AlbumModel.cpp
    DatabaseManager.cpp
    Picture.cpp
    PictureDao.cpp
    PictureModel.cpp
)

# WIN32 is needed to disable console poping up in GUI
# It adds linker options /SUBSYSTEM:windows /ENTRY:mainCRTStartup
add_library(core
    ${core_HDRS}
    ${core_SRC}
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_definitions(core PUBLIC GALLERY_CORE_LIBRARY)
target_link_libraries(core Qt5::Sql)

# if (WIN32)
#     set_target_properties(core PROPERTIES VS_DEBUGGER_ENVIRONMENT "${gallery_PATH}")
# endif()