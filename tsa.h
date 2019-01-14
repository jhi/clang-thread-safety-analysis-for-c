#ifndef TSA_H
#define TSA_H

/*
 * Copyright 2018 Jarkko Hietaniemi <jhi@iki.fi>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* http://clang.llvm.org/docs/ThreadSafetyAnalysis.html
 *
 * TSA is available since clang 3.6-ish.
 */
#ifdef __clang__
#  define TSA(x)   __attribute__((x))
#else
#  define TSA(x)   /* No TSA, make TSA attributes no-ops. */
#endif

/* TSA_CAPABILITY() is used to annotate typedefs:
 *
 * typedef pthread_mutex_t TSA_CAPABILITY("mutex") tsa_mutex;
 */
#define TSA_CAPABILITY(x) TSA(capability(x))

/* TSA_GUARDED_BY() is used to annotate global variables,
 * the data is guarded:
 *
 * Foo foo TSA_GUARDED_BY(mutex);
 */
#define TSA_GUARDED_BY(x) TSA(guarded_by(x))

/* TSA_PT_GUARDED_BY() is used to annotate global pointers, the data
 * behind the pointer is guarded.
 *
 * Foo* ptr TSA_PT_GUARDED_BY(mutex);
 */
#define TSA_PT_GUARDED_BY(x) TSA(pt_guarded_by(x))

/* The TSA_REQUIRES() is used to annotate functions: the caller of the
 * function MUST hold the resource, the function will NOT release it.
 *
 * void Foo() TSA_REQUIRES(mutex);
 */
#define TSA_REQUIRES(x) TSA(requires_capability(x))

/* TSA_EXCLUDES() is used to annotate functions: the caller of the
 * function MUST NOT hold resource, the function first acquires the
 * resource, and then releases it.
 *
 * void Foo() TSA_EXCLUDES(mutex);
 */
#define TSA_EXCLUDES(x) TSA(locks_excluded(x))

/* TSA_ACQUIRE() is used to annotate functions: the caller of the
 * function MUST NOT hold the resource, the function will acquire the
 * resource, but NOT release it.
 *
 * void Foo() TSA_ACQUIRE(mutex);
 */
#define TSA_ACQUIRE(x) TSA(acquire_capability(x))

/* TSA_RELEASE() is used to annotate functions: the caller of the
 * function MUST hold the resource, but the function will then release it.
 *
 * void Foo() TSA_RELEASE(mutex);
 */
#define TSA_RELEASE(x) TSA(release_capability(x))

/* TSA_NO_TSA is used to annotate functions.  Use only when you need to.
 *
 * void Foo() TSA_NO_TSA;
 */
#define TSA_NO_TSA TSA(no_thread_safety_analysis)

#include <pthread.h>

typedef pthread_mutex_t TSA_CAPABILITY("mutex") tsa_mutex;

/* In real use the implementation of the mutex lock and unlock
 * wrappers probably should be in a single source code file,
 * not like here as C99 style static inlines.
 *
 * The TSA_NO_TSA is needed because for these this is C, not C++,
 * we cannot annotate the methods of a class. */
static inline int tsa_mutex_lock(tsa_mutex* mutex) TSA_ACQUIRE(*mutex) TSA_NO_TSA {
    return pthread_mutex_lock(mutex);
}
static inline int tsa_mutex_unlock(tsa_mutex* mutex) TSA_RELEASE(*mutex) TSA_NO_TSA {
    return pthread_mutex_unlock(mutex);
}

#endif /* #ifndef TSA_H */
