/*
 * $Id: pfill.c 598 2006-12-13 11:12:09Z mbec $
 * p_fill for MS Windows
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

#include "playw.h"

/* ARGSUSED */
void
p_fill(p_win *w, int convexity)
{
  int n = w_pt_count;
  HDC dc = w_getdc(w, 12);
  if (dc) {
    /* SetPolyFillMode(dc, ALTERNATE); */
    Polygon(dc, w_pt_list, n);
  }
}
