#ifdef __cplusplus
 		 extern "C" { 
 		 #endif 
#define nx_struct struct
#define nx_union union
# 149 "/usr/lib/x86_64-linux-gnu/gcc/x86_64-linux-gnu/4.5.2/include/stddef.h" 3
typedef long int ptrdiff_t;
#line 211
typedef long unsigned int size_t;
#line 323
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
# 281 "/usr/lib/ncc/nesc_nx.h"
static __inline uint8_t __nesc_ntoh_uint8(const void * source)  ;




static __inline uint8_t __nesc_hton_uint8(void * target, uint8_t value)  ;
#line 310
static __inline uint16_t __nesc_ntoh_uint16(const void * source)  ;




static __inline uint16_t __nesc_hton_uint16(void * target, uint16_t value)  ;
#line 347
static __inline uint32_t __nesc_hton_uint32(void * target, uint32_t value)  ;
#line 431
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
extern void *memset(void *__s, int __c, size_t __n) __attribute((__nothrow__)) __attribute((__nonnull__(1))) ;
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
# 67 "/usr/include/bits/waitstatus.h" 3
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
# 31 "/usr/include/bits/types.h" 3
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
# 34 "/usr/include/sys/types.h" 3
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
# 151 "/usr/include/sys/types.h" 3
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
#line 201
typedef unsigned int u_int8_t __attribute((__mode__(__QI__))) ;
typedef unsigned int u_int16_t __attribute((__mode__(__HI__))) ;
typedef unsigned int u_int32_t __attribute((__mode__(__SI__))) ;
typedef unsigned int u_int64_t __attribute((__mode__(__DI__))) ;

typedef int register_t __attribute((__mode__(__word__))) ;
# 24 "/usr/include/bits/sigset.h" 3
typedef int __sig_atomic_t;







#line 29
typedef struct __nesc_unnamed4250 {

  unsigned long int __val[1024 / (8 * sizeof(unsigned long int ))];
} __sigset_t;
# 38 "/usr/include/sys/select.h" 3
typedef __sigset_t sigset_t;
# 120 "/usr/include/time.h" 3
struct timespec {

  __time_t tv_sec;
  long int tv_nsec;
};
# 75 "/usr/include/bits/time.h" 3
struct timeval {

  __time_t tv_sec;
  __suseconds_t tv_usec;
};
# 49 "/usr/include/sys/select.h" 3
typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
#line 78
#line 67
typedef struct __nesc_unnamed4251 {







  __fd_mask __fds_bits[1024 / (8 * (int )sizeof(__fd_mask ))];
} 

fd_set;






typedef __fd_mask fd_mask;
# 30 "/usr/include/sys/sysmacros.h" 3
__extension__ 


__extension__ 


__extension__ 
# 229 "/usr/include/sys/types.h" 3
typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 50 "/usr/include/bits/pthreadtypes.h" 3
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
typedef int (*__compar_fn_t)(const void *arg_0x2b25d9c5f6b0, const void *arg_0x2b25d9c5f988);
#line 776
__extension__ 
#line 793
__extension__ 
# 31 "/usr/include/bits/mathdef.h" 3
typedef float float_t;
typedef double double_t;
# 202 "/usr/include/math.h" 3
enum __nesc_unnamed4263 {

  FP_NAN, 

  FP_INFINITE, 

  FP_ZERO, 

  FP_SUBNORMAL, 

  FP_NORMAL
};
#line 302
#line 295
typedef enum __nesc_unnamed4264 {

  _IEEE_ = -1, 
  _SVID_, 
  _XOPEN_, 
  _POSIX_, 
  _ISOC_
} _LIB_VERSION_TYPE;
#line 320
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
# 40 "/usr/lib/x86_64-linux-gnu/gcc/x86_64-linux-gnu/4.5.2/include/stdarg.h" 3
typedef __builtin_va_list __gnuc_va_list;
# 170 "/usr/include/libio.h" 3
struct _IO_jump_t;
#line 170
struct _IO_FILE;









typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
};
#line 206
enum __codecvt_result {

  __codecvt_ok, 
  __codecvt_partial, 
  __codecvt_error, 
  __codecvt_noconv
};
#line 271
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
#line 364
typedef __ssize_t __io_read_fn(void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn(void *__cookie, const char *__buf, 
size_t __n);







typedef int __io_seek_fn(void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn(void *__cookie);
# 80 "/usr/include/stdio.h" 3
typedef __gnuc_va_list va_list;
#line 111
typedef _G_fpos_t fpos_t;
#line 165
struct _IO_FILE;
struct _IO_FILE;
struct _IO_FILE;
#line 359
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





#line 41
typedef enum __nesc_unnamed4276 {
  APP_ON = 1, 
  APP_OFF = 2, 
  APP_RX = 3
} ApplicationCall;






#line 47
typedef enum __nesc_unnamed4277 {
  SECOND = 1, 
  MILLISECOND = 1000, 
  MICROSECOND = 1000000, 
  NANOSECOND = 1000000000
} PRECISION;
# 73 "/home/lauril/dev/symphony/ns-3.14/build/ns3/tos-to-ns3-proxy.h"
#line 72
uint64_t 
gateway(void *obj, int func, int arg);
int setProxy(void *obj);

int gatewayRadio(void *obj, DeviceCall call, int val1, int val2, void *hdr, void *msg);
# 6 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/sim_main.h"
int a;
int id_this_lib;
void *proxy;





int setUniqueID(int i)   ;





int setProxy(void *con)   ;
# 43 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/types/Leds.h"
enum __nesc_unnamed4278 {
  LEDS_LED0 = 1 << 0, 
  LEDS_LED1 = 1 << 1, 
  LEDS_LED2 = 1 << 2, 
  LEDS_LED3 = 1 << 3, 
  LEDS_LED4 = 1 << 4, 
  LEDS_LED5 = 1 << 5, 
  LEDS_LED6 = 1 << 6, 
  LEDS_LED7 = 1 << 7
};
# 22 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/system/../defines.h"
static inline void os_log_debug(char *string, const char *format, ...);

static inline void os_log_debug(char *string, const char *format, ...);
# 40 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.h"
typedef struct __nesc_unnamed4279 {
#line 40
  int notUsed;
} 
#line 40
TMilli;
typedef struct __nesc_unnamed4280 {
#line 41
  int notUsed;
} 
#line 41
T32khz;
typedef struct __nesc_unnamed4281 {
#line 42
  int notUsed;
} 
#line 42
TMicro;
# 11 "RadioTestC.nc"
#line 5
typedef nx_struct radio_count_msg {
  nx_uint16_t counter;
  nx_uint32_t a;
  nx_uint32_t b;
  nx_uint32_t c;
  nx_uint32_t d;
} __attribute__((packed)) radio_count_msg_t;

enum __nesc_unnamed4282 {
  AM_RADIO_COUNT_MSG = 6
};
# 6 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/types/AM.h"
typedef nx_uint8_t nx_am_id_t;
typedef nx_uint8_t nx_am_group_t;
typedef nx_uint16_t nx_am_addr_t;

typedef uint8_t am_id_t;
typedef uint8_t am_group_t;
typedef uint16_t am_addr_t;

enum __nesc_unnamed4283 {
  AM_BROADCAST_ADDR = 0xffff
};









enum __nesc_unnamed4284 {
  TOS_AM_GROUP = 0x22, 
  TOS_AM_ADDRESS = 1
};
# 14 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/radioheader.h"
#line 6
typedef struct ns3_metadata_t {

  uint8_t lqi;
  union  {

    uint8_t power;
    uint8_t rssi;
  } ;
} __attribute((__packed__))  ns3_metadata_t;
#line 29
#line 18
typedef nx_struct ns3packet_header_t {

  nx_uint8_t length;
  nx_uint8_t dsn;
  nx_am_id_t type;
  nx_uint16_t fdest;
  nx_am_group_t destpan;
  nx_am_addr_t dest;
  nx_am_addr_t src;
  nx_uint8_t padd;
} __attribute__((packed)) 
__attribute((__packed__))  ns3packet_header_t;




#line 31
typedef struct timestamp_metadata_t {

  uint32_t timestamp;
} __attribute((__packed__))  timestamp_metadata_t;




#line 36
typedef nx_struct ns3packet_footer_t {
} __attribute__((packed)) 

__attribute((__packed__))  ns3packet_footer_t;





#line 41
typedef struct flags_metadata_t {


  uint8_t flags;
} __attribute((__packed__))  flags_metadata_t;







#line 48
typedef struct ns3packet_metadata_t {

  timestamp_metadata_t timestamp;
  flags_metadata_t flags;
  ns3_metadata_t ns3;
} __attribute((__packed__))  ns3packet_metadata_t;
# 50 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/platform_message.h"
#line 47
typedef union message_header {
  ns3packet_header_t rf230;
} 
message_header_t;



#line 52
typedef union message_footer {
  ns3packet_footer_t rf230;
} message_footer_t;



#line 56
typedef union message_metadata {
  ns3packet_metadata_t rf230;
} message_metadata_t;
# 19 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/types/message.h"
#line 14
typedef nx_struct message_t {
  nx_uint8_t header[sizeof(message_header_t )];
  nx_uint8_t data[28];
  nx_uint8_t footer[sizeof(message_footer_t )];
  nx_uint8_t metadata[sizeof(message_metadata_t )];
} __attribute__((packed)) __attribute((__packed__))  message_t;
typedef TMilli NsTimerP$Timer$precision_tag;
typedef TMilli RadioTestC$MilliTimer$precision_tag;
enum AMQueueP$__nesc_unnamed4285 {
  AMQueueP$NUM_CLIENTS = 1U
};
typedef TMilli /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$precision_tag;
typedef /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$precision_tag /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$precision_tag;
typedef /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$precision_tag /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$precision_tag;
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t PlatformP$Init$init(void );
#line 62
static error_t LedsP$Init$init(void );
#line 62
static error_t NsTimerP$Init$init(void );
# 136 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static uint32_t NsTimerP$Timer$getNow(void );
#line 129
static void NsTimerP$Timer$startOneShotAt(uint32_t t0, uint32_t dt);
#line 78
static void NsTimerP$Timer$stop(void );
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static error_t SchedulerBasicP$TaskBasic$postTask(
# 47 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
uint8_t arg_0x2b25d9f0c960);
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void SchedulerBasicP$TaskBasic$default$runTask(
# 47 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
uint8_t arg_0x2b25d9f0c960);
# 57 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Scheduler.nc"
static void SchedulerBasicP$Scheduler$init(void );







static bool SchedulerBasicP$Scheduler$runNextTask(void );
# 113 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
static void RadioTestC$AMControl$startDone(error_t error);
# 60 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Boot.nc"
static void RadioTestC$Boot$booted(void );
# 110 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
static void RadioTestC$AMSend$sendDone(
#line 103
message_t * msg, 






error_t error);
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void RadioTestC$send$runTask(void );
# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
static 
#line 74
message_t * 



RadioTestC$Receive$receive(
#line 71
message_t * msg, 
void * payload, 





uint8_t len);
# 83 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static void RadioTestC$MilliTimer$fired(void );
# 80 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
static error_t /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMSend$send(am_addr_t addr, 
#line 71
message_t * msg, 








uint8_t len);
# 100 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
static void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$Send$sendDone(
#line 96
message_t * msg, 



error_t error);
# 110 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMSend$sendDone(
# 48 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
am_id_t arg_0x2b25da081d28, 
# 103 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
message_t * msg, 






error_t error);
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
static error_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$send(
# 46 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
uint8_t arg_0x2b25da082b90, 
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
message_t * msg, 







uint8_t len);
#line 100
static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$default$sendDone(
# 46 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
uint8_t arg_0x2b25da082b90, 
# 96 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
message_t * msg, 



error_t error);
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask$runTask(void );
#line 75
static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$CancelTask$runTask(void );
# 104 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
static error_t Ns3ActiveMessageC$SplitControl$start(void );
# 54 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareSend.nc"
static void Ns3ActiveMessageC$SubSend$sendDone(message_t *msg, error_t error);
# 42 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareReceive.nc"
static message_t *Ns3ActiveMessageC$SubReceive$receive(message_t *msg);
# 59 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SendNotifier.nc"
static void Ns3ActiveMessageC$SendNotifier$default$aboutToSend(
# 19 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
am_id_t arg_0x2b25da0eb7d0, 
# 59 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SendNotifier.nc"
am_addr_t dest, 
#line 57
message_t * msg);
# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Packet.nc"
static uint8_t Ns3ActiveMessageC$Packet$payloadLength(
#line 74
message_t * msg);
#line 126
static 
#line 123
void * 


Ns3ActiveMessageC$Packet$getPayload(
#line 121
message_t * msg, 




uint8_t len);
#line 106
static uint8_t Ns3ActiveMessageC$Packet$maxPayloadLength(void );
#line 94
static void Ns3ActiveMessageC$Packet$setPayloadLength(
#line 90
message_t * msg, 



uint8_t len);
# 80 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
static error_t Ns3ActiveMessageC$AMSend$send(
# 16 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
am_id_t arg_0x2b25da0cf020, 
# 80 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
am_addr_t addr, 
#line 71
message_t * msg, 








uint8_t len);
# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
static 
#line 74
message_t * 



Ns3ActiveMessageC$Snoop$default$receive(
# 18 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
am_id_t arg_0x2b25da0ecca0, 
# 71 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
message_t * msg, 
void * payload, 





uint8_t len);
# 69 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/RadioState.nc"
static void Ns3ActiveMessageC$SubState$done(void );
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void Ns3ActiveMessageC$SplitControlStartDone$runTask(void );
# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
static 
#line 74
message_t * 



Ns3ActiveMessageC$Receive$default$receive(
# 17 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
am_id_t arg_0x2b25da0ec158, 
# 71 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
message_t * msg, 
void * payload, 





uint8_t len);
# 68 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMPacket.nc"
static am_addr_t Ns3ActiveMessageC$AMPacket$address(void );









static am_addr_t Ns3ActiveMessageC$AMPacket$destination(
#line 74
message_t * amsg);
#line 121
static void Ns3ActiveMessageC$AMPacket$setSource(
#line 117
message_t * amsg, 



am_addr_t addr);
#line 103
static void Ns3ActiveMessageC$AMPacket$setDestination(
#line 99
message_t * amsg, 



am_addr_t addr);
#line 147
static am_id_t Ns3ActiveMessageC$AMPacket$type(
#line 143
message_t * amsg);
#line 162
static void Ns3ActiveMessageC$AMPacket$setType(
#line 158
message_t * amsg, 



am_id_t t);
#line 136
static bool Ns3ActiveMessageC$AMPacket$isForMe(
#line 133
message_t * amsg);
#line 187
static void Ns3ActiveMessageC$AMPacket$setGroup(
#line 184
message_t * amsg, 


am_group_t grp);







static am_group_t Ns3ActiveMessageC$AMPacket$localGroup(void );
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void NS3MsgGatewayP$receive$runTask(void );
#line 75
static void NS3MsgGatewayP$sendDoneTask$runTask(void );
# 46 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareSend.nc"
static error_t NS3MsgGatewayP$Send$send(message_t *msg);
# 56 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/RadioState.nc"
static error_t NS3MsgGatewayP$State$turnOn(void );
# 55 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/ActiveMessageAddressC.nc"
static am_addr_t ActiveMessageAddressC$amAddress(void );
# 50 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/ActiveMessageAddress.nc"
static am_addr_t ActiveMessageAddressC$ActiveMessageAddress$amAddress(void );




static am_group_t ActiveMessageAddressC$ActiveMessageAddress$amGroup(void );
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer$runTask(void );
# 83 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$fired(void );
#line 83
static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$default$fired(
# 48 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
uint8_t arg_0x2b25da1e8228);
# 73 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$startOneShot(
# 48 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
uint8_t arg_0x2b25da1e8228, 
# 73 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
uint32_t dt);
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t PlatformP$SubInit$init(void );
#line 62
static error_t PlatformP$TimerInit$init(void );
# 56 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/PlatformP.nc"
static inline error_t PlatformP$Init$init(void );
# 37 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/system/LedsP.nc"
static inline error_t LedsP$Init$init(void );
# 83 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static void NsTimerP$Timer$fired(void );
# 21 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
uint32_t NsTimerP$time_now = 0;
uint64_t NsTimerP$real_time = 0;









#line 24
typedef struct NsTimerP$__nesc_unnamed4286 {

  uint32_t t0;
  uint32_t dt;
  uint32_t shoot;
  bool isoneshot : 1;
  bool isrunning : 1;
  bool _reserved : 6;
} NsTimerP$Timer_t;

NsTimerP$Timer_t NsTimerP$m_timer;

static inline void NsTimerP$updateTimer(void );
#line 49
extern int tickFired(uint64_t a)   ;
#line 79
static inline void NsTimerP$Timer$stop(void );
#line 109
static inline void NsTimerP$Timer$startOneShotAt(uint32_t t0, uint32_t dt);
#line 122
static inline uint32_t NsTimerP$Timer$getNow(void );
#line 143
static inline error_t NsTimerP$Init$init(void );
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t SimMainP$SoftwareInit$init(void );
# 60 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Boot.nc"
static void SimMainP$Boot$booted(void );
# 62 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Init.nc"
static error_t SimMainP$PlatformInit$init(void );
# 57 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Scheduler.nc"
static void SimMainP$Scheduler$init(void );
# 14 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMainP.nc"
extern void sim_function_not_found(void )   ;



extern int sim_main_start_mote(int id)   ;
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static void SchedulerBasicP$TaskBasic$runTask(
# 47 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
uint8_t arg_0x2b25d9f0c960);




extern int runNextEventExternal(uint32_t a)   ;





enum SchedulerBasicP$__nesc_unnamed4287 {

  SchedulerBasicP$NUM_TASKS = 7U, 
  SchedulerBasicP$NO_TASK = 255
};

uint8_t SchedulerBasicP$m_head;
uint8_t SchedulerBasicP$m_tail;
uint8_t SchedulerBasicP$m_next[SchedulerBasicP$NUM_TASKS];








static __inline uint8_t SchedulerBasicP$popTask(void );
#line 94
static inline bool SchedulerBasicP$isWaiting(uint8_t id);




static inline bool SchedulerBasicP$pushTask(uint8_t id);
#line 121
static inline void SchedulerBasicP$Scheduler$init(void );
#line 133
static inline bool SchedulerBasicP$Scheduler$runNextTask(void );
#line 171
static error_t SchedulerBasicP$TaskBasic$postTask(uint8_t id);




static inline void SchedulerBasicP$TaskBasic$default$runTask(uint8_t id);
# 104 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
static error_t RadioTestC$AMControl$start(void );
# 80 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
static error_t RadioTestC$AMSend$send(am_addr_t addr, 
#line 71
message_t * msg, 








uint8_t len);
# 126 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Packet.nc"
static 
#line 123
void * 


RadioTestC$Packet$getPayload(
#line 121
message_t * msg, 




uint8_t len);
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static error_t RadioTestC$send$postTask(void );
# 73 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static void RadioTestC$MilliTimer$startOneShot(uint32_t dt);
# 29 "RadioTestC.nc"
enum RadioTestC$__nesc_unnamed4288 {
#line 29
  RadioTestC$send = 0U
};
#line 29
typedef int RadioTestC$__nesc_sillytask_send[RadioTestC$send];
message_t RadioTestC$packet;
uint8_t RadioTestC$dest = 0;
bool RadioTestC$locked;
uint16_t RadioTestC$counter = 0;

static inline void RadioTestC$Boot$booted(void );







static inline void RadioTestC$AMControl$startDone(error_t err);
#line 59
static inline void RadioTestC$send$runTask(void );
#line 85
static inline void RadioTestC$MilliTimer$fired(void );




static inline message_t *RadioTestC$Receive$receive(message_t *bufPtr, 
void *payload, uint8_t len);
#line 108
static inline void RadioTestC$AMSend$sendDone(message_t *bufPtr, error_t error);
# 110 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
static void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMSend$sendDone(
#line 103
message_t * msg, 






error_t error);
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
static error_t /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$Send$send(
#line 67
message_t * msg, 







uint8_t len);
# 103 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMPacket.nc"
static void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMPacket$setDestination(
#line 99
message_t * amsg, 



am_addr_t addr);
#line 162
static void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMPacket$setType(
#line 158
message_t * amsg, 



am_id_t t);
# 53 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueEntryP.nc"
static inline error_t /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMSend$send(am_addr_t dest, 
message_t *msg, 
uint8_t len);









static inline void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$Send$sendDone(message_t *m, error_t err);
# 80 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
static error_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMSend$send(
# 48 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
am_id_t arg_0x2b25da081d28, 
# 80 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
am_addr_t addr, 
#line 71
message_t * msg, 








uint8_t len);
# 100 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$sendDone(
# 46 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
uint8_t arg_0x2b25da082b90, 
# 96 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
message_t * msg, 



error_t error);
# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Packet.nc"
static uint8_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Packet$payloadLength(
#line 74
message_t * msg);
#line 94
static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Packet$setPayloadLength(
#line 90
message_t * msg, 



uint8_t len);
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static error_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask$postTask(void );
# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMPacket.nc"
static am_addr_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMPacket$destination(
#line 74
message_t * amsg);
#line 147
static am_id_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMPacket$type(
#line 143
message_t * amsg);
# 126 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
enum /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$__nesc_unnamed4289 {
#line 126
  AMQueueImplP$0$CancelTask = 1U
};
#line 126
typedef int /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$__nesc_sillytask_CancelTask[/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$CancelTask];
#line 169
enum /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$__nesc_unnamed4290 {
#line 169
  AMQueueImplP$0$errorTask = 2U
};
#line 169
typedef int /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$__nesc_sillytask_errorTask[/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask];
#line 57
#line 55
typedef struct /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$__nesc_unnamed4291 {
  message_t * msg;
} /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue_entry_t;

uint8_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current = 1;
/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue_entry_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[1];
uint8_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$cancelMask[1 / 8 + 1];

static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$tryToSend(void );

static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$nextPacket(void );
#line 90
static inline error_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$send(uint8_t clientId, message_t *msg, 
uint8_t len);
#line 126
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$CancelTask$runTask(void );
#line 163
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$sendDone(uint8_t last, message_t * msg, error_t err);





static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask$runTask(void );




static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$tryToSend(void );
#line 189
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMSend$sendDone(am_id_t id, message_t *msg, error_t err);
#line 215
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$default$sendDone(uint8_t id, message_t *msg, error_t err);
# 113 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
static void Ns3ActiveMessageC$SplitControl$startDone(error_t error);
# 46 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareSend.nc"
static error_t Ns3ActiveMessageC$SubSend$send(message_t *msg);
# 59 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SendNotifier.nc"
static void Ns3ActiveMessageC$SendNotifier$aboutToSend(
# 19 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
am_id_t arg_0x2b25da0eb7d0, 
# 59 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SendNotifier.nc"
am_addr_t dest, 
#line 57
message_t * msg);
# 110 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
static void Ns3ActiveMessageC$AMSend$sendDone(
# 16 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
am_id_t arg_0x2b25da0cf020, 
# 103 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
message_t * msg, 






error_t error);
# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
static 
#line 74
message_t * 



Ns3ActiveMessageC$Snoop$receive(
# 18 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
am_id_t arg_0x2b25da0ecca0, 
# 71 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
message_t * msg, 
void * payload, 





uint8_t len);
# 56 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/RadioState.nc"
static error_t Ns3ActiveMessageC$SubState$turnOn(void );
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static error_t Ns3ActiveMessageC$SplitControlStartDone$postTask(void );
# 50 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/ActiveMessageAddress.nc"
static am_addr_t Ns3ActiveMessageC$ActiveMessageAddress$amAddress(void );




static am_group_t Ns3ActiveMessageC$ActiveMessageAddress$amGroup(void );
# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
static 
#line 74
message_t * 



Ns3ActiveMessageC$Receive$receive(
# 17 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
am_id_t arg_0x2b25da0ec158, 
# 71 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
message_t * msg, 
void * payload, 





uint8_t len);
# 54 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
enum Ns3ActiveMessageC$__nesc_unnamed4292 {
#line 54
  Ns3ActiveMessageC$SplitControlStartDone = 3U
};
#line 54
typedef int Ns3ActiveMessageC$__nesc_sillytask_SplitControlStartDone[Ns3ActiveMessageC$SplitControlStartDone];
#line 54
static inline void Ns3ActiveMessageC$SplitControlStartDone$runTask(void );



extern int radioStateDone(void )   ;





static inline error_t Ns3ActiveMessageC$SplitControl$start(void );
#line 79
static inline ns3packet_header_t *Ns3ActiveMessageC$getHeader(message_t *msg);





static inline void *Ns3ActiveMessageC$getPayload(message_t *msg);







static inline am_addr_t Ns3ActiveMessageC$destination(message_t *msg);



static inline void Ns3ActiveMessageC$setDestination(message_t *msg, am_addr_t addr);







static inline void Ns3ActiveMessageC$setSource(message_t *msg, am_addr_t addr);







static inline void Ns3ActiveMessageC$setGroup(message_t *msg, am_group_t grp);





static error_t Ns3ActiveMessageC$AMSend$send(am_id_t id, am_addr_t addr, message_t *msg, uint8_t len);
#line 133
static inline void Ns3ActiveMessageC$SubSend$sendDone(message_t *msg, error_t error);
#line 157
static inline void Ns3ActiveMessageC$SendNotifier$default$aboutToSend(am_id_t id, am_addr_t addr, message_t *msg);



static inline void Ns3ActiveMessageC$SubState$done(void );




static inline message_t *Ns3ActiveMessageC$SubReceive$receive(message_t *msg);
#line 184
static inline message_t *Ns3ActiveMessageC$Receive$default$receive(am_id_t id, message_t *msg, void *payload, uint8_t len);




static inline message_t *Ns3ActiveMessageC$Snoop$default$receive(am_id_t id, message_t *msg, void *payload, uint8_t len);






static __inline am_addr_t Ns3ActiveMessageC$AMPacket$address(void );




static __inline am_group_t Ns3ActiveMessageC$AMPacket$localGroup(void );




static __inline bool Ns3ActiveMessageC$AMPacket$isForMe(message_t *msg);





static __inline am_addr_t Ns3ActiveMessageC$AMPacket$destination(message_t *msg);




static __inline void Ns3ActiveMessageC$AMPacket$setDestination(message_t *msg, am_addr_t addr);









static __inline void Ns3ActiveMessageC$AMPacket$setSource(message_t *msg, am_addr_t addr);




static __inline am_id_t Ns3ActiveMessageC$AMPacket$type(message_t *msg);




static __inline void Ns3ActiveMessageC$AMPacket$setType(message_t *msg, am_id_t type);









static __inline void Ns3ActiveMessageC$AMPacket$setGroup(message_t *msg, am_group_t grp);
#line 267
static uint8_t Ns3ActiveMessageC$Packet$payloadLength(message_t *msg);





static void Ns3ActiveMessageC$Packet$setPayloadLength(message_t *msg, uint8_t len);





static inline uint8_t Ns3ActiveMessageC$Packet$maxPayloadLength(void );




static inline void *Ns3ActiveMessageC$Packet$getPayload(message_t *msg, uint8_t len);
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static error_t NS3MsgGatewayP$receive$postTask(void );
#line 67
static error_t NS3MsgGatewayP$sendDoneTask$postTask(void );
# 54 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareSend.nc"
static void NS3MsgGatewayP$Send$sendDone(message_t *msg, error_t error);
# 42 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareReceive.nc"
static message_t *NS3MsgGatewayP$Receive$receive(message_t *msg);
# 69 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/RadioState.nc"
static void NS3MsgGatewayP$State$done(void );
# 43 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/NS3MsgGatewayP.nc"
enum NS3MsgGatewayP$__nesc_unnamed4293 {
#line 43
  NS3MsgGatewayP$sendDoneTask = 4U
};
#line 43
typedef int NS3MsgGatewayP$__nesc_sillytask_sendDoneTask[NS3MsgGatewayP$sendDoneTask];



enum NS3MsgGatewayP$__nesc_unnamed4294 {
#line 47
  NS3MsgGatewayP$receive = 5U
};
#line 47
typedef int NS3MsgGatewayP$__nesc_sillytask_receive[NS3MsgGatewayP$receive];
#line 37
message_t *NS3MsgGatewayP$msg_out;
error_t NS3MsgGatewayP$error_out = 0;

message_t *NS3MsgGatewayP$msg_in;


static inline void NS3MsgGatewayP$sendDoneTask$runTask(void );



static inline void NS3MsgGatewayP$receive$runTask(void );



extern int receiveMessage(void *msg)   ;









extern int sendDone(void *msg, error_t err)   ;





extern int radioStartDone(void )   ;






static inline error_t NS3MsgGatewayP$Send$send(message_t *msg);
#line 109
static error_t NS3MsgGatewayP$State$turnOn(void );
# 65 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/ActiveMessageAddressC.nc"
am_group_t ActiveMessageAddressC$group = TOS_AM_GROUP;






static inline am_addr_t ActiveMessageAddressC$ActiveMessageAddress$amAddress(void );
#line 93
static inline am_group_t ActiveMessageAddressC$ActiveMessageAddress$amGroup(void );
#line 106
static inline am_addr_t ActiveMessageAddressC$amAddress(void );
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
static error_t /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer$postTask(void );
# 136 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
static uint32_t /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$getNow(void );
#line 129
static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$startOneShotAt(uint32_t t0, uint32_t dt);
#line 78
static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$stop(void );




static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$fired(
# 48 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
uint8_t arg_0x2b25da1e8228);
#line 71
enum /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$__nesc_unnamed4295 {
#line 71
  VirtualizeTimerC$0$updateFromTimer = 6U
};
#line 71
typedef int /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$__nesc_sillytask_updateFromTimer[/*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer];
#line 53
enum /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$__nesc_unnamed4296 {

  VirtualizeTimerC$0$NUM_TIMERS = 1U, 
  VirtualizeTimerC$0$END_OF_LIST = 255
};








#line 59
typedef struct /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$__nesc_unnamed4297 {

  uint32_t t0;
  uint32_t dt;
  bool isoneshot : 1;
  bool isrunning : 1;
  bool _reserved : 6;
} /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer_t;

/*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer_t /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$m_timers[/*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$NUM_TIMERS];




static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$fireTimers(uint32_t now);
#line 99
static inline void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer$runTask(void );
#line 138
static inline void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$fired(void );




static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$startTimer(uint8_t num, uint32_t t0, uint32_t dt, bool isoneshot);
#line 159
static inline void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$startOneShot(uint8_t num, uint32_t dt);
#line 204
static inline void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$default$fired(uint8_t num);
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

# 347 "/usr/lib/ncc/nesc_nx.h"
static __inline  uint32_t __nesc_hton_uint32(void * target, uint32_t value)
#line 347
{
  uint8_t *base = (uint8_t *)target;

#line 349
  base[3] = value;
  base[2] = value >> 8;
  base[1] = value >> 16;
  base[0] = value >> 24;
  return value;
}

#line 315
static __inline  uint16_t __nesc_hton_uint16(void * target, uint16_t value)
#line 315
{
  uint8_t *base = (uint8_t *)target;

#line 317
  base[1] = value;
  base[0] = value >> 8;
  return value;
}

# 24 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/system/../defines.h"
static inline void os_log_debug(char *string, const char *format, ...)
#line 24
{
}

# 80 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
inline static error_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMSend$send(am_id_t arg_0x2b25da081d28, am_addr_t addr, message_t * msg, uint8_t len){
#line 80
  unsigned char __nesc_result;
#line 80

#line 80
  __nesc_result = Ns3ActiveMessageC$AMSend$send(arg_0x2b25da081d28, addr, msg, len);
#line 80

#line 80
  return __nesc_result;
#line 80
}
#line 80
# 310 "/usr/lib/ncc/nesc_nx.h"
static __inline  uint16_t __nesc_ntoh_uint16(const void * source)
#line 310
{
  const uint8_t *base = (uint8_t *)source;

#line 312
  return ((uint16_t )base[0] << 8) | base[1];
}

# 79 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline ns3packet_header_t *Ns3ActiveMessageC$getHeader(message_t *msg)
#line 79
{
  ns3packet_header_t *hdr;

#line 81
  hdr = (ns3packet_header_t *)((message_t *)msg)->header;
  return hdr;
}









static inline am_addr_t Ns3ActiveMessageC$destination(message_t *msg)
#line 93
{
  return __nesc_ntoh_uint16(Ns3ActiveMessageC$getHeader(msg)->dest.nxdata);
}

#line 212
static __inline am_addr_t Ns3ActiveMessageC$AMPacket$destination(message_t *msg)
{
  return Ns3ActiveMessageC$destination(msg);
}

# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMPacket.nc"
inline static am_addr_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMPacket$destination(message_t * amsg){
#line 78
  unsigned short __nesc_result;
#line 78

#line 78
  __nesc_result = Ns3ActiveMessageC$AMPacket$destination(amsg);
#line 78

#line 78
  return __nesc_result;
#line 78
}
#line 78
# 281 "/usr/lib/ncc/nesc_nx.h"
static __inline  uint8_t __nesc_ntoh_uint8(const void * source)
#line 281
{
  const uint8_t *base = (uint8_t *)source;

#line 283
  return base[0];
}

# 232 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static __inline am_id_t Ns3ActiveMessageC$AMPacket$type(message_t *msg)
{
  return __nesc_ntoh_uint8(Ns3ActiveMessageC$getHeader(msg)->type.nxdata);
}

# 147 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMPacket.nc"
inline static am_id_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMPacket$type(message_t * amsg){
#line 147
  unsigned char __nesc_result;
#line 147

#line 147
  __nesc_result = Ns3ActiveMessageC$AMPacket$type(amsg);
#line 147

#line 147
  return __nesc_result;
#line 147
}
#line 147
# 94 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Packet.nc"
inline static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Packet$setPayloadLength(message_t * msg, uint8_t len){
#line 94
  Ns3ActiveMessageC$Packet$setPayloadLength(msg, len);
#line 94
}
#line 94
# 90 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
static inline error_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$send(uint8_t clientId, message_t *msg, 
uint8_t len)
#line 91
{
  if (clientId >= 1) {
      return FAIL;
    }
  if (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[clientId].msg != (void *)0) {
      return EBUSY;
    }
  os_log_debug("AMQueue", "AMQueue: request to send from %hhu (%p): passed checks\n", clientId, msg);

  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[clientId].msg = msg;
  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Packet$setPayloadLength(msg, len);

  if (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current >= 1) {
      error_t err;
      am_id_t amId = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMPacket$type(msg);
      am_addr_t dest = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMPacket$destination(msg);

      os_log_debug("AMQueue", "%s: request to send from %hhu (%p): queue empty\n", __FUNCTION__, clientId, msg);
      /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current = clientId;

      err = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMSend$send(amId, dest, msg, len);
      if (err != SUCCESS) {
          os_log_debug("AMQueue", "%s: underlying send failed.\n", __FUNCTION__);
          /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current = 1;
          /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[clientId].msg = (message_t *)(void *)0;
        }

      return err;
    }
  else {
      os_log_debug("AMQueue", "AMQueue: request to send from %hhu (%p): queue not empty\n", clientId, msg);
    }
  return SUCCESS;
}

# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
inline static error_t /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$Send$send(message_t * msg, uint8_t len){
#line 75
  unsigned char __nesc_result;
#line 75

#line 75
  __nesc_result = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$send(0U, msg, len);
#line 75

#line 75
  return __nesc_result;
#line 75
}
#line 75
# 286 "/usr/lib/ncc/nesc_nx.h"
static __inline  uint8_t __nesc_hton_uint8(void * target, uint8_t value)
#line 286
{
  uint8_t *base = (uint8_t *)target;

#line 288
  base[0] = value;
  return value;
}

# 237 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static __inline void Ns3ActiveMessageC$AMPacket$setType(message_t *msg, am_id_t type)
{
  __nesc_hton_uint8(Ns3ActiveMessageC$getHeader(msg)->type.nxdata, type);
}

# 162 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMPacket.nc"
inline static void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMPacket$setType(message_t * amsg, am_id_t t){
#line 162
  Ns3ActiveMessageC$AMPacket$setType(amsg, t);
#line 162
}
#line 162
# 97 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline void Ns3ActiveMessageC$setDestination(message_t *msg, am_addr_t addr)
#line 97
{
  __nesc_hton_uint16(Ns3ActiveMessageC$getHeader(msg)->dest.nxdata, addr);
}

#line 217
static __inline void Ns3ActiveMessageC$AMPacket$setDestination(message_t *msg, am_addr_t addr)
{
  Ns3ActiveMessageC$setDestination(msg, addr);
}

# 103 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMPacket.nc"
inline static void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMPacket$setDestination(message_t * amsg, am_addr_t addr){
#line 103
  Ns3ActiveMessageC$AMPacket$setDestination(amsg, addr);
#line 103
}
#line 103
# 53 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueEntryP.nc"
static inline error_t /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMSend$send(am_addr_t dest, 
message_t *msg, 
uint8_t len)
#line 55
{
  /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMPacket$setDestination(msg, dest);
  /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMPacket$setType(msg, 12);
  return /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$Send$send(msg, len);
}

# 80 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
inline static error_t RadioTestC$AMSend$send(am_addr_t addr, message_t * msg, uint8_t len){
#line 80
  unsigned char __nesc_result;
#line 80

#line 80
  __nesc_result = /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMSend$send(addr, msg, len);
#line 80

#line 80
  return __nesc_result;
#line 80
}
#line 80
# 284 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline void *Ns3ActiveMessageC$Packet$getPayload(message_t *msg, uint8_t len)
{
  for (; 0; ) ;

  return (void *)msg->data;
}

# 126 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Packet.nc"
inline static void * RadioTestC$Packet$getPayload(message_t * msg, uint8_t len){
#line 126
  void *__nesc_result;
#line 126

#line 126
  __nesc_result = Ns3ActiveMessageC$Packet$getPayload(msg, len);
#line 126

#line 126
  return __nesc_result;
#line 126
}
#line 126
# 59 "RadioTestC.nc"
static inline void RadioTestC$send$runTask(void )
#line 59
{
  RadioTestC$counter++;

  printf("TOSNODE (%d) send() - COUNTER (%d)- DEST (%d) PKT SIZE (%ld)\n", 
  TOS_NODE_ID, RadioTestC$counter, RadioTestC$dest, sizeof(radio_count_msg_t ));
  if (RadioTestC$locked) {

      return;
    }
  else {
      radio_count_msg_t *rcm = (radio_count_msg_t *)RadioTestC$Packet$getPayload(&RadioTestC$packet, sizeof(radio_count_msg_t ));

#line 70
      if (rcm == (void *)0) {

          return;
        }
      __nesc_hton_uint16(rcm->counter.nxdata, RadioTestC$counter);
      __nesc_hton_uint32(rcm->a.nxdata, 178956970);
      __nesc_hton_uint32(rcm->b.nxdata, 196852667);
      __nesc_hton_uint32(rcm->c.nxdata, 214748364);
      __nesc_hton_uint32(rcm->d.nxdata, 232644061);
      if (RadioTestC$AMSend$send(RadioTestC$dest, &RadioTestC$packet, sizeof(radio_count_msg_t )) == SUCCESS) {
          RadioTestC$locked = true;
        }
    }
}

#line 108
static inline void RadioTestC$AMSend$sendDone(message_t *bufPtr, error_t error)
#line 108
{
  if (&RadioTestC$packet == bufPtr) {
      RadioTestC$locked = false;
    }
}

# 110 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
inline static void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMSend$sendDone(message_t * msg, error_t error){
#line 110
  RadioTestC$AMSend$sendDone(msg, error);
#line 110
}
#line 110
# 65 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueEntryP.nc"
static inline void /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$Send$sendDone(message_t *m, error_t err)
#line 65
{
  /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$AMSend$sendDone(m, err);
}

# 215 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$default$sendDone(uint8_t id, message_t *msg, error_t err)
#line 215
{
}

# 100 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Send.nc"
inline static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$sendDone(uint8_t arg_0x2b25da082b90, message_t * msg, error_t error){
#line 100
  switch (arg_0x2b25da082b90) {
#line 100
    case 0U:
#line 100
      /*RadioApp.AMSenderC.SenderC.AMQueueEntryP*/AMQueueEntryP$0$Send$sendDone(msg, error);
#line 100
      break;
#line 100
    default:
#line 100
      /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$default$sendDone(arg_0x2b25da082b90, msg, error);
#line 100
      break;
#line 100
    }
#line 100
}
#line 100
# 163 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$sendDone(uint8_t last, message_t * msg, error_t err)
#line 163
{
  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[last].msg = (message_t *)(void *)0;
  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$tryToSend();
  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$sendDone(last, msg, err);
}

static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask$runTask(void )
#line 169
{
  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$sendDone(/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current, /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current].msg, FAIL);
}

#line 126
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$CancelTask$runTask(void )
#line 126
{
  uint8_t i;
#line 127
  uint8_t j;
#line 127
  uint8_t mask;
#line 127
  uint8_t last;
  message_t *msg;

#line 129
  for (i = 0; i < 1 / 8 + 1; i++) {
      if (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$cancelMask[i]) {
          for (mask = 1, j = 0; j < 8; j++) {
              if (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$cancelMask[i] & mask) {
                  last = i * 8 + j;
                  msg = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[last].msg;
                  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[last].msg = (message_t *)(void *)0;
                  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$cancelMask[i] &= ~mask;
                  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Send$sendDone(last, msg, ECANCEL);
                }
              mask <<= 1;
            }
        }
    }
}

# 56 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/RadioState.nc"
inline static error_t Ns3ActiveMessageC$SubState$turnOn(void ){
#line 56
  unsigned char __nesc_result;
#line 56

#line 56
  __nesc_result = NS3MsgGatewayP$State$turnOn();
#line 56

#line 56
  return __nesc_result;
#line 56
}
#line 56
# 64 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline error_t Ns3ActiveMessageC$SplitControl$start(void )
#line 64
{

  Ns3ActiveMessageC$SubState$turnOn();
  return 0;
}

# 104 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
inline static error_t RadioTestC$AMControl$start(void ){
#line 104
  unsigned char __nesc_result;
#line 104

#line 104
  __nesc_result = Ns3ActiveMessageC$SplitControl$start();
#line 104

#line 104
  return __nesc_result;
#line 104
}
#line 104
# 122 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
static inline uint32_t NsTimerP$Timer$getNow(void )
#line 122
{

  return NsTimerP$time_now;
}

# 136 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
inline static uint32_t /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$getNow(void ){
#line 136
  unsigned int __nesc_result;
#line 136

#line 136
  __nesc_result = NsTimerP$Timer$getNow();
#line 136

#line 136
  return __nesc_result;
#line 136
}
#line 136
# 159 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
static inline void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$startOneShot(uint8_t num, uint32_t dt)
{
  /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$startTimer(num, /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$getNow(), dt, true);
}

# 73 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
inline static void RadioTestC$MilliTimer$startOneShot(uint32_t dt){
#line 73
  /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$startOneShot(0U, dt);
#line 73
}
#line 73
# 43 "RadioTestC.nc"
static inline void RadioTestC$AMControl$startDone(error_t err)
#line 43
{

  if (err == SUCCESS) {
      if (TOS_NODE_ID == 10) {
          RadioTestC$MilliTimer$startOneShot(100);
        }
    }
  else {
      RadioTestC$AMControl$start();
    }
}

# 113 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SplitControl.nc"
inline static void Ns3ActiveMessageC$SplitControl$startDone(error_t error){
#line 113
  RadioTestC$AMControl$startDone(error);
#line 113
}
#line 113
# 54 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline void Ns3ActiveMessageC$SplitControlStartDone$runTask(void )
#line 54
{
  Ns3ActiveMessageC$SplitControl$startDone(SUCCESS);
}

# 189 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMSend$sendDone(am_id_t id, message_t *msg, error_t err)
#line 189
{





  if (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current >= 1) {
      return;
    }
  if (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current].msg == msg) {
      /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$sendDone(/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current, msg, err);
    }
  else {
      os_log_debug("PointerBug", "%s received send done for %p, signaling for %p.\n", __FUNCTION__, msg, /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current].msg);
    }
}

# 110 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/AMSend.nc"
inline static void Ns3ActiveMessageC$AMSend$sendDone(am_id_t arg_0x2b25da0cf020, message_t * msg, error_t error){
#line 110
  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMSend$sendDone(arg_0x2b25da0cf020, msg, error);
#line 110
}
#line 110
# 133 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline void Ns3ActiveMessageC$SubSend$sendDone(message_t *msg, error_t error)
{
  Ns3ActiveMessageC$AMSend$sendDone(Ns3ActiveMessageC$AMPacket$type(msg), msg, error);
}

# 54 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareSend.nc"
inline static void NS3MsgGatewayP$Send$sendDone(message_t *msg, error_t error){
#line 54
  Ns3ActiveMessageC$SubSend$sendDone(msg, error);
#line 54
}
#line 54
# 43 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/NS3MsgGatewayP.nc"
static inline void NS3MsgGatewayP$sendDoneTask$runTask(void )
#line 43
{
  NS3MsgGatewayP$Send$sendDone(NS3MsgGatewayP$msg_out, NS3MsgGatewayP$error_out);
}

# 189 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline message_t *Ns3ActiveMessageC$Snoop$default$receive(am_id_t id, message_t *msg, void *payload, uint8_t len)
{
  return msg;
}

# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
inline static message_t * Ns3ActiveMessageC$Snoop$receive(am_id_t arg_0x2b25da0ecca0, message_t * msg, void * payload, uint8_t len){
#line 78
  nx_struct message_t *__nesc_result;
#line 78

#line 78
    __nesc_result = Ns3ActiveMessageC$Snoop$default$receive(arg_0x2b25da0ecca0, msg, payload, len);
#line 78

#line 78
  return __nesc_result;
#line 78
}
#line 78
# 90 "RadioTestC.nc"
static inline message_t *RadioTestC$Receive$receive(message_t *bufPtr, 
void *payload, uint8_t len)
#line 91
{

  if (len != sizeof(radio_count_msg_t )) {

      return bufPtr;
    }
  else 
#line 96
    {


      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 99
        RadioTestC$counter = __nesc_ntoh_uint16(((radio_count_msg_t *)payload)->counter.nxdata);
#line 99
        __nesc_atomic_end(__nesc_atomic); }
      printf("TOSNODE (%d) receive (%d) len (%d)\n", TOS_NODE_ID, RadioTestC$counter, len);

      RadioTestC$MilliTimer$startOneShot(10);
      return bufPtr;
    }
}

# 184 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline message_t *Ns3ActiveMessageC$Receive$default$receive(am_id_t id, message_t *msg, void *payload, uint8_t len)
{
  return msg;
}

# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Receive.nc"
inline static message_t * Ns3ActiveMessageC$Receive$receive(am_id_t arg_0x2b25da0ec158, message_t * msg, void * payload, uint8_t len){
#line 78
  nx_struct message_t *__nesc_result;
#line 78

#line 78
  switch (arg_0x2b25da0ec158) {
#line 78
    case 12:
#line 78
      __nesc_result = RadioTestC$Receive$receive(msg, payload, len);
#line 78
      break;
#line 78
    default:
#line 78
      __nesc_result = Ns3ActiveMessageC$Receive$default$receive(arg_0x2b25da0ec158, msg, payload, len);
#line 78
      break;
#line 78
    }
#line 78

#line 78
  return __nesc_result;
#line 78
}
#line 78
# 106 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/ActiveMessageAddressC.nc"
static inline am_addr_t ActiveMessageAddressC$amAddress(void )
#line 106
{
  am_addr_t myAddr;

#line 108
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 108
    myAddr = TOS_NODE_ID;
#line 108
    __nesc_atomic_end(__nesc_atomic); }
  return myAddr;
}

#line 72
static inline am_addr_t ActiveMessageAddressC$ActiveMessageAddress$amAddress(void )
#line 72
{
  return ActiveMessageAddressC$amAddress();
}

# 50 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/ActiveMessageAddress.nc"
inline static am_addr_t Ns3ActiveMessageC$ActiveMessageAddress$amAddress(void ){
#line 50
  unsigned short __nesc_result;
#line 50

#line 50
  __nesc_result = ActiveMessageAddressC$ActiveMessageAddress$amAddress();
#line 50

#line 50
  return __nesc_result;
#line 50
}
#line 50
# 196 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static __inline am_addr_t Ns3ActiveMessageC$AMPacket$address(void )
{
  return Ns3ActiveMessageC$ActiveMessageAddress$amAddress();
}






static __inline bool Ns3ActiveMessageC$AMPacket$isForMe(message_t *msg)
{
  am_addr_t addr = Ns3ActiveMessageC$AMPacket$destination(msg);

#line 209
  return addr == Ns3ActiveMessageC$AMPacket$address() || addr == AM_BROADCAST_ADDR;
}

#line 85
static inline void *Ns3ActiveMessageC$getPayload(message_t *msg)
#line 85
{
  return (void *)msg->data;
}

#line 166
static inline message_t *Ns3ActiveMessageC$SubReceive$receive(message_t *msg)
{
  am_id_t id = Ns3ActiveMessageC$AMPacket$type(msg);
  void *payload = Ns3ActiveMessageC$getPayload(msg);
  uint8_t len = Ns3ActiveMessageC$Packet$payloadLength(msg);





  Ns3ActiveMessageC$AMPacket$isForMe(msg) ? 
  Ns3ActiveMessageC$Receive$receive(id, msg, payload, len) : 
  Ns3ActiveMessageC$Snoop$receive(id, msg, payload, len);

  return msg;
}

# 42 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareReceive.nc"
inline static message_t *NS3MsgGatewayP$Receive$receive(message_t *msg){
#line 42
  nx_struct message_t *__nesc_result;
#line 42

#line 42
  __nesc_result = Ns3ActiveMessageC$SubReceive$receive(msg);
#line 42

#line 42
  return __nesc_result;
#line 42
}
#line 42
# 47 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/NS3MsgGatewayP.nc"
static inline void NS3MsgGatewayP$receive$runTask(void )
#line 47
{
  NS3MsgGatewayP$Receive$receive(NS3MsgGatewayP$msg_in);
}

# 138 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
static inline void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$fired(void )
{
  /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$fireTimers(/*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$getNow());
}

# 83 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
inline static void NsTimerP$Timer$fired(void ){
#line 83
  /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$fired();
#line 83
}
#line 83
# 36 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
static inline void NsTimerP$updateTimer(void )
#line 36
{

  if (NsTimerP$m_timer.shoot == NsTimerP$time_now) {

      NsTimerP$Timer$fired();
    }
}

#line 109
static inline void NsTimerP$Timer$startOneShotAt(uint32_t t0, uint32_t dt)
#line 109
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 110
    {
      NsTimerP$m_timer.isoneshot = true;
      NsTimerP$m_timer.dt = dt;
      NsTimerP$m_timer.t0 = t0;
      NsTimerP$m_timer.shoot = t0 + dt;
      NsTimerP$m_timer.isrunning = true;
    }
#line 116
    __nesc_atomic_end(__nesc_atomic); }

  NsTimerP$updateTimer();
}

# 129 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
inline static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$startOneShotAt(uint32_t t0, uint32_t dt){
#line 129
  NsTimerP$Timer$startOneShotAt(t0, dt);
#line 129
}
#line 129
# 79 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
static inline void NsTimerP$Timer$stop(void )
#line 79
{

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 81
    {
      NsTimerP$m_timer.isoneshot = false;
      NsTimerP$m_timer.dt = 0;
      NsTimerP$m_timer.t0 = 0;
      NsTimerP$m_timer.shoot = 0;
      NsTimerP$m_timer.isrunning = false;
    }
#line 87
    __nesc_atomic_end(__nesc_atomic); }
}

# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
inline static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$stop(void ){
#line 78
  NsTimerP$Timer$stop();
#line 78
}
#line 78
# 99 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
static inline void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer$runTask(void )
{




  uint32_t now = /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$getNow();
  int32_t min_remaining = (1UL << 31) - 1;
  bool min_remaining_isset = false;
  uint8_t num;

  /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$stop();

  for (num = 0; num < /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$NUM_TIMERS; num++) 
    {
      /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer_t *timer = &/*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$m_timers[num];

      if (timer->isrunning) 
        {
          uint32_t elapsed = now - timer->t0;
          int32_t remaining = timer->dt - elapsed;

          if (remaining < min_remaining) 
            {
              min_remaining = remaining;
              min_remaining_isset = true;
            }
        }
    }

  if (min_remaining_isset) 
    {
      if (min_remaining <= 0) {
        /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$fireTimers(now);
        }
      else {
#line 134
        /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$TimerFrom$startOneShotAt(now, min_remaining);
        }
    }
}

# 176 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
static inline void SchedulerBasicP$TaskBasic$default$runTask(uint8_t id)
{
}

# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
inline static void SchedulerBasicP$TaskBasic$runTask(uint8_t arg_0x2b25d9f0c960){
#line 75
  switch (arg_0x2b25d9f0c960) {
#line 75
    case RadioTestC$send:
#line 75
      RadioTestC$send$runTask();
#line 75
      break;
#line 75
    case /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$CancelTask:
#line 75
      /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$CancelTask$runTask();
#line 75
      break;
#line 75
    case /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask:
#line 75
      /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask$runTask();
#line 75
      break;
#line 75
    case Ns3ActiveMessageC$SplitControlStartDone:
#line 75
      Ns3ActiveMessageC$SplitControlStartDone$runTask();
#line 75
      break;
#line 75
    case NS3MsgGatewayP$sendDoneTask:
#line 75
      NS3MsgGatewayP$sendDoneTask$runTask();
#line 75
      break;
#line 75
    case NS3MsgGatewayP$receive:
#line 75
      NS3MsgGatewayP$receive$runTask();
#line 75
      break;
#line 75
    case /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer:
#line 75
      /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer$runTask();
#line 75
      break;
#line 75
    default:
#line 75
      SchedulerBasicP$TaskBasic$default$runTask(arg_0x2b25d9f0c960);
#line 75
      break;
#line 75
    }
#line 75
}
#line 75
# 75 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
static __inline uint8_t SchedulerBasicP$popTask(void )
{
  if (SchedulerBasicP$m_head != SchedulerBasicP$NO_TASK) 
    {
      uint8_t id = SchedulerBasicP$m_head;

#line 80
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

#line 133
static inline bool SchedulerBasicP$Scheduler$runNextTask(void )
{

  uint8_t nextTask;

#line 137
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {
      nextTask = SchedulerBasicP$popTask();
      if (nextTask == SchedulerBasicP$NO_TASK) 
        {
          {
            unsigned char __nesc_temp = 
#line 142
            true;

            {
#line 142
              __nesc_atomic_end(__nesc_atomic); 
#line 142
              return __nesc_temp;
            }
          }
        }
    }
#line 146
    __nesc_atomic_end(__nesc_atomic); }
#line 145
  SchedulerBasicP$TaskBasic$runTask(nextTask);
  return true;
}

# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
inline static error_t RadioTestC$send$postTask(void ){
#line 67
  unsigned char __nesc_result;
#line 67

#line 67
  __nesc_result = SchedulerBasicP$TaskBasic$postTask(RadioTestC$send);
#line 67

#line 67
  return __nesc_result;
#line 67
}
#line 67
# 85 "RadioTestC.nc"
static inline void RadioTestC$MilliTimer$fired(void )
#line 85
{

  RadioTestC$send$postTask();
}

# 204 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
static inline void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$default$fired(uint8_t num)
{
}

# 83 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/Timer.nc"
inline static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$fired(uint8_t arg_0x2b25da1e8228){
#line 83
  switch (arg_0x2b25da1e8228) {
#line 83
    case 0U:
#line 83
      RadioTestC$MilliTimer$fired();
#line 83
      break;
#line 83
    default:
#line 83
      /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$default$fired(arg_0x2b25da1e8228);
#line 83
      break;
#line 83
    }
#line 83
}
#line 83
# 94 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
static inline bool SchedulerBasicP$isWaiting(uint8_t id)
{
  return SchedulerBasicP$m_next[id] != SchedulerBasicP$NO_TASK || SchedulerBasicP$m_tail == id;
}

static inline bool SchedulerBasicP$pushTask(uint8_t id)
{
  if (!SchedulerBasicP$isWaiting(id)) 
    {
      if (SchedulerBasicP$m_head == SchedulerBasicP$NO_TASK) 
        {
          SchedulerBasicP$m_head = id;
          SchedulerBasicP$m_tail = id;
        }
      else 
        {
          SchedulerBasicP$m_next[SchedulerBasicP$m_tail] = id;
          SchedulerBasicP$m_tail = id;
        }
      return true;
    }
  else 
    {
      return false;
    }
}

# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
inline static error_t /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer$postTask(void ){
#line 67
  unsigned char __nesc_result;
#line 67

#line 67
  __nesc_result = SchedulerBasicP$TaskBasic$postTask(/*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer);
#line 67

#line 67
  return __nesc_result;
#line 67
}
#line 67
# 65 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
static inline void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$nextPacket(void )
#line 65
{
  uint8_t i;

#line 67
  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current = (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current + 1) % 1;
  for (i = 0; i < 1; i++) {
      if (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current].msg == (void *)0 || 
      /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$cancelMask[/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current / 8] & (1 << /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current % 8)) 
        {
          /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current = (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current + 1) % 1;
        }
      else {
          break;
        }
    }
  if (i >= 1) {
#line 78
    /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current = 1;
    }
}

# 78 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Packet.nc"
inline static uint8_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Packet$payloadLength(message_t * msg){
#line 78
  unsigned char __nesc_result;
#line 78

#line 78
  __nesc_result = Ns3ActiveMessageC$Packet$payloadLength(msg);
#line 78

#line 78
  return __nesc_result;
#line 78
}
#line 78
# 279 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline uint8_t Ns3ActiveMessageC$Packet$maxPayloadLength(void )
{
  return 28;
}

#line 105
static inline void Ns3ActiveMessageC$setSource(message_t *msg, am_addr_t addr)
#line 105
{
  __nesc_hton_uint16(Ns3ActiveMessageC$getHeader(msg)->src.nxdata, addr);
}

#line 227
static __inline void Ns3ActiveMessageC$AMPacket$setSource(message_t *msg, am_addr_t addr)
{
  Ns3ActiveMessageC$setSource(msg, addr);
}

#line 113
static inline void Ns3ActiveMessageC$setGroup(message_t *msg, am_group_t grp)
#line 113
{
  __nesc_hton_uint8(Ns3ActiveMessageC$getHeader(msg)->destpan.nxdata, grp);
}

#line 247
static __inline void Ns3ActiveMessageC$AMPacket$setGroup(message_t *msg, am_group_t grp)
{
  Ns3ActiveMessageC$setGroup(msg, grp);
}

# 93 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/ActiveMessageAddressC.nc"
static inline am_group_t ActiveMessageAddressC$ActiveMessageAddress$amGroup(void )
#line 93
{
  am_group_t myGroup;

#line 95
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 95
    myGroup = ActiveMessageAddressC$group;
#line 95
    __nesc_atomic_end(__nesc_atomic); }
  return myGroup;
}

# 55 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/ActiveMessageAddress.nc"
inline static am_group_t Ns3ActiveMessageC$ActiveMessageAddress$amGroup(void ){
#line 55
  unsigned char __nesc_result;
#line 55

#line 55
  __nesc_result = ActiveMessageAddressC$ActiveMessageAddress$amGroup();
#line 55

#line 55
  return __nesc_result;
#line 55
}
#line 55
# 201 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static __inline am_group_t Ns3ActiveMessageC$AMPacket$localGroup(void )
{
  return Ns3ActiveMessageC$ActiveMessageAddress$amGroup();
}

#line 157
static inline void Ns3ActiveMessageC$SendNotifier$default$aboutToSend(am_id_t id, am_addr_t addr, message_t *msg)
{
}

# 59 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/SendNotifier.nc"
inline static void Ns3ActiveMessageC$SendNotifier$aboutToSend(am_id_t arg_0x2b25da0eb7d0, am_addr_t dest, message_t * msg){
#line 59
    Ns3ActiveMessageC$SendNotifier$default$aboutToSend(arg_0x2b25da0eb7d0, dest, msg);
#line 59
}
#line 59
# 74 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/NS3MsgGatewayP.nc"
static inline error_t NS3MsgGatewayP$Send$send(message_t *msg)
#line 74
{
  NS3MsgGatewayP$msg_out = msg;


  a = gatewayRadio(proxy, RADIO_SEND, -1, -1, (void *)msg, (void *)msg);
  return 0;
}

# 46 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/BareSend.nc"
inline static error_t Ns3ActiveMessageC$SubSend$send(message_t *msg){
#line 46
  unsigned char __nesc_result;
#line 46

#line 46
  __nesc_result = NS3MsgGatewayP$Send$send(msg);
#line 46

#line 46
  return __nesc_result;
#line 46
}
#line 46
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
inline static error_t /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask$postTask(void ){
#line 67
  unsigned char __nesc_result;
#line 67

#line 67
  __nesc_result = SchedulerBasicP$TaskBasic$postTask(/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask);
#line 67

#line 67
  return __nesc_result;
#line 67
}
#line 67
# 121 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
static inline void SchedulerBasicP$Scheduler$init(void )
{
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
# 143 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
static inline error_t NsTimerP$Init$init(void )
#line 143
{
  /* atomic removed: atomic calls only */
#line 144
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
# 37 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/system/LedsP.nc"
static inline error_t LedsP$Init$init(void )
#line 37
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
inline static error_t SimMainP$SoftwareInit$init(void ){
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
# 35 "RadioTestC.nc"
static inline void RadioTestC$Boot$booted(void )
#line 35
{

  if (TOS_NODE_ID == 10) {
#line 37
    RadioTestC$dest = 0;
    }
  else {
#line 38
    if (TOS_NODE_ID == 0) {
#line 38
      RadioTestC$dest = 10;
      }
    }
#line 40
  RadioTestC$AMControl$start();
}

# 60 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/Boot.nc"
inline static void SimMainP$Boot$booted(void ){
#line 60
  RadioTestC$Boot$booted();
#line 60
}
#line 60
# 67 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/interfaces/TaskBasic.nc"
inline static error_t NS3MsgGatewayP$receive$postTask(void ){
#line 67
  unsigned char __nesc_result;
#line 67

#line 67
  __nesc_result = SchedulerBasicP$TaskBasic$postTask(NS3MsgGatewayP$receive);
#line 67

#line 67
  return __nesc_result;
#line 67
}
#line 67
inline static error_t NS3MsgGatewayP$sendDoneTask$postTask(void ){
#line 67
  unsigned char __nesc_result;
#line 67

#line 67
  __nesc_result = SchedulerBasicP$TaskBasic$postTask(NS3MsgGatewayP$sendDoneTask);
#line 67

#line 67
  return __nesc_result;
#line 67
}
#line 67
inline static error_t Ns3ActiveMessageC$SplitControlStartDone$postTask(void ){
#line 67
  unsigned char __nesc_result;
#line 67

#line 67
  __nesc_result = SchedulerBasicP$TaskBasic$postTask(Ns3ActiveMessageC$SplitControlStartDone);
#line 67

#line 67
  return __nesc_result;
#line 67
}
#line 67
# 161 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static inline void Ns3ActiveMessageC$SubState$done(void )
#line 161
{
  Ns3ActiveMessageC$SplitControlStartDone$postTask();
}

# 69 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/radio/RadioState.nc"
inline static void NS3MsgGatewayP$State$done(void ){
#line 69
  Ns3ActiveMessageC$SubState$done();
#line 69
}
#line 69
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
    }
  else 
    {
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

# 73 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$fireTimers(uint32_t now)
{
  uint8_t num;

#line 76
  for (num = 0; num < /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$NUM_TIMERS; num++) 
    {
      /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer_t *timer = &/*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$m_timers[num];

      if (timer->isrunning) 
        {
          uint32_t elapsed = now - timer->t0;

          if (elapsed >= timer->dt) 
            {
              if (timer->isoneshot) {
                timer->isrunning = false;
                }
              else {
#line 89
                timer->t0 += timer->dt;
                }
              /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer$fired(num);
              break;
            }
        }
    }
  /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer$postTask();
}

# 171 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SchedulerBasicP.nc"
static error_t SchedulerBasicP$TaskBasic$postTask(uint8_t id)
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 173
    {
#line 173
      {
        unsigned char __nesc_temp = 
#line 173
        SchedulerBasicP$pushTask(id) ? SUCCESS : EBUSY;

        {
#line 173
          __nesc_atomic_end(__nesc_atomic); 
#line 173
          return __nesc_temp;
        }
      }
    }
#line 176
    __nesc_atomic_end(__nesc_atomic); }
}

# 267 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static uint8_t Ns3ActiveMessageC$Packet$payloadLength(message_t *msg)
{

  return __nesc_ntoh_uint8(Ns3ActiveMessageC$getHeader(msg)->length.nxdata);
}

# 143 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/lib/timer/VirtualizeTimerC.nc"
static void /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$startTimer(uint8_t num, uint32_t t0, uint32_t dt, bool isoneshot)
{
  /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$Timer_t *timer = &/*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$m_timers[num];

#line 146
  timer->t0 = t0;
  timer->dt = dt;
  timer->isoneshot = isoneshot;
  timer->isrunning = true;
  /*HilTimerMilliC.VirtualizeTimerC*/VirtualizeTimerC$0$updateFromTimer$postTask();
}

# 174 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/system/AMQueueImplP.nc"
static void /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$tryToSend(void )
#line 174
{
  /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$nextPacket();
  if (/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current < 1) {
      error_t nextErr;
      message_t *nextMsg = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$queue[/*AMQueueP.AMQueueImplP*/AMQueueImplP$0$current].msg;
      am_id_t nextId = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMPacket$type(nextMsg);
      am_addr_t nextDest = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMPacket$destination(nextMsg);
      uint8_t len = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$Packet$payloadLength(nextMsg);

#line 182
      nextErr = /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$AMSend$send(nextId, nextDest, nextMsg, len);
      if (nextErr != SUCCESS) {
          /*AMQueueP.AMQueueImplP*/AMQueueImplP$0$errorTask$postTask();
        }
    }
}

# 119 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
static error_t Ns3ActiveMessageC$AMSend$send(am_id_t id, am_addr_t addr, message_t *msg, uint8_t len)
{
  if (len > Ns3ActiveMessageC$Packet$maxPayloadLength()) {
    return EINVAL;
    }
  Ns3ActiveMessageC$Packet$setPayloadLength(msg, len);
  Ns3ActiveMessageC$AMPacket$setSource(msg, Ns3ActiveMessageC$AMPacket$address());
  Ns3ActiveMessageC$AMPacket$setGroup(msg, Ns3ActiveMessageC$AMPacket$localGroup());
  Ns3ActiveMessageC$AMPacket$setType(msg, id);
  Ns3ActiveMessageC$AMPacket$setDestination(msg, addr);
  Ns3ActiveMessageC$SendNotifier$aboutToSend(id, addr, msg);
  return Ns3ActiveMessageC$SubSend$send(msg);
}

#line 273
static void Ns3ActiveMessageC$Packet$setPayloadLength(message_t *msg, uint8_t len)
{
  for (; 0; ) ;
  __nesc_hton_uint8(Ns3ActiveMessageC$getHeader(msg)->length.nxdata, len);
}

# 109 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/NS3MsgGatewayP.nc"
static error_t NS3MsgGatewayP$State$turnOn(void )
#line 109
{
  void *buff = (void *)0;

#line 111
  return gatewayRadio(proxy, RADIO_ON, -1, -1, buff, buff);
}

# 49 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/timers/NsTimerP.nc"
extern   int tickFired(uint64_t a)
#line 49
{

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 51
    {
      NsTimerP$time_now = NsTimerP$time_now + 1;
      NsTimerP$real_time = a;
    }
#line 54
    __nesc_atomic_end(__nesc_atomic); }
  NsTimerP$updateTimer();
  runNextEventExternal(0);


  return 0;
}

# 14 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/sim/SimMainP.nc"
extern   void sim_function_not_found(void )
#line 14
{
  printf("ERROR: Function does not exist!!!\n");
}

extern   int sim_main_start_mote(int id)
#line 18
{
  TOS_NODE_ID = id;



  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 23
    {






      SimMainP$Scheduler$init();





      SimMainP$PlatformInit$init();






      SimMainP$SoftwareInit$init();

      TOS_NODE_ID = id;
    }
#line 46
    __nesc_atomic_end(__nesc_atomic); }







  SimMainP$Boot$booted();







  return 0;
}

# 58 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/Ns3ActiveMessageC.nc"
extern   int radioStateDone(void )
#line 58
{

  Ns3ActiveMessageC$SplitControlStartDone$postTask();
  return 0;
}

# 51 "/home/lauril/dev/symphony/tinyos-2.1.1/tos/platforms/ns3/NS3MsgGatewayP.nc"
extern   int receiveMessage(void *msg)
#line 51
{



  NS3MsgGatewayP$msg_in = (message_t *)msg;

  NS3MsgGatewayP$receive$postTask();
  return 0;
}

extern   int sendDone(void *msg, error_t err)
#line 61
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 62
    NS3MsgGatewayP$error_out = err;
#line 62
    __nesc_atomic_end(__nesc_atomic); }
  NS3MsgGatewayP$sendDoneTask$postTask();
  return 0;
}

extern   int radioStartDone(void )
#line 67
{
  NS3MsgGatewayP$State$done();
  return 0;
}

 #ifdef __cplusplus 
 		 } 
 		 #endif 
