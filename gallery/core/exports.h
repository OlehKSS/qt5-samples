#pragma once
#include <QtCore/qglobal.h>

#if defined(GALLERY_CORE_LIBRARY)
#define GALLERY_CORE_SHARED_EXPORT Q_DECL_EXPORT
#else
#define GALLERY_CORE_SHARED_EXPORT Q_DECL_IMPORT
#endif