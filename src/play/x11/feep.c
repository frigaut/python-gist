/*
 * $Id: feep.c 598 2006-12-13 11:12:09Z mbec $
 * p_feep for X11
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

#include "config.h"
#include "playx.h"

void
p_feep(p_win *w)
{
  if (w->s->xdpy->dpy) XBell(w->s->xdpy->dpy, 100);
}
