#pragma once

// Data structures and primitive operations for the 1D Euler equations.

#include "aderweno/eos.hpp"

struct Conserved {
    double rho; // mass density
    double mom; // momentum density (= rho * u)
    double E;   // total energy density
};

struct Primitive {
    double rho; // mass density
    double u;   // velocity
    double p;   // pressure
};

struct Physical {
    double fluxRho; // mass flux
    double fluxMom; // momentum flux
    double fluxE;   // energy flux
};

Primitive conservedToPrimitive(const Conserved& U);

Conserved primitiveToConserved(const Primitive& W);

Physical physicalFlux(const Conserved& U);

double maxSignalSpeed(const Conserved& U);