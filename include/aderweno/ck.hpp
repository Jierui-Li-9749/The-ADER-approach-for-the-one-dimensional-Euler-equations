#pragma once

// Cauchy-Kovalewski procedure: spatial derivatives -> time derivatives for ADER3/4/5.

#include "aderweno/euler1d.hpp"

// ===================== Order 2 (for ADER3) =====================

struct CKInput {
    Conserved Q;      // Q(x0)
    Conserved Qx;     // dQ/dx
    Conserved Qxx;    // d²Q/dx²
};

struct CKOutput {
    Conserved Qt;     // dQ/dt
    Conserved Qtt;    // d²Q/dt²
};

CKOutput ck_euler_order2(const CKInput& in);

// ===================== Order 3 (for ADER4) =====================

struct CKInput3 {
    Conserved Q;
    Conserved Qx;
    Conserved Qxx;
    Conserved Qxxx;   // d³Q/dx³
};

struct CKOutput3 {
    Conserved Qt;
    Conserved Qtt;
    Conserved Qttt;   // d³Q/dt³
};

CKOutput3 ck_euler_order3(const CKInput3& in);

// ===================== Order 4 (for ADER5) =====================

struct CKInput4 {
    Conserved Q;
    Conserved Qx;
    Conserved Qxx;
    Conserved Qxxx;
    Conserved Qxxxx;  // d⁴Q/dx⁴
};

struct CKOutput4 {
    Conserved Qt;
    Conserved Qtt;
    Conserved Qttt;
    Conserved Qtttt;  // d⁴Q/dt⁴
};

CKOutput4 ck_euler_order4(const CKInput4& in);