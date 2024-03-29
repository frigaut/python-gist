/*
 * $Id: resource.c 598 2006-12-13 11:12:09Z mbec $
 * X11 runtime resources
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

#include "config.h"
#include "playx.h"

char *x_xfont = 0;       /* boldfont, font, Font */
char *x_foreground = 0;  /* foreground, Foreground */
char *x_background = 0;  /* background, Background */
char *x_guibg = 0;       /* guibg */
char *x_guifg = 0;       /* guifg */
char *x_guihi = 0;       /* guihi */
char *x_guilo = 0;       /* guilo */
