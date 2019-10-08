/*
 * $Id: eps.h 598 2006-12-13 11:12:09Z mbec $
 * Declare the Encapsulated PostScript pseudo-engine for GIST.
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

#ifndef EPS_H
#define EPS_H

#include "gist.h"

extern Engine *EPSPreview(Engine *engine, char *file);

extern int epsFMbug;

#endif
