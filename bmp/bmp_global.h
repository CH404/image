#ifndef BMP_GLOBAL_H
#define BMP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BMP_LIBRARY)
#  define BMP_EXPORT Q_DECL_EXPORT
#else
#  define BMP_EXPORT Q_DECL_IMPORT
#endif

#endif // BMP_GLOBAL_H
