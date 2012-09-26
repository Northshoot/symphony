#ifndef __LOG_PRINTER__
#define __LOG_PRINTER__
#include "sim_main.h"
#include "ns3/tos-to-ns3-proxy.h"

//fallback
#if __STDC_VERSION__ < 199901L
	# if __GNUC__ >= 2
	   #  define __func__ __FUNCTION__
	# else
	   #  define __func__ "<unknown>"
	# endif
#endif
//borrowed from NS3
//TODO: would be best to reuse existing code

typedef enum LogLevel {
  LOG_NONE           = 0x00000000, // no logging

  LOG_ERROR          = 0x00000001, // serious error messages only
  LOG_LEVEL_ERROR    = 0x00000001,

  LOG_WARN           = 0x00000002, // warning messages
  LOG_LEVEL_WARN     = 0x00000003,

  LOG_DEBUG          = 0x00000004, // rare ad-hoc debug messages
  LOG_LEVEL_DEBUG    = 0x00000007,

  LOG_INFO           = 0x00000008, // informational messages (e.g., banners)
  LOG_LEVEL_INFO     = 0x0000000f,

  LOG_FUNCTION       = 0x00000010, // function tracing
  LOG_LEVEL_FUNCTION = 0x0000001f, 

  LOG_LOGIC          = 0x00000020, // control flow tracing within functions
  LOG_LEVEL_LOGIC    = 0x0000003f,

  LOG_ALL            = 0x1fffffff, // print everything
  LOG_LEVEL_ALL      = LOG_ALL,

  LOG_PREFIX_FUNC    = 0x80000000, // prefix all trace prints with function
  LOG_PREFIX_TIME    = 0x40000000, // prefix all trace prints with simulation time
  LOG_PREFIX_NODE    = 0x20000000  // prefix all trace prints with simulation node
}LogLevel;


#define DBVIRTGLED( n,msg) \
    gatewayLogg(proxy,__func__, __LINE__, msg)
    
//#define DBVIRTGLED(func, n,msg) 
  //gatewayLogg(proxy, func,n,#msg)
  
//void logPasser( const char* func, int val,const char* msg){
//	gatewayLogg(proxy, func, val, msg);
//}

#endif //__LOG_PRINTER__