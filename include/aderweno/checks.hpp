#pragma once

// Validation and physical admissibility functions for the ADER-WENO solver.

#include "aderweno/euler1d.hpp"
#include "aderweno/constants.hpp"
#include <cmath>
#include <algorithm>

bool isValidRho(double rho);

bool isValidPressure(double p);

bool checkConserved(const Conserved& U);

bool isConverged(double oldPStar, double newPStar, double tolerance = 1e-6);

inline void enforcePhysical(Conserved& U)
{
    if (!std::isfinite(U.rho) || U.rho < RhoMin) U.rho = RhoMin;
    if (!std::isfinite(U.mom / U.rho)) U.mom = 0.0;
    const double eMin = 0.5 * U.mom * U.mom / U.rho + PMin / (Gamma - 1.0);
    if (!std::isfinite(U.E) || U.E < eMin) U.E = eMin;
}

inline Physical safeFlux(const Physical& fAder, const Physical& fHllc, double tol = 10.0)
{
    if (!std::isfinite(fAder.fluxRho) ||
        !std::isfinite(fAder.fluxMom) ||
        !std::isfinite(fAder.fluxE))
        return fHllc;

    auto close = [&](double fa, double fh) {
        return std::abs(fa - fh) <= tol * std::max({std::abs(fa), std::abs(fh), 1e-6});
    };

    if (close(fAder.fluxRho, fHllc.fluxRho) &&
        close(fAder.fluxMom, fHllc.fluxMom) &&
        close(fAder.fluxE,   fHllc.fluxE))
        return fAder;
    return fHllc;
}