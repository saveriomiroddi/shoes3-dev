#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef WIN32
#define fseeko fseeko64
#define ftello ftello64
#ifndef off_t	// cjc
#define off_t off64_t
#endif
#define mkdir(x, y) mkdir(x)
#endif

#define TRUE 1
#define FALSE 0

#define FLIPENDIAN(x) flipEndian((unsigned char *)(&(x)), sizeof(x))
#define FLIPENDIANLE(x) flipEndianLE((unsigned char *)(&(x)), sizeof(x))

#define IS_BIG_ENDIAN      0
#define IS_LITTLE_ENDIAN   1

#define TIME_OFFSET_FROM_UNIX 2082844800L
#define APPLE_TO_UNIX_TIME(x) ((x) - TIME_OFFSET_FROM_UNIX)
#define UNIX_TO_APPLE_TIME(x) ((x) + TIME_OFFSET_FROM_UNIX)

#define ASSERT(x, m) if(!(x)) { fflush(stdout); fprintf(stderr, "error: %s\n", m); perror("error"); fflush(stderr); exit(1); }

extern char endianness;

static inline void flipEndian(unsigned char* x, int length) {
  int i;
  unsigned char tmp;

  if(endianness == IS_BIG_ENDIAN) {
    return;
  } else {
    for(i = 0; i < (length / 2); i++) {
      tmp = x[i];
      x[i] = x[length - i - 1];
      x[length - i - 1] = tmp;
    }
  }
}

static inline void flipEndianLE(unsigned char* x, int length) {
  int i;
  unsigned char tmp;

  if(endianness == IS_LITTLE_ENDIAN) {
    return;
  } else {
    for(i = 0; i < (length / 2); i++) {
      tmp = x[i];
      x[i] = x[length - i - 1];
      x[length - i - 1] = tmp;
    }
  }
}

struct io_func_struct;

typedef int (*readFunc)(struct io_func_struct* io, off_t location, size_t size, void *buffer);
typedef int (*writeFunc)(struct io_func_struct* io, off_t location, size_t size, void *buffer);
typedef void (*closeFunc)(struct io_func_struct* io);

typedef struct io_func_struct {
  void* data;
  readFunc read;
  writeFunc write;
  closeFunc close;
} io_func;

#endif
