# XF Port - IDF Qt

This port folder contains specific classes for the _IDF Qt_
XF port.

# Classes used by the _IDF Qt_ Port

| Class name | File location | Define to set |
|--|--|--|
| XFTimeoutManagerDefault | xf/port/default/timeoutmanager-default.cpp | USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION |
| XFDispatcherActiveDefault | xf/port/default/dispatcher-active.cpp | USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION |
| XF | xf/port/idf-qt/xf.cpp | USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION |
| XFResourceFactoryPort | xf/port/idf-qt/resourcefactory.cpp | USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION |
| XFMutexPort | xf/port/idf-qt/mutex.cpp | USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION |
| XFThreadPort | xf/port/idf-qt/thread.cpp | USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION |
| XFEventQueuePort | xf/port/idf-qt/eventqueue.cpp | USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION |
| Port Functions | xf/port/idf-qt/port-functions.cpp | USE_XF_PORT_IDF_QT_PORT_FUNCTIONS_IMPLEMENTATION |

# Example _config/xf-config.h_ File

```c++
#define USE_XF_DEFAULT_IMPLEMENTATION                       0
#define USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION      0
#define USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION        1
#define USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION            0
#define USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION     1

#define USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION                1
#define USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION  1
#define USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION             1
#define USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION            1
#define USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION       1
#define USE_XF_PORT_IDF_QT_PORT_FUNCTIONS_IMPLEMENTATION    1

#include "idf-qt/eventqueue.h"
```