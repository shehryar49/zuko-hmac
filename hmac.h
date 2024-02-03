#ifdef _WIN32
  #include "C:\\zuko\\include\\zapi.h"
  #define EXPORT __declspec(dllexport)
#else
  #include "/opt/zuko/include/zapi.h"
  #define EXPORT
#endif

extern "C"
{
  EXPORT ZObject init();
  
  EXPORT ZObject SIGN(ZObject*,int32_t);
}
