#pragma once

// Approximate and exact Riemann solvers for the 1D Euler equations.

#include "aderweno/euler1d.hpp"
#include "aderweno/checks.hpp"

// ---- Approximate solvers -----------------------------------------------

// Lax-Friedrichs numerical flux.
Physical laxFriedrichsFlux(const Conserved& UL, const Conserved& UR);

// HLL numerical flux.
Physical hllFlux(const Conserved& UL, const Conserved& UR);

// HLLC numerical flux.
Physical hllcFlux(const Conserved& UL, const Conserved& UR);

// ---- Exact solver ------------------------------------------------------

double fk(double pStar, double vk, double rhok, double pk);

double dfkDp(double pStar, double vk, double rhok, double pk);

double solvePStar(double vL, double vR, double rhoL, double pL,
                  double rhoR, double pR);

double calcVStar(double pStar, double vL, double rhoL, double pL,
                 double vR,  double rhoR, double pR);

Physical exactFlux(const Conserved& UL, const Conserved& UR);

// Exact Riemann state at the interface.
struct ExactRiemannState {
    double rho_k_star;
    double v_k_star;
    double p_star;
};

ExactRiemannState determine_interface_state(
    double p_star, double v_star,
    double vL, double vR,
    double rhoL, double pL,
    double rhoR, double pR);