#pragma once

// TT-GRP interface flux computation for ADER3, ADER4, and ADER5 solvers.

#include "aderweno/euler1d.hpp"
#include "aderweno/weno.hpp"

enum class TTRiemannFluxType { Exact, LaxFriedrichs, HLL, HLLC };

struct TTGRPOptions {
    TTRiemannFluxType flux_type    = TTRiemannFluxType::Exact;
    bool              use_exact_q0 = true; // use exact Riemann solver for leading Godunov state
};

Conserved exactInterfaceStateQ0(const InterfacePoly& L, const InterfacePoly& R);

Conserved predictStateTaylor2(const InterfacePoly& P, double t);

Conserved predictStateTaylor3(const InterfacePoly& P, double t);

Conserved predictStateTaylor4(const InterfacePoly& P, double t);

Physical ttGrpFluxAder3(const InterfacePoly& L, const InterfacePoly& R,
                        double dt, const TTGRPOptions& opt = TTGRPOptions{});

Physical ttGrpFluxAder4(const InterfacePoly& L, const InterfacePoly& R,
                        double dt, const TTGRPOptions& opt = TTGRPOptions{});

Physical ttGrpFluxAder5(const InterfacePoly& L, const InterfacePoly& R,
                        double dt, const TTGRPOptions& opt = TTGRPOptions{});