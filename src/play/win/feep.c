/*
 * $Id: feep.c 598 2006-12-13 11:12:09Z mbec $
 * p_feep for MS Windows
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

#include "playw.h"

/* ARGSUSED */
void
p_feep(p_win *w)
{
  MessageBeep(MB_OK);
}
