/*
 * $Id: uinbg.c 598 2006-12-13 11:12:09Z mbec $
 * foreground/background detection function (UNIX arcana)
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

#include "config.h"
#include "playu.h"

#ifndef NO_PROCS
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif

#include <sys/types.h>
extern pid_t tcgetpgrp(int fd);
/* POSIX and SYSV getpgrp prototype is:    pid_t getpgrp(void)
 * BSD4.3 is more like 2nd branch, where the parameter is the pid of the
 *   process whose process group is returned (pid=0 means this process)
 * - passing the parameter to the POSIX/SYSV function is harmless,
 *   while omitting the paramter to the BSD function is disastrous
 * - the only reason for the first branch is if sys/types.h has the
 *   POSIX prototype for getpgrp */
#ifdef USE_POSIX_GETPGRP
#undef USE_POSIX_GETPGRP
#define USE_POSIX_GETPGRP
extern pid_t getpgrp(void);
#else
#define USE_POSIX_GETPGRP 0
extern pid_t getpgrp(pid_t);
#endif
#endif

int
u_in_background(void)
{
#ifndef NO_PROCS
  /* if the process group of the controlling terminal for stdin (fd 0)
   *   does not match our process group, we are in the background, and
   *   any attempt to read stdin will generate a SIGTTIN signal
   * read the intro(2) and termio(4) man pages for more
   * (possibly easier to just handle SIGTTIN if it happens...) */
  pid_t tgid = tcgetpgrp(0);      /* controlling terminal process group */
  if (tgid>0) {
    pid_t pgid = getpgrp(USE_POSIX_GETPGRP);   /* get our process group */
    return (pgid!=tgid);
  }
#endif
  return 0;
}

#ifdef USE_TIOCGPGRP_IOCTL
#include USE_TIOCGPGRP_IOCTL
pid_t
tcgetpgrp(int fd)
{
  int tgid;
  if (ioctl(fd, TIOCGPGRP, &tgid)<0) return -1;
  else return tgid;
}
#endif
