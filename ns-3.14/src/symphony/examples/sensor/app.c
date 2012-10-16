#define nx_struct struct
#define nx_union union
# 150 "/usr/lib/gcc/x86_64-linux-gnu/4.6/include/stddef.h" 3
typedef long int ptrdiff_t;
#line 212
typedef long unsigned int size_t;
#line 324
typedef int wchar_t;
# 8 "/usr/lib/ncc/deputy_nodeputy.h"
struct __nesc_attr_nonnull {
#line 8
  int dummy;
}  ;
#line 9
struct __nesc_attr_bnd {
#line 9
  void *lo, *hi;
}  ;
#line 10
struct __nesc_attr_bnd_nok {
#line 10
  void *lo, *hi;
}  ;
#line 11
struct __nesc_attr_count {
#line 11
  int n;
}  ;
#line 12
struct __nesc_attr_count_nok {
#line 12
  int n;
}  ;
#line 13
struct __nesc_attr_one {
#line 13
  int dummy;
}  ;
#line 14
struct __nesc_attr_one_nok {
#line 14
  int dummy;
}  ;
#line 15
struct __nesc_attr_dmemset {
#line 15
  int a1, a2, a3;
}  ;
#line 16
struct __nesc_attr_dmemcpy {
#line 16
  int a1, a2, a3;
}  ;
#line 17
struct __nesc_attr_nts {
#line 17
  int dummy;
}  ;
# 37 "/usr/include/stdint.h" 3
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;

typedef long int int64_t;







typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;



typedef unsigned long int uint64_t;









typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;

typedef long int int_least64_t;






typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;

typedef unsigned long int uint_least64_t;









typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;








typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
#line 120
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
#line 135
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
# 35 "/usr/include/inttypes.h" 3
typedef int __gwchar_t;
#line 283
#line 279
typedef struct __nesc_unnamed4242 {

  long int quot;
  long int rem;
} imaxdiv_t;
# 431 "/usr/lib/ncc/nesc_nx.h"
typedef struct { unsigned char nxdata[1]; } __attribute__((packed)) nx_int8_t;typedef int8_t __nesc_nxbase_nx_int8_t  ;
typedef struct { unsigned char nxdata[2]; } __attribute__((packed)) nx_int16_t;typedef int16_t __nesc_nxbase_nx_int16_t  ;
typedef struct { unsigned char nxdata[4]; } __attribute__((packed)) nx_int32_t;typedef int32_t __nesc_nxbase_nx_int32_t  ;
typedef struct { unsigned char nxdata[8]; } __attribute__((packed)) nx_int64_t;typedef int64_t __nesc_nxbase_nx_int64_t  ;
typedef struct { unsigned char nxdata[1]; } __attribute__((packed)) nx_uint8_t;typedef uint8_t __nesc_nxbase_nx_uint8_t  ;
typedef struct { unsigned char nxdata[2]; } __attribute__((packed)) nx_uint16_t;typedef uint16_t __nesc_nxbase_nx_uint16_t  ;
typedef struct { unsigned char nxdata[4]; } __attribute__((packed)) nx_uint32_t;typedef uint32_t __nesc_nxbase_nx_uint32_t  ;
typedef struct { unsigned char nxdata[8]; } __attribute__((packed)) nx_uint64_t;typedef uint64_t __nesc_nxbase_nx_uint64_t  ;


typedef struct { unsigned char nxdata[1]; } __attribute__((packed)) nxle_int8_t;typedef int8_t __nesc_nxbase_nxle_int8_t  ;
typedef struct { unsigned char nxdata[2]; } __attribute__((packed)) nxle_int16_t;typedef int16_t __nesc_nxbase_nxle_int16_t  ;
typedef struct { unsigned char nxdata[4]; } __attribute__((packed)) nxle_int32_t;typedef int32_t __nesc_nxbase_nxle_int32_t  ;
typedef struct { unsigned char nxdata[8]; } __attribute__((packed)) nxle_int64_t;typedef int64_t __nesc_nxbase_nxle_int64_t  ;
typedef struct { unsigned char nxdata[1]; } __attribute__((packed)) nxle_uint8_t;typedef uint8_t __nesc_nxbase_nxle_uint8_t  ;
typedef struct { unsigned char nxdata[2]; } __attribute__((packed)) nxle_uint16_t;typedef uint16_t __nesc_nxbase_nxle_uint16_t  ;
typedef struct { unsigned char nxdata[4]; } __attribute__((packed)) nxle_uint32_t;typedef uint32_t __nesc_nxbase_nxle_uint32_t  ;
typedef struct { unsigned char nxdata[8]; } __attribute__((packed)) nxle_uint64_t;typedef uint64_t __nesc_nxbase_nxle_uint64_t  ;
# 65 "/usr/include/string.h" 3
extern void *memset(void *__s, int __c, size_t __n) __attribute((__leaf__)) __attribute((__nothrow__)) __attribute((__nonnull__(1))) ;
# 40 "/usr/include/xlocale.h" 3
#line 28
typedef struct __locale_struct {


  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;
# 67 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 3
union wait {

  int w_status;
  struct __nesc_unnamed4243 {


    unsigned int __w_termsig : 7;
    unsigned int __w_coredump : 1;
    unsigned int __w_retcode : 8;
    unsigned int  : 16;
  } 






  __wait_terminated;
  struct __nesc_unnamed4244 {


    unsigned int __w_stopval : 8;
    unsigned int __w_stopsig : 8;
    unsigned int  : 16;
  } 





  __wait_stopped;
};
# 72 "/usr/include/stdlib.h" 3
#line 68
typedef union __nesc_unnamed4245 {

  union wait *__uptr;
  int *__iptr;
} __WAIT_STATUS __attribute((__transparent_union__)) ;
#line 102
#line 98
typedef struct __nesc_unnamed4246 {

  int quot;
  int rem;
} div_t;







#line 106
typedef struct __nesc_unnamed4247 {

  long int quot;
  long int rem;
} ldiv_t;







__extension__ 



#line 118
typedef struct __nesc_unnamed4248 {

  long long int quot;
  long long int rem;
} lldiv_t;
#line 158
__extension__ 
#line 195
__extension__ 




__extension__ 








__extension__ 




__extension__ 
# 31 "/usr/include/x86_64-linux-gnu/bits/types.h" 3
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
#line 134
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct __nesc_unnamed4249 {
#line 144
  int __val[2];
} 
#line 144
__fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef long int __swblk_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void *__timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

typedef long int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;
# 34 "/usr/include/x86_64-linux-gnu/sys/types.h" 3
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
#line 61
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
#line 99
typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 60 "/usr/include/time.h" 3
typedef __clock_t clock_t;
#line 76
typedef __time_t time_t;
#line 92
typedef __clockid_t clockid_t;
#line 104
typedef __timer_t timer_t;
# 151 "/usr/include/x86_64-linux-gnu/sys/types.h" 3
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
#line 201
typedef unsigned int u_int8_t __attribute((__mode__(__QI__))) ;
typedef unsigned int u_int16_t __attribute((__mode__(__HI__))) ;
typedef unsigned int u_int32_t __attribute((__mode__(__SI__))) ;
typedef unsigned int u_int64_t __attribute((__mode__(__DI__))) ;

typedef int register_t __attribute((__mode__(__word__))) ;
# 24 "/usr/include/x86_64-linux-gnu/bits/sigset.h" 3
typedef int __sig_atomic_t;







#line 29
typedef struct __nesc_unnamed4250 {

  unsigned long int __val[1024 / (8 * sizeof(unsigned long int ))];
} __sigset_t;
# 38 "/usr/include/x86_64-linux-gnu/sys/select.h" 3
typedef __sigset_t sigset_t;
# 120 "/usr/include/time.h" 3
struct timespec {

  __time_t tv_sec;
  long int tv_nsec;
};
# 31 "/usr/include/x86_64-linux-gnu/bits/time.h" 3
struct timeval {

  __time_t tv_sec;
  __suseconds_t tv_usec;
};
# 49 "/usr/include/x86_64-linux-gnu/sys/select.h" 3
typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
#line 76
#line 65
typedef struct __nesc_unnamed4251 {







  __fd_mask __fds_bits[1024 / (8 * (int )sizeof(__fd_mask ))];
} 

fd_set;






typedef __fd_mask fd_mask;
# 32 "/usr/include/x86_64-linux-gnu/sys/sysmacros.h" 3
__extension__ 


__extension__ 


__extension__ 
# 229 "/usr/include/x86_64-linux-gnu/sys/types.h" 3
typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 50 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3
typedef unsigned long int pthread_t;






#line 53
typedef union __nesc_unnamed4252 {

  char __size[56];
  long int __align;
} pthread_attr_t;







#line 61
typedef struct __pthread_internal_list {

  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
#line 104
#line 76
typedef union __nesc_unnamed4253 {

  struct __pthread_mutex_s {

    int __lock;
    unsigned int __count;
    int __owner;

    unsigned int __nusers;



    int __kind;

    int __spins;
    __pthread_list_t __list;
  } 








  __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;





#line 106
typedef union __nesc_unnamed4254 {

  char __size[4];
  int __align;
} pthread_mutexattr_t;
#line 130
#line 115
typedef union __nesc_unnamed4255 {

  struct __nesc_unnamed4256 {

    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;





#line 132
typedef union __nesc_unnamed4257 {

  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;
#line 189
#line 150
typedef union __nesc_unnamed4258 {


  struct __nesc_unnamed4259 {

    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;


    unsigned int __flags;
  } __data;
#line 187
  char __size[56];
  long int __align;
} pthread_rwlock_t;





#line 191
typedef union __nesc_unnamed4260 {

  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;








#line 206
typedef union __nesc_unnamed4261 {

  char __size[32];
  long int __align;
} pthread_barrier_t;





#line 212
typedef union __nesc_unnamed4262 {

  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 349 "/usr/include/stdlib.h" 3
struct random_data {

  int32_t *fptr;
  int32_t *rptr;
  int32_t *state;
  int rand_type;
  int rand_deg;
  int rand_sep;
  int32_t *end_ptr;
};
#line 418
struct drand48_data {

  unsigned short int __x[3];
  unsigned short int __old_x[3];
  unsigned short int __c;
  unsigned short int __init;
  unsigned long long int __a;
};
#line 742
typedef int (*__compar_fn_t)(const void *arg_0x2ba5039c61f0, const void *arg_0x2ba5039c64c8);
#line 776
__extension__ 
#line 793
__extension__ 
# 31 "/usr/include/x86_64-linux-gnu/bits/mathdef.h" 3
typedef float float_t;
typedef double double_t;
# 203 "/usr/include/math.h" 3
enum __nesc_unnamed4263 {

  FP_NAN, 

  FP_INFINITE, 

  FP_ZERO, 

  FP_SUBNORMAL, 

  FP_NORMAL
};
#line 303
#line 296
typedef enum __nesc_unnamed4264 {

  _IEEE_ = -1, 
  _SVID_, 
  _XOPEN_, 
  _POSIX_, 
  _ISOC_
} _LIB_VERSION_TYPE;
#line 321
struct exception {


  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
};
# 48 "/usr/include/ctype.h" 3
enum __nesc_unnamed4265 {

  _ISupper = 0 < 8 ? (1 << 0) << 8 : (1 << 0) >> 8, 
  _ISlower = 1 < 8 ? (1 << 1) << 8 : (1 << 1) >> 8, 
  _ISalpha = 2 < 8 ? (1 << 2) << 8 : (1 << 2) >> 8, 
  _ISdigit = 3 < 8 ? (1 << 3) << 8 : (1 << 3) >> 8, 
  _ISxdigit = 4 < 8 ? (1 << 4) << 8 : (1 << 4) >> 8, 
  _ISspace = 5 < 8 ? (1 << 5) << 8 : (1 << 5) >> 8, 
  _ISprint = 6 < 8 ? (1 << 6) << 8 : (1 << 6) >> 8, 
  _ISgraph = 7 < 8 ? (1 << 7) << 8 : (1 << 7) >> 8, 
  _ISblank = 8 < 8 ? (1 << 8) << 8 : (1 << 8) >> 8, 
  _IScntrl = 9 < 8 ? (1 << 9) << 8 : (1 << 9) >> 8, 
  _ISpunct = 10 < 8 ? (1 << 10) << 8 : (1 << 10) >> 8, 
  _ISalnum = 11 < 8 ? (1 << 11) << 8 : (1 << 11) >> 8
};
# 23 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/system/tos.h"
typedef uint8_t bool;
enum __nesc_unnamed4266 {
#line 24
  FALSE = 0, TRUE = 1
};
typedef nx_int8_t nx_bool;
uint16_t TOS_NODE_ID = 1;






struct __nesc_attr_atmostonce {
};
#line 35
struct __nesc_attr_atleastonce {
};
#line 36
struct __nesc_attr_exactlyonce {
};
# 51 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/types/TinyError.h"
enum __nesc_unnamed4267 {
  SUCCESS = 0, 
  FAIL = 1, 
  ESIZE = 2, 
  ECANCEL = 3, 
  EOFF = 4, 
  EBUSY = 5, 
  EINVAL = 6, 
  ERETRY = 7, 
  ERESERVE = 8, 
  EALREADY = 9, 
  ENOMEM = 10, 
  ENOACK = 11, 
  ELAST = 11
};

typedef uint8_t error_t  ;

static inline error_t ecombine(error_t r1, error_t r2)  ;
# 4 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/hardware.h"
static __inline void __nesc_enable_interrupt();
static __inline void __nesc_disable_interrupt();

typedef uint8_t __nesc_atomic_t;
typedef uint8_t mcu_power_t;

__inline __nesc_atomic_t __nesc_atomic_start(void )  ;



__inline void __nesc_atomic_end(__nesc_atomic_t x)  ;



typedef struct { unsigned char nxdata[4]; } __attribute__((packed)) nx_float;typedef float __nesc_nxbase_nx_float  ;
#line 34
enum __nesc_unnamed4268 {
  TOS_SLEEP_NONE = 0
};
# 45 "/usr/include/stdio.h" 3
struct _IO_FILE;



typedef struct _IO_FILE FILE;
#line 65
typedef struct _IO_FILE __FILE;
# 95 "/usr/include/wchar.h" 3
#line 83
typedef struct __nesc_unnamed4269 {

  int __count;
  union __nesc_unnamed4270 {


    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
# 26 "/usr/include/_G_config.h" 3
#line 22
typedef struct __nesc_unnamed4271 {

  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;




#line 27
typedef struct __nesc_unnamed4272 {

  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
#line 53
typedef int _G_int16_t __attribute((__mode__(__HI__))) ;
typedef int _G_int32_t __attribute((__mode__(__SI__))) ;
typedef unsigned int _G_uint16_t __attribute((__mode__(__HI__))) ;
typedef unsigned int _G_uint32_t __attribute((__mode__(__SI__))) ;
# 40 "/usr/lib/gcc/x86_64-linux-gnu/4.6/include/stdarg.h" 3
typedef __builtin_va_list __gnuc_va_list;
# 172 "/usr/include/libio.h" 3
struct _IO_jump_t;
#line 172
struct _IO_FILE;









typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
};
#line 208
enum __codecvt_result {

  __codecvt_ok, 
  __codecvt_partial, 
  __codecvt_error, 
  __codecvt_noconv
};
#line 273
struct _IO_FILE {
  int _flags;




  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;








  __off64_t _offset;








  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;

  int _mode;

  char _unused2[15 * sizeof(int ) - 4 * sizeof(void *) - sizeof(size_t )];
};



typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

struct _IO_FILE_plus;
struct _IO_FILE_plus;
struct _IO_FILE_plus;
#line 366
typedef __ssize_t __io_read_fn(void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn(void *__cookie, const char *__buf, 
size_t __n);







typedef int __io_seek_fn(void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn(void *__cookie);
# 80 "/usr/include/stdio.h" 3
typedef __gnuc_va_list va_list;
#line 111
typedef _G_fpos_t fpos_t;
#line 169
struct _IO_FILE;
extern struct _IO_FILE *stdout;
struct _IO_FILE;
#line 243
extern int fflush(FILE *__stream);
#line 363
extern int printf(const char *__restrict __format, ...);
# 23 "/home/lauril/dev/symphony/ns-3.14/build/ns3/calls-to-ns3.h"
#line 12
typedef enum __nesc_unnamed4273 {
  RADIO_ON = 0, 
  RADIO_START = 1, 
  RADIO_SLEEP = 2, 
  RADIO_STOP = 3, 
  RADIO_SET_CHANNEL = 4, 
  RADIO_GET_CHANNEL = 5, 
  RADIO_SET_TX_POWER = 6, 
  RADIO_GET_TX_POWER = 7, 
  RADIO_SEND = 8, 
  RADIO_CANCEL = 9
} DeviceCall;








#line 25
typedef enum __nesc_unnamed4274 {
  RADIO_STATE_ON, 
  RADIO_STATE_STANDBY, 
  RADIO_STATE_OFF, 
  RADIO_STATE_SWITCHING_CHANNEL, 
  RADIO_STATE_TX, 
  RADIO_STATE_RX
} RadioState;






#line 34
typedef enum __nesc_unnamed4275 {
  SENSOR_ON = 0, 
  SENSOR_OFF = 1, 
  SENSOR_GET_DATA = 2, 
  SENSOR_RESET = 3
} SensorCall;
# 65 "/home/lauril/dev/symphony/ns-3.14/build/ns3/tos-to-ns3-proxy.h"
int gateway(void *obj, int func, int arg);
int setProxy(void *obj);


int gatewaySensor(void *obj, SensorCall call);
# 6 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/sim_main.h"
int a;
int id_this_lib;
void *proxy;





int setUniqueID(int i)   ;





int setProxy(void *con)   ;
# 43 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/types/Leds.h"
enum __nesc_unnamed4276 {
  LEDS_LED0 = 1 << 0, 
  LEDS_LED1 = 1 << 1, 
  LEDS_LED2 = 1 << 2, 
  LEDS_LED3 = 1 << 3, 
  LEDS_LED4 = 1 << 4, 
  LEDS_LED5 = 1 << 5, 
  LEDS_LED6 = 1 << 6, 
  LEDS_LED7 = 1 << 7
};
# 44 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/logprinter.h"
#line 17
typedef enum LogLevel {
  LOG_NONE = 0x00000000, 

  LOG_ERROR = 0x00000001, 
  LOG_LEVEL_ERROR = 0x00000001, 

  LOG_WARN = 0x00000002, 
  LOG_LEVEL_WARN = 0x00000003, 

  LOG_DEBUG = 0x00000004, 
  LOG_LEVEL_DEBUG = 0x00000007, 

  LOG_INFO = 0x00000008, 
  LOG_LEVEL_INFO = 0x0000000f, 

  LOG_FUNCTION = 0x00000010, 
  LOG_LEVEL_FUNCTION = 0x0000001f, 

  LOG_LOGIC = 0x00000020, 
  LOG_LEVEL_LOGIC = 0x0000003f, 

  LOG_ALL = 0x1fffffff, 
  LOG_LEVEL_ALL = LOG_ALL, 

  LOG_PREFIX_FUNC = 0x80000000, 
  LOG_PREFIX_TIME = 0x40000000, 
  LOG_PREFIX_NODE = 0x20000000
} LogLevel;
# 40 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.h"
typedef struct __nesc_unnamed4277 {
#line 40
  int notUsed;
} 
#line 40
TMilli;
typedef struct __nesc_unnamed4278 {
#line 41
  int notUsed;
} 
#line 41
T32khz;
typedef struct __nesc_unnamed4279 {
#line 42
  int notUsed;
} 
#line 42
TMicro;
typedef TMilli NsTimerP$Timer$precision_tag;
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t PlatformP$Init$init(void );
#line 62
static error_t LedsP$Init$init(void );
#line 62
static error_t NsTimerP$Init$init(void );
# 83 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static void NsTimerP$Timer$default$fired(void );
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t SimMainP$SoftwareInit$default$init(void );
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void SchedulerBasicP$TaskBasic$default$runTask(
# 47 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
uint8_t arg_0x2ba503c90cb0);
# 57 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Scheduler.nc"
static void SchedulerBasicP$Scheduler$init(void );







static bool SchedulerBasicP$Scheduler$runNextTask(void );
# 36 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMote.nc"
static void SimMoteP$SimMote$setEuid(long long int euid);



static void SimMoteP$SimMote$turnOn(void );
# 113 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
static void SensorAppC$SensorControl$startDone(error_t error);
#line 138
static void SensorAppC$SensorControl$stopDone(error_t error);
# 60 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Boot.nc"
static void SensorAppC$Boot$booted(void );
# 22 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sensors/InterruptWithData.nc"
static void SensorAppC$DataIn$interruptWithData(error_t result, uint16_t length, void *buffer);
# 104 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
static error_t MagnetomiterP$SplitControl$start(void );
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t PlatformP$SubInit$init(void );
#line 62
static error_t PlatformP$TimerInit$init(void );
# 56 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/PlatformP.nc"
static inline error_t PlatformP$Init$init(void );
# 68 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/system/LedsP.nc"
static inline error_t LedsP$Init$init(void );
# 83 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static void NsTimerP$Timer$fired(void );
# 20 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
uint32_t NsTimerP$time_now = 0;








#line 21
typedef struct NsTimerP$__nesc_unnamed4280 {

  uint32_t t0;
  uint32_t dt;
  uint32_t shoot;
  bool isoneshot : 1;
  bool isrunning : 1;
  bool _reserved : 6;
} NsTimerP$Timer_t;

NsTimerP$Timer_t NsTimerP$m_timer;

static inline void NsTimerP$updateTimer(void );








extern int tickFired(uint32_t a)   ;
#line 133
static inline error_t NsTimerP$Init$init(void );




static inline void NsTimerP$Timer$default$fired(void );
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t SimMainP$SoftwareInit$init(void );
# 60 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Boot.nc"
static void SimMainP$Boot$booted(void );
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t SimMainP$PlatformInit$init(void );
# 57 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Scheduler.nc"
static void SimMainP$Scheduler$init(void );
# 17 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMainP.nc"
int sim_main_start_mote(int id)   ;
#line 64
static inline error_t SimMainP$SoftwareInit$default$init(void );
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void SchedulerBasicP$TaskBasic$runTask(
# 47 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
uint8_t arg_0x2ba503c90cb0);




extern int runNextEventExternal(uint32_t a)   ;




enum SchedulerBasicP$__nesc_unnamed4281 {

  SchedulerBasicP$NUM_TASKS = 0U, 
  SchedulerBasicP$NO_TASK = 255
};

uint8_t SchedulerBasicP$m_head;
uint8_t SchedulerBasicP$m_tail;
uint8_t SchedulerBasicP$m_next[SchedulerBasicP$NUM_TASKS];








static __inline uint8_t SchedulerBasicP$popTask(void );
#line 120
static inline void SchedulerBasicP$Scheduler$init(void );
#line 132
static inline bool SchedulerBasicP$Scheduler$runNextTask(void );
#line 175
static inline void SchedulerBasicP$TaskBasic$default$runTask(uint8_t id);
# 8 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMoteP.nc"
long long int SimMoteP$euid;

bool SimMoteP$isOn;





static inline void SimMoteP$SimMote$setEuid(long long int e);
#line 30
static inline void SimMoteP$SimMote$turnOn(void );
#line 50
long long int sim_mote_euid(int mote)   ;








void sim_mote_set_euid(int mote, long long int id)   ;






long long int sim_mote_start_time(int mote)   ;








int sim_mote_get_variable_info(int mote, char *name, void **ptr, size_t *len)   ;









void sim_mote_set_start_time(int mote, long long int t)   ;








bool sim_mote_is_on(int mote)   ;








void sim_mote_turn_on(int mote)   ;







void sim_mote_turn_off(int mote)   ;
#line 127
void sim_mote_enqueue_boot_event(int mote)   ;
# 104 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
static error_t SensorAppC$SensorControl$start(void );
# 11 "SensorAppC.nc"
static inline void SensorAppC$Boot$booted(void );




static inline void SensorAppC$SensorControl$startDone(error_t err);








static inline void SensorAppC$SensorControl$stopDone(error_t err);





static inline void SensorAppC$DataIn$interruptWithData(error_t result, uint16_t length, void *buffer);
# 113 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
static void MagnetomiterP$SplitControl$startDone(error_t error);
#line 138
static void MagnetomiterP$SplitControl$stopDone(error_t error);
# 22 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sensors/InterruptWithData.nc"
static void MagnetomiterP$data$interruptWithData(error_t result, uint16_t length, void *buffer);
# 17 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sensors/MagnetomiterP.nc"
static inline error_t MagnetomiterP$SplitControl$start(void );




extern int sensorStartDone(error_t error)   ;








extern int sensorStopDone(error_t error)   ;




extern void interruptData(error_t result, uint16_t lenght, void *buffer)   ;
# 10 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/hardware.h"
__inline  __nesc_atomic_t __nesc_atomic_start(void )
#line 10
{
  return 0;
}

__inline  void __nesc_atomic_end(__nesc_atomic_t x)
#line 14
{
}

# 175 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
static inline void SchedulerBasicP$TaskBasic$default$runTask(uint8_t id)
{
}

# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
inline static void SchedulerBasicP$TaskBasic$runTask(uint8_t arg_0x2ba503c90cb0){
#line 75
    SchedulerBasicP$TaskBasic$default$runTask(arg_0x2ba503c90cb0);
#line 75
}
#line 75
# 74 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
static __inline uint8_t SchedulerBasicP$popTask(void )
{
  if (SchedulerBasicP$m_head != SchedulerBasicP$NO_TASK) 
    {
      uint8_t id = SchedulerBasicP$m_head;

#line 79
      SchedulerBasicP$m_head = SchedulerBasicP$m_next[SchedulerBasicP$m_head];
      if (SchedulerBasicP$m_head == SchedulerBasicP$NO_TASK) 
        {
          SchedulerBasicP$m_tail = SchedulerBasicP$NO_TASK;
        }
      SchedulerBasicP$m_next[id] = SchedulerBasicP$NO_TASK;
      return id;
    }
  else 
    {
      return SchedulerBasicP$NO_TASK;
    }
}

#line 132
static inline bool SchedulerBasicP$Scheduler$runNextTask(void )
{

  uint8_t nextTask;

#line 136
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {
      nextTask = SchedulerBasicP$popTask();
      if (nextTask == SchedulerBasicP$NO_TASK) 
        {
          {
            unsigned char __nesc_temp = 
#line 141
            TRUE;

            {
#line 141
              __nesc_atomic_end(__nesc_atomic); 
#line 141
              return __nesc_temp;
            }
          }
        }
    }
#line 145
    __nesc_atomic_end(__nesc_atomic); }
#line 144
  SchedulerBasicP$TaskBasic$runTask(nextTask);
  return TRUE;
}

# 138 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
static inline void NsTimerP$Timer$default$fired(void )
#line 138
{
}

# 83 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
inline static void NsTimerP$Timer$fired(void ){
#line 83
  NsTimerP$Timer$default$fired();
#line 83
}
#line 83
# 33 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
static inline void NsTimerP$updateTimer(void )
#line 33
{

  if (NsTimerP$m_timer.shoot == NsTimerP$time_now) {

      NsTimerP$Timer$fired();
    }
}

# 120 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
static inline void SchedulerBasicP$Scheduler$init(void )
{
  printf("Scheduler.init()\n");
  /* atomic removed: atomic calls only */

  {
    memset((void *)SchedulerBasicP$m_next, SchedulerBasicP$NO_TASK, sizeof SchedulerBasicP$m_next);
    SchedulerBasicP$m_head = SchedulerBasicP$NO_TASK;
    SchedulerBasicP$m_tail = SchedulerBasicP$NO_TASK;
  }
}

# 57 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Scheduler.nc"
inline static void SimMainP$Scheduler$init(void ){
#line 57
  SchedulerBasicP$Scheduler$init();
#line 57
}
#line 57
# 133 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
static inline error_t NsTimerP$Init$init(void )
#line 133
{
  /* atomic removed: atomic calls only */
#line 134
  NsTimerP$time_now = 0;
  return 0;
}

# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
inline static error_t PlatformP$TimerInit$init(void ){
#line 62
  unsigned char __nesc_result;
#line 62

#line 62
  __nesc_result = NsTimerP$Init$init();
#line 62

#line 62
  return __nesc_result;
#line 62
}
#line 62
# 68 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/system/LedsP.nc"
static inline error_t LedsP$Init$init(void )
#line 68
{

  return SUCCESS;
}

# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
inline static error_t PlatformP$SubInit$init(void ){
#line 62
  unsigned char __nesc_result;
#line 62

#line 62
  __nesc_result = LedsP$Init$init();
#line 62

#line 62
  return __nesc_result;
#line 62
}
#line 62
# 69 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/types/TinyError.h"
static inline  error_t ecombine(error_t r1, error_t r2)




{
  return r1 == r2 ? r1 : FAIL;
}

# 56 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/PlatformP.nc"
static inline error_t PlatformP$Init$init(void )
{
  error_t ok = SUCCESS;

  ok = ecombine(ok, PlatformP$SubInit$init());
  PlatformP$TimerInit$init();
  return SUCCESS;
}

# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
inline static error_t SimMainP$PlatformInit$init(void ){
#line 62
  unsigned char __nesc_result;
#line 62

#line 62
  __nesc_result = PlatformP$Init$init();
#line 62

#line 62
  return __nesc_result;
#line 62
}
#line 62
# 64 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMainP.nc"
static inline error_t SimMainP$SoftwareInit$default$init(void )
#line 64
{
#line 64
  return SUCCESS;
}

# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
inline static error_t SimMainP$SoftwareInit$init(void ){
#line 62
  unsigned char __nesc_result;
#line 62

#line 62
  __nesc_result = SimMainP$SoftwareInit$default$init();
#line 62

#line 62
  return __nesc_result;
#line 62
}
#line 62
# 17 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sensors/MagnetomiterP.nc"
static inline error_t MagnetomiterP$SplitControl$start(void )
#line 17
{

  return gatewaySensor(proxy, SENSOR_ON);
}

# 104 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
inline static error_t SensorAppC$SensorControl$start(void ){
#line 104
  unsigned char __nesc_result;
#line 104

#line 104
  __nesc_result = MagnetomiterP$SplitControl$start();
#line 104

#line 104
  return __nesc_result;
#line 104
}
#line 104
# 11 "SensorAppC.nc"
static inline void SensorAppC$Boot$booted(void )
#line 11
{
  printf("App: booted %d\n", TOS_NODE_ID);
  SensorAppC$SensorControl$start();
}

# 60 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Boot.nc"
inline static void SimMainP$Boot$booted(void ){
#line 60
  SensorAppC$Boot$booted();
#line 60
}
#line 60
# 16 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMoteP.nc"
static inline void SimMoteP$SimMote$setEuid(long long int e)
#line 16
{
  SimMoteP$euid = e;
}











static inline void SimMoteP$SimMote$turnOn(void )
#line 30
{
  SimMoteP$isOn = TRUE;
}

# 16 "SensorAppC.nc"
static inline void SensorAppC$SensorControl$startDone(error_t err)
#line 16
{
  if (err == SUCCESS) {
      printf("SensorControl.startDone: TOS_NODE_ID == %d\n", TOS_NODE_ID);
      fflush(stdout);
    }
  else 
#line 20
    {
      SensorAppC$SensorControl$start();
    }
}

# 113 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
inline static void MagnetomiterP$SplitControl$startDone(error_t error){
#line 113
  SensorAppC$SensorControl$startDone(error);
#line 113
}
#line 113
# 25 "SensorAppC.nc"
static inline void SensorAppC$SensorControl$stopDone(error_t err)
#line 25
{
}

# 138 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
inline static void MagnetomiterP$SplitControl$stopDone(error_t error){
#line 138
  SensorAppC$SensorControl$stopDone(error);
#line 138
}
#line 138
# 31 "SensorAppC.nc"
static inline void SensorAppC$DataIn$interruptWithData(error_t result, uint16_t length, void *buffer)
#line 31
{
  printf("event void InterruptWithData.interruptWithData NODE_ID %d - data lenght %d\n", TOS_NODE_ID, length);
}

# 22 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sensors/InterruptWithData.nc"
inline static void MagnetomiterP$data$interruptWithData(error_t result, uint16_t length, void *buffer){
#line 22
  SensorAppC$DataIn$interruptWithData(result, length, buffer);
#line 22
}
#line 22
# 4 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/hardware.h"
static __inline void __nesc_enable_interrupt()
#line 4
{
}

#line 5
static __inline void __nesc_disable_interrupt()
#line 5
{
}

# 14 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/sim_main.h"
  int setUniqueID(int i)
#line 14
{
  TOS_NODE_ID = i;
  id_this_lib = i;
  return id_this_lib;
}

  int setProxy(void *con)
#line 20
{
  proxy = con;
  if (proxy != (void *)0) {
      a = gateway(proxy, 0, id_this_lib);
      printf("\tFROM toslib: gateway(proxy,0,id_this_lib): %i\n", a);
    }
  else {
      printf("FROM toslib: ops! no proxy\n");
    }
  return id_this_lib;
}

# 52 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
extern   int runNextEventExternal(uint32_t a)
#line 52
{

  SchedulerBasicP$Scheduler$runNextTask();
  return 0;
}

# 42 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
extern   int tickFired(uint32_t a)
#line 42
{

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 44
    NsTimerP$time_now = a;
#line 44
    __nesc_atomic_end(__nesc_atomic); }
  NsTimerP$updateTimer();
  runNextEventExternal(0);

  NsTimerP$Timer$fired();
  return 0;
}

# 17 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMainP.nc"
  int sim_main_start_mote(int id)
#line 17
{



  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 21
    {






      SimMainP$Scheduler$init();





      SimMainP$PlatformInit$init();






      SimMainP$SoftwareInit$init();

      TOS_NODE_ID = id;
    }
#line 44
    __nesc_atomic_end(__nesc_atomic); }







  SimMainP$Boot$booted();







  return 0;
}

# 50 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMoteP.nc"
  long long int sim_mote_euid(int mote)
#line 50
{





  return 3;
}

  void sim_mote_set_euid(int mote, long long int id)
#line 59
{


  SimMoteP$SimMote$setEuid(id);
}


  long long int sim_mote_start_time(int mote)
#line 66
{





  return 2;
}

  int sim_mote_get_variable_info(int mote, char *name, void **ptr, size_t *len)
#line 75
{
  int result = 0;





  return result;
}

  void sim_mote_set_start_time(int mote, long long int t)
#line 85
{
}







  bool sim_mote_is_on(int mote)
#line 94
{





  return SimMoteP$isOn;
}

  void sim_mote_turn_on(int mote)
#line 103
{
  printf("sim_main_start_mote\n");


  SimMoteP$SimMote$turnOn();
}


  void sim_mote_turn_off(int mote)
#line 111
{
}

#line 127
  void sim_mote_enqueue_boot_event(int mote)
#line 127
{
}

# 22 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sensors/MagnetomiterP.nc"
extern   int sensorStartDone(error_t error)
#line 22
{
  MagnetomiterP$SplitControl$startDone(error);
  return 0;
}





extern   int sensorStopDone(error_t error)
#line 31
{
  MagnetomiterP$SplitControl$stopDone(error);
  return 0;
}

extern   void interruptData(error_t result, uint16_t lenght, void *buffer)
#line 36
{
  MagnetomiterP$data$interruptWithData(result, lenght, buffer);
}

