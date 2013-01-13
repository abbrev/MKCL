/* -*- mode: c -*- */
/*
    mkcl.h -- Main headers for use and/or development of MKCL
*/
/*
    Copyright (c) 1984, Taiichi Yuasa and Masami Hagiya.
    Copyright (c) 1990, Giuseppe Attardi.
    Copyright (c) 2010-2013, Jean-Claude Beaudoin.

    MKCL is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    See file './Copyright' for full details.
*/

#ifndef MKCL_H
#define MKCL_H

#ifdef __MINGW32__
/* These defines have to be done before any system include. */
# define __USE_MINGW_ANSI_STDIO 1
# include <w32api.h>
# define WINVER WindowsXP /* Don't want to support below that. JCB */
# ifndef __MSVCRT_VERSION__
/*  High byte is the major version, low byte is the minor. */
#  if 0
#  define __MSVCRT_VERSION__ 0x0601 /* Don't want to support below that. JCB */
#  else
#  define __MSVCRT_VERSION__ 0x0700 /* Matches Windows XP */ /* Don't want to support below that. JCB */
#  endif
# endif
#endif

#include <sys/types.h>

#include <stddef.h>		/* NULL, ptrdiff_t */
#include <stdarg.h> 		/* va_list */
#include <setjmp.h> 		/* setjmp and buffers */
#include <errno.h>
#include <stdlib.h>


/* Microsoft VC++ does not have va_copy() */
#if defined(_MSC_VER) || !defined(va_copy)
# define va_copy(dst, src) \
   ((void) memcpy(&(dst), &(src), sizeof(va_list)))
#endif

#include <mkcl/config.h>

#ifdef MKCL_WINDOWS
# define WIN32_LEAN_AND_MEAN 1 /* Do not include winsock.h */
#ifndef WINVER
# define WINVER 0x0501 /* We require at least Windows XP or later. */
# define _WIN32_WINNT WINVER
#endif
# include <winsock2.h>
# include <windows.h>
# include <malloc.h> /* for alloca() */
typedef HANDLE mkcl_os_process_t;
typedef DWORD mkcl_exit_code_t;
typedef HANDLE mkcl_os_thread_t;
typedef HANDLE mkcl_os_mutex_ref;
# if defined(_MSC_VER) && (defined(WinVista) || defined(Win7))
typedef SRWLOCK mkcl_os_rwlock_ref; /* MingW does not support this yet it seems. JCB 2010/02/15 */
# else
typedef HANDLE mkcl_os_rwlock_ref;
# endif
#else /* def MKCL_WINDOWS */
# include <alloca.h> /* for alloca() */
# include <semaphore.h>
typedef pthread_t mkcl_os_thread_t;
typedef pthread_mutex_t * mkcl_os_mutex_ref;
typedef pthread_rwlock_t * mkcl_os_rwlock_ref;
typedef pid_t mkcl_os_process_t;
typedef int mkcl_exit_code_t;
#endif /* else def MKCL_WINDOWS */

#ifndef __GNUC__
# define mkcl_likely(expr) (expr)
# define mkcl_unlikely(expr) (expr)
# define mkcl_noreturn
#else
# define mkcl_likely(expr) __builtin_expect((expr), TRUE)
# define mkcl_unlikely(expr) __builtin_expect((expr), FALSE)
# define mkcl_noreturn __attribute__((noreturn))
# if (__GNUC__ < 4)
#  error MKCL expects GCC version 4.X.X or later
# endif
#endif


#include <mkcl/object.h>
#include <mkcl/number.h>
#include <mkcl/list.h>
#include <mkcl/external.h>
#include <mkcl/stacks.h>

#endif /* MKCL_H */
