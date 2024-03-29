/*
 * $Id: cursors.c 598 2006-12-13 11:12:09Z mbec $
 * p_cursor for MS Windows
 */
/* Copyright (c) 2005, The Regents of the University of California.
 * All rights reserved.
 * This file is part of yorick (http://yorick.sourceforge.net).
 * Read the accompanying LICENSE file for details.
 */

/* is this really necessary to get OCR_NORMAL?? (==32512) */
#define OEMRESOURCE

#include "playw.h"

/* need to create P_S, P_E, P_W, P_ROTATE, P_DEATH, P_HAND cursors
 * -- may as well do P_N as well for consistent look
 *
 * notes:
 * (1) the 326-byte \windows\cursors\*.cur files are 32x32 bitmaps
 *     stored most significant bit first, least significant byte first,
 *     top-to-bottom order
 * (2) SM_CXCURSOR = SM_CYCURSOR = 32 on my Win95 box
 * (3) AND mask: 0 where cursor drawn, 1 where not
 * (4) XOR mask: 0 black/screen, 1 white/invert  (where AND bit 0/1)
 * (5) CreateBitmap documentation states that each scan line
 *     of a bitmap should be word (2-byte) aligned
 */

typedef struct w_curshape w_curshape;
struct w_curshape {
  int xhot, yhot;
  unsigned char amsk[32], xmsk[32];
};

static w_curshape w_narrow = {
  7, 1,
  { 0xfe, 0xff, 0xfc, 0x7f, 0xf8, 0x3f, 0xf0, 0x1f,
    0xe0, 0x0f, 0xe0, 0x0f, 0xf8, 0x3f, 0xf8, 0x3f,
    0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f,
    0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f },
  { 0x01, 0x00, 0x02, 0x80, 0x04, 0x40, 0x08, 0x20,
    0x10, 0x10, 0x1d, 0x70, 0x05, 0x40, 0x05, 0x40,
    0x05, 0x40, 0x05, 0x40, 0x05, 0x40, 0x05, 0x40,
    0x05, 0x40, 0x05, 0x40, 0x05, 0x40, 0x05, 0x40 } };

static w_curshape w_sarrow = {
  7, 14,
  { 0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f,
    0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f,
    0xf8, 0x3f, 0xf8, 0x3f, 0xe0, 0x0f, 0xe0, 0x0f,
    0xf0, 0x1f, 0xf8, 0x3f, 0xfc, 0x7f, 0xfe, 0xff },
  { 0x05, 0x40, 0x05, 0x40, 0x05, 0x40, 0x05, 0x40,
    0x05, 0x40, 0x05, 0x40, 0x05, 0x40, 0x05, 0x40,
    0x05, 0x40, 0x05, 0x40, 0x1d, 0x70, 0x10, 0x10,
    0x08, 0x20, 0x04, 0x40, 0x02, 0x80, 0x01, 0x00 } };

static w_curshape w_earrow = {
  14, 7,
  { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf,
    0xff, 0xc7, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x03, 0xff, 0xc7, 0xff, 0xcf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
    0x00, 0x28, 0xff, 0xe4, 0x00, 0x02, 0xff, 0xe1,
    0x00, 0x02, 0xff, 0xe4, 0x00, 0x28, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

static w_curshape w_warrow = {
  1, 7,
  { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff,
    0xe3, 0xff, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x80, 0x00, 0xc0, 0x00, 0xe3, 0xff, 0xf3, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00,
    0x14, 0x00, 0x27, 0xff, 0x40, 0x00, 0x87, 0xff,
    0x40, 0x00, 0x27, 0xff, 0x14, 0x00, 0x0c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

static w_curshape w_rotate = {
  7, 7,
  { 0x38, 0x1f, 0x10, 0x0f, 0x00, 0x07, 0x00, 0x03,
    0x03, 0xe3, 0x00, 0xf3, 0x00, 0xff, 0x00, 0xff,
    0xff, 0x00, 0xff, 0x00, 0xcf, 0x80, 0xc7, 0xc0,
    0xc0, 0x00, 0xe0, 0x00, 0xf0, 0x08, 0xf8, 0x1c },
  { 0xc7, 0xe0, 0xa8, 0x10, 0x90, 0x08, 0x83, 0xe4,
    0xb4, 0x14, 0xb3, 0x0c, 0x81, 0x00, 0xff, 0x00,
    0x00, 0xff, 0x00, 0x81, 0x30, 0x4d, 0x28, 0x2d,
    0x27, 0xc1, 0x10, 0x09, 0x08, 0x15, 0x07, 0xe3 } };

static w_curshape w_death = {
  7, 11,
  { 0xf0, 0x3f, 0xe0, 0x1f, 0xc0, 0x0f, 0x80, 0x07,
    0x80, 0x07, 0xc0, 0x0f, 0xe0, 0x1f, 0x70, 0x3e,
    0x70, 0x38, 0x30, 0x30, 0x08, 0x63, 0x87, 0x87,
    0xf8, 0x7f, 0x80, 0x1c, 0x00, 0x00, 0x0f, 0xc1 },
  { 0x08, 0x40, 0x10, 0x20, 0x20, 0x10, 0x4c, 0xc8,
    0x4c, 0xc8, 0x20, 0x10, 0x10, 0x20, 0x88, 0x41,
    0x08, 0x43, 0x48, 0x49, 0xb4, 0x94, 0x40, 0x08,
    0x00, 0x00, 0x60, 0x01, 0x0f, 0xc1, 0x70, 0x3a } };

static w_curshape w_hand = {
  3, 2,
  { 0xfe, 0x7f, 0xe4, 0x0f, 0xc0, 0x07, 0xc0, 0x05,
    0xe0, 0x00, 0xe0, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x80, 0x01, 0xc0, 0x01, 0xc0, 0x03,
    0xe0, 0x03, 0xf0, 0x07, 0xf8, 0x07, 0xf8, 0x07 },
  { 0x00, 0x00, 0x01, 0x80, 0x19, 0xb0, 0x19, 0xb0,
    0x0d, 0xb2, 0x0d, 0xb6, 0x17, 0xf6, 0x67, 0xfe,
    0x77, 0xfc, 0x3f, 0xfc, 0x1f, 0xfc, 0x1f, 0xf8,
    0x0f, 0xf8, 0x07, 0xf0, 0x03, 0xf0, 0x03, 0xf0 } };

static w_curshape *w_curs[7] = {
  &w_narrow, &w_sarrow, &w_earrow, &w_warrow, &w_rotate, &w_death, &w_hand };
static unsigned char *w_cursbits = 0;

HCURSOR
w_cursor(int cursor)
{
  HCURSOR c = 0;
  int i = cursor - 3;
  if (i>3) {
    if (i>6) i -= 3;
    else i -= 7;
  }
  if (i>=0 && i<7) {
    w_curshape *cs = w_curs[i];
    int w = GetSystemMetrics(SM_CXCURSOR);    /* bits per scan line */
    int h = GetSystemMetrics(SM_CYCURSOR);  /* number of scan lines */
    int wb = ((w+15)/16)*2;        /* number of bytes per scan line */
    unsigned char *and_msk = w_cursbits, *xor_msk;
    int j, k;
    w_cursbits = 0;
    if (and_msk) HeapFree(GetProcessHeap(), 0, and_msk);
    w_cursbits = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS,
                          2*wb*h);
    and_msk = w_cursbits;
    xor_msk = and_msk + wb*h;
    for (j=k=0 ; j<h ; j++,k+=wb) {
      if (j < 16) {
        for (i=0 ; i<wb ; i++) {
          if (i<2) {
            and_msk[k+i] = cs->amsk[2*j+i];
            xor_msk[k+i] = cs->xmsk[2*j+i];
          } else {
            and_msk[k+i] = 0xff;
            xor_msk[k+i] = 0;
          }
        }
      } else {
        for (i=0 ; i<wb ; i++) {
          and_msk[k+i] = 0xff;
          xor_msk[k+i] = 0;
        }
      }
    }
    c = CreateCursor(w_app_instance, cs->xhot, cs->yhot, w, h,
                    and_msk, xor_msk);
    w_cursbits = 0;
    HeapFree(GetProcessHeap(), 0, and_msk);
  } else {
    c = LoadCursor(0, IDC_ARROW);
    /* c = LoadImage(0, MAKEINTRESOURCE(OCR_NORMAL),
     *              IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR); */
  }
  return c;
}
