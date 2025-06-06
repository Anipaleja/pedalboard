/*
 * Copyright (c) 2003, 2007-14 Matteo Frigo
 * Copyright (c) 2003, 2007-14 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Tue Sep 14 10:44:24 EDT 2021 */

#include "dft/codelet-dft.h"

#if defined(ARCH_PREFERS_FMA) || defined(ISA_EXTENSION_PREFERS_FMA)

/* Generated by: ../../../genfft/gen_notw.native -fma -compact -variables 4
 * -pipeline-latency 4 -n 6 -name n1_6 -include dft/scalar/n.h */

/*
 * This function contains 36 FP additions, 12 FP multiplications,
 * (or, 24 additions, 0 multiplications, 12 fused multiply/add),
 * 23 stack variables, 2 constants, and 24 memory accesses
 */
#include "dft/scalar/n.h"

static void n1_6(const R *ri, const R *ii, R *ro, R *io, stride is, stride os,
                 INT v, INT ivs, INT ovs) {
  DK(KP866025403, +0.866025403784438646763723170752936183471402627);
  DK(KP500000000, +0.500000000000000000000000000000000000000000000);
  {
    INT i;
    for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, ro = ro + ovs,
        io = io + ovs, MAKE_VOLATILE_STRIDE(24, is),
        MAKE_VOLATILE_STRIDE(24, os)) {
      E T3, Tb, Tp, Tx, T6, Tc, T9, Td, Ta, Te, Ti, Tu, Tl, Tv, Tq;
      E Ty;
      {
        E T1, T2, Tn, To;
        T1 = ri[0];
        T2 = ri[WS(is, 3)];
        T3 = T1 - T2;
        Tb = T1 + T2;
        Tn = ii[0];
        To = ii[WS(is, 3)];
        Tp = Tn - To;
        Tx = Tn + To;
      }
      {
        E T4, T5, T7, T8;
        T4 = ri[WS(is, 2)];
        T5 = ri[WS(is, 5)];
        T6 = T4 - T5;
        Tc = T4 + T5;
        T7 = ri[WS(is, 4)];
        T8 = ri[WS(is, 1)];
        T9 = T7 - T8;
        Td = T7 + T8;
      }
      Ta = T6 + T9;
      Te = Tc + Td;
      {
        E Tg, Th, Tj, Tk;
        Tg = ii[WS(is, 2)];
        Th = ii[WS(is, 5)];
        Ti = Tg - Th;
        Tu = Tg + Th;
        Tj = ii[WS(is, 4)];
        Tk = ii[WS(is, 1)];
        Tl = Tj - Tk;
        Tv = Tj + Tk;
      }
      Tq = Ti + Tl;
      Ty = Tu + Tv;
      ro[WS(os, 3)] = T3 + Ta;
      io[WS(os, 3)] = Tp + Tq;
      ro[0] = Tb + Te;
      io[0] = Tx + Ty;
      {
        E Tf, Tm, Tr, Ts;
        Tf = FNMS(KP500000000, Ta, T3);
        Tm = Ti - Tl;
        ro[WS(os, 5)] = FNMS(KP866025403, Tm, Tf);
        ro[WS(os, 1)] = FMA(KP866025403, Tm, Tf);
        Tr = FNMS(KP500000000, Tq, Tp);
        Ts = T9 - T6;
        io[WS(os, 1)] = FMA(KP866025403, Ts, Tr);
        io[WS(os, 5)] = FNMS(KP866025403, Ts, Tr);
      }
      {
        E Tt, Tw, Tz, TA;
        Tt = FNMS(KP500000000, Te, Tb);
        Tw = Tu - Tv;
        ro[WS(os, 2)] = FNMS(KP866025403, Tw, Tt);
        ro[WS(os, 4)] = FMA(KP866025403, Tw, Tt);
        Tz = FNMS(KP500000000, Ty, Tx);
        TA = Td - Tc;
        io[WS(os, 2)] = FNMS(KP866025403, TA, Tz);
        io[WS(os, 4)] = FMA(KP866025403, TA, Tz);
      }
    }
  }
}

static const kdft_desc desc = {6, "n1_6", {24, 0, 12, 0}, &GENUS, 0, 0, 0, 0};

void X(codelet_n1_6)(planner *p) { X(kdft_register)(p, n1_6, &desc); }

#else

/* Generated by: ../../../genfft/gen_notw.native -compact -variables 4
 * -pipeline-latency 4 -n 6 -name n1_6 -include dft/scalar/n.h */

/*
 * This function contains 36 FP additions, 8 FP multiplications,
 * (or, 32 additions, 4 multiplications, 4 fused multiply/add),
 * 23 stack variables, 2 constants, and 24 memory accesses
 */
#include "dft/scalar/n.h"

static void n1_6(const R *ri, const R *ii, R *ro, R *io, stride is, stride os,
                 INT v, INT ivs, INT ovs) {
  DK(KP866025403, +0.866025403784438646763723170752936183471402627);
  DK(KP500000000, +0.500000000000000000000000000000000000000000000);
  {
    INT i;
    for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, ro = ro + ovs,
        io = io + ovs, MAKE_VOLATILE_STRIDE(24, is),
        MAKE_VOLATILE_STRIDE(24, os)) {
      E T3, Tb, Tq, Tx, T6, Tc, T9, Td, Ta, Te, Ti, Tu, Tl, Tv, Tr;
      E Ty;
      {
        E T1, T2, To, Tp;
        T1 = ri[0];
        T2 = ri[WS(is, 3)];
        T3 = T1 - T2;
        Tb = T1 + T2;
        To = ii[0];
        Tp = ii[WS(is, 3)];
        Tq = To - Tp;
        Tx = To + Tp;
      }
      {
        E T4, T5, T7, T8;
        T4 = ri[WS(is, 2)];
        T5 = ri[WS(is, 5)];
        T6 = T4 - T5;
        Tc = T4 + T5;
        T7 = ri[WS(is, 4)];
        T8 = ri[WS(is, 1)];
        T9 = T7 - T8;
        Td = T7 + T8;
      }
      Ta = T6 + T9;
      Te = Tc + Td;
      {
        E Tg, Th, Tj, Tk;
        Tg = ii[WS(is, 2)];
        Th = ii[WS(is, 5)];
        Ti = Tg - Th;
        Tu = Tg + Th;
        Tj = ii[WS(is, 4)];
        Tk = ii[WS(is, 1)];
        Tl = Tj - Tk;
        Tv = Tj + Tk;
      }
      Tr = Ti + Tl;
      Ty = Tu + Tv;
      ro[WS(os, 3)] = T3 + Ta;
      io[WS(os, 3)] = Tq + Tr;
      ro[0] = Tb + Te;
      io[0] = Tx + Ty;
      {
        E Tf, Tm, Tn, Ts;
        Tf = FNMS(KP500000000, Ta, T3);
        Tm = KP866025403 * (Ti - Tl);
        ro[WS(os, 5)] = Tf - Tm;
        ro[WS(os, 1)] = Tf + Tm;
        Tn = KP866025403 * (T9 - T6);
        Ts = FNMS(KP500000000, Tr, Tq);
        io[WS(os, 1)] = Tn + Ts;
        io[WS(os, 5)] = Ts - Tn;
      }
      {
        E Tt, Tw, Tz, TA;
        Tt = FNMS(KP500000000, Te, Tb);
        Tw = KP866025403 * (Tu - Tv);
        ro[WS(os, 2)] = Tt - Tw;
        ro[WS(os, 4)] = Tt + Tw;
        Tz = FNMS(KP500000000, Ty, Tx);
        TA = KP866025403 * (Td - Tc);
        io[WS(os, 2)] = Tz - TA;
        io[WS(os, 4)] = TA + Tz;
      }
    }
  }
}

static const kdft_desc desc = {6, "n1_6", {32, 4, 4, 0}, &GENUS, 0, 0, 0, 0};

void X(codelet_n1_6)(planner *p) { X(kdft_register)(p, n1_6, &desc); }

#endif
