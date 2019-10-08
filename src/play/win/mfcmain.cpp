/*
 * $Id: mfcmain.cpp 598 2006-12-13 11:12:09Z mbec $
 * MFC main program stub
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

extern "C" {
  extern int on_launch(int argc, char *argv[]);
}
#include "mfcapp.h"

mfc_boss the_boss(on_launch);
