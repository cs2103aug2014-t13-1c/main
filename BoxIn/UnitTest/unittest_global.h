#ifndef UNITTEST_GLOBAL_H
#define UNITTEST_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef UNITTEST_LIB
# define UNITTEST_EXPORT Q_DECL_EXPORT
#else
# define UNITTEST_EXPORT Q_DECL_IMPORT
#endif

#endif // UNITTEST_GLOBAL_H
