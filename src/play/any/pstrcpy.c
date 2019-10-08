/*
 * $Id: pstrcpy.c 598 2006-12-13 11:12:09Z mbec $
 * strcpy that p_mallocs its destination
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

#include "config.h"
#include "pstdlib.h"
#include <string.h>

char *
p_strcpy(const char *s)
{
  if (s) {
    char *d = p_malloc(strlen(s)+1);
    strcpy(d, s);
    return d;
  } else {
    return 0;
  }
}
