/*
 * Copyright (C) 2011 Ludovic Courtes
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED. ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 */

/* Make sure 'MK_GC_INIT' can be called from threads other than the initial
 * thread.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifndef MK_GC_THREADS
# define MK_GC_THREADS
#endif

#define MK_GC_NO_THREAD_REDIRECTS 1
                /* Do not redirect thread creation and join calls.      */

#include "gc.h"

#ifdef MK_GC_PTHREADS
# include <pthread.h>
#else
# include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#ifdef MK_GC_PTHREADS
  static void *thread(void *arg)
#else
  static DWORD WINAPI thread(LPVOID arg)
#endif
{
  MK_GC_INIT();
  (void)MK_GC_MALLOC(123);
  (void)MK_GC_MALLOC(12345);
# ifdef MK_GC_PTHREADS
    return arg;
# else
    return (DWORD)(MK_GC_word)arg;
# endif
}

#include "private/gcconfig.h"

int main(void)
{
# ifdef MK_GC_PTHREADS
    int code;
    pthread_t t;
# else
    HANDLE t;
    DWORD thread_id;
# endif
# if !(defined(BEOS) || defined(MSWIN32) || defined(MSWINCE) \
       || defined(CYGWIN32) || defined(MK_GC_OPENBSD_UTHREADS) \
       || (defined(DARWIN) && !defined(NO_PTHREAD_GET_STACKADDR_NP)) \
       || (defined(LINUX) && !defined(NACL)) \
       || (defined(MK_GC_SOLARIS_THREADS) && !defined(_STRICT_STDC)) \
       || (!defined(STACKBOTTOM) && (defined(HEURISTIC1) \
          || (!defined(LINUX_STACKBOTTOM) && !defined(FREEBSD_STACKBOTTOM)))))
    /* MK_GC_INIT() must be called from main thread only. */
    MK_GC_INIT();
# endif
# ifdef MK_GC_PTHREADS
    if ((code = pthread_create (&t, NULL, thread, NULL)) != 0) {
      fprintf(stderr, "Thread creation failed %d\n", code);
      return 1;
    }
    if ((code = pthread_join (t, NULL)) != 0) {
      fprintf(stderr, "Thread join failed %d\n", code);
      return 1;
    }
# else
    t = CreateThread(NULL, 0, thread, 0, 0, &thread_id);
    if (t == NULL) {
      fprintf(stderr, "Thread creation failed %d\n", (int)GetLastError());
      return 1;
    }
    if (WaitForSingleObject(t, INFINITE) != WAIT_OBJECT_0) {
      fprintf(stderr, "Thread join failed %d\n", (int)GetLastError());
      CloseHandle(t);
      return 1;
    }
    CloseHandle(t);
# endif
  return 0;
}
