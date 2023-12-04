#ifndef MYLOGIN_GLOBAL_H
#define MYLOGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYLOGIN_LIBRARY)
#define MYLOGIN_EXPORT Q_DECL_EXPORT
#else
#define MYLOGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // MYLOGIN_GLOBAL_H
