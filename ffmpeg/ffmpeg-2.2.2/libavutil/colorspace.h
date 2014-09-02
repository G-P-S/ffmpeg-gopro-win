/*
 * Colorspace conversion defines
 * Copyright (c) 2001, 2002, 2003 Fabrice Bellard
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * Various defines for YUV<->RGB conversion
 */

#ifndef AVUTIL_COLORSPACE_H
#define AVUTIL_COLORSPACE_H

#define SCALEBITS 10
#define ONE_HALF  (1 << (SCALEBITS - 1))
#define FIX(x)    ((int) ((x) * (1<<SCALEBITS) + 0.5))

#define YUV601_TO_RGB1_CCIR(cb1, cr1)\
{\
    cb = (cb1) - 128;\
    cr = (cr1) - 128;\
    r_add = FIX(1.59600) * cr + ONE_HALF;\
    g_add = - FIX(0.39100) * cb - FIX(0.81300) * cr + \
            ONE_HALF;\
    b_add = FIX(2.01800) * cb + ONE_HALF;\
}

#define YUV601_TO_RGB2_CCIR(r, g, b, y1)\
{\
    y = ((y1) - 16) * FIX(255.0/219.0);\
    r = cm[(y + r_add) >> SCALEBITS];\
    g = cm[(y + g_add) >> SCALEBITS];\
    b = cm[(y + b_add) >> SCALEBITS];\
}

#define YUV601_TO_RGB1(cb1, cr1)\
{\
    cb = (cb1) - 128;\
    cr = (cr1) - 128;\
    r_add = FIX(1.37100) * cr + ONE_HALF;\
    g_add = - FIX(0.33600) * cb - FIX(0.69800) * cr + ONE_HALF;\
    b_add = FIX(1.73200) * cb + ONE_HALF;\
}



#define YUV_TO_RGB1_CCIR(cb1, cr1)\
{\
    cb = (cb1) - 128;\
    cr = (cr1) - 128;\
    r_add = FIX(1.79300) * cr + ONE_HALF;\
    g_add = - FIX(0.21300) * cb - FIX(0.53400) * cr + \
            ONE_HALF;\
    b_add = FIX(2.115000) * cb + ONE_HALF;\
}

#define YUV_TO_RGB2_CCIR(r, g, b, y1)\
{\
    y = ((y1) - 16) * FIX(255.0/219.0);\
    r = cm[(y + r_add) >> SCALEBITS];\
    g = cm[(y + g_add) >> SCALEBITS];\
    b = cm[(y + b_add) >> SCALEBITS];\
}

#define YUV_TO_RGB1(cb1, cr1)\
{\
    cb = (cb1) - 128;\
    cr = (cr1) - 128;\
    r_add = FIX(1.54000) * cr + ONE_HALF;\
    g_add = - FIX(0.18300) * cb - FIX(0.45900) * cr + ONE_HALF;\
    b_add = FIX(1.81600) * cb + ONE_HALF;\
}


#define YUV_TO_RGB2(r, g, b, y1)\
{\
    y = (y1) << SCALEBITS;\
    r = cm[(y + r_add) >> SCALEBITS];\
    g = cm[(y + g_add) >> SCALEBITS];\
    b = cm[(y + b_add) >> SCALEBITS];\
}

#define Y_CCIR_TO_JPEG(y)\
 cm[((y) * FIX(255.0/219.0) + (ONE_HALF - 16 * FIX(255.0/219.0))) >> SCALEBITS]

#define Y_JPEG_TO_CCIR(y)\
 (((y) * FIX(219.0/255.0) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

#define C_CCIR_TO_JPEG(y)\
 cm[(((y) - 128) * FIX(127.0/112.0) + (ONE_HALF + (128 << SCALEBITS))) >> SCALEBITS]

/* NOTE: the clamp is really necessary! */
static inline int C_JPEG_TO_CCIR(int y) {
    y = (((y - 128) * FIX(112.0/127.0) + (ONE_HALF + (128 << SCALEBITS))) >> SCALEBITS);
    if (y < 16)
        y = 16;
    return y;
}


#define RGB_TO_Y601(r, g, b) \
((FIX(0.29900) * (r) + FIX(0.58700) * (g) + \
  FIX(0.11400) * (b) + ONE_HALF) >> SCALEBITS)

// old 601 calcuations were wrong
#define RGB_TO_U601(r1, g1, b1, shift)\
(((- FIX(0.17200) * r1 - FIX(0.33900) * g1 +         \
     FIX(0.51100) * b1 + (ONE_HALF << shift) - 1) >> (SCALEBITS + shift)) + 128)

// old 601 calcuations were wrong
#define RGB_TO_V601(r1, g1, b1, shift)\
(((FIX(0.51100) * r1 - FIX(0.42800) * g1 -           \
   FIX(0.08300) * b1 + (ONE_HALF << shift) - 1) >> (SCALEBITS + shift)) + 128)

#define RGB_TO_Y_CCIR601(r, g, b) \
((FIX(0.25700) * (r) + FIX(0.50400) * (g) + \
  FIX(0.09800) * (b) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

// old 601 calcuations were wrong
#define RGB_TO_U_CCIR601(r1, g1, b1, shift)\
(((- FIX(0.14800) * r1 - FIX(0.29100) * g1 +         \
     FIX(0.43900) * b1 + (ONE_HALF << shift) - 1) >> (SCALEBITS + shift)) + 128)

// old 601 calcuations were wrong
#define RGB_TO_V_CCIR601(r1, g1, b1, shift)\
(((FIX(0.43900) * r1 - FIX(0.36800) * g1 -           \
   FIX(0.07100) * b1 + (ONE_HALF << shift) - 1) >> (SCALEBITS + shift)) + 128)
   
   
   
#define RGB_TO_Y(r, g, b) \
((FIX(0.21300) * (r) + FIX(0.71500) * (g) + \
  FIX(0.07200) * (b) + ONE_HALF) >> SCALEBITS)

#define RGB_TO_U(r1, g1, b1, shift)\
(((- FIX(0.11700) * r1 - FIX(0.39400) * g1 +         \
     FIX(0.51100) * b1 + (ONE_HALF << shift) - 1) >> (SCALEBITS + shift)) + 128)

#define RGB_TO_V(r1, g1, b1, shift)\
(((FIX(0.51100) * r1 - FIX(0.46400) * g1 -           \
   FIX(0.04700) * b1 + (ONE_HALF << shift) - 1) >> (SCALEBITS + shift)) + 128)

#define RGB_TO_Y_CCIR(r, g, b) \
((FIX(0.18300) * (r) + FIX(0.61400) * (g) + \
  FIX(0.06200) * (b) + (ONE_HALF + (16 << SCALEBITS))) >> SCALEBITS)

#define RGB_TO_U_CCIR(r1, g1, b1, shift)\
(((- FIX(0.10100) * r1 - FIX(0.33800) * g1 +         \
     FIX(0.43900) * b1 + (ONE_HALF << shift) - 1) >> (SCALEBITS + shift)) + 128)

#define RGB_TO_V_CCIR(r1, g1, b1, shift)\
(((FIX(0.43900) * r1 - FIX(0.39900) * g1 -           \
   FIX(0.04000) * b1 + (ONE_HALF << shift) - 1) >> (SCALEBITS + shift)) + 128)

#endif /* AVUTIL_COLORSPACE_H */
