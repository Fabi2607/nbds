/* 
 * Written by Josh Dybnis and released to the public domain, as explained at
 * http://creativecommons.org/licenses/publicdomain
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>

#define MAX_NUM_THREADS  4 // make this whatever you want, but make it a power of 2

#define CACHE_LINE_SIZE  64 // 64 byte cache line on x86 and x86-64
#define CACHE_LINE_SCALE 6  // log base 2 of the cache line size

#define EXPECT_TRUE(x)      __builtin_expect(!!(x), 1)
#define EXPECT_FALSE(x)     __builtin_expect(!!(x), 0)

#define SYNC_SWAP           __sync_lock_test_and_set
#define SYNC_CAS            __sync_val_compare_and_swap
#define SYNC_ADD            __sync_add_and_fetch
#define SYNC_FETCH_AND_OR   __sync_fetch_and_or

#define COUNT_TRAILING_ZEROS __builtin_ctz

#define MASK(n)     ((1ULL << (n)) - 1)

#define TRUE  1
#define FALSE 0

#ifdef NBD32
#define TAG1         (1U << 31)
#define TAG2         (1U << 30)
#else
#define TAG1         (1ULL << 63)
#define TAG2         (1ULL << 62)
#endif
#define TAG_VALUE(v, tag) ((v) |  tag)
#define IS_TAGGED(v, tag) ((v) &  tag)
#define STRIP_TAG(v, tag) ((v) & ~tag)

#define DOES_NOT_EXIST 0
#define ERROR_INVALID_OPTION      (-1)
#define ERROR_INVALID_ARGUMENT    (-2)
#define ERROR_UNSUPPORTED_FEATURE (-3)
#define ERROR_TXN_NOT_RUNNING     (-4)

#define VOLATILE_DEREF(x) (*((volatile typeof(x))(x)))

typedef unsigned long long uint64_t;
typedef unsigned int       uint32_t;
typedef unsigned short     uint16_t;
typedef unsigned char      uint8_t;

typedef size_t markable_t;

static inline uint64_t rdtsc (void) {
    unsigned l, u;
    __asm__ __volatile__("rdtsc" : "=a" (l), "=d" (u));
    return ((uint64_t)u << 32) | l;
}

#include "lwt.h"
#endif //COMMON_H
