#pragma once

// First-order Godunov solver for the 1D Euler equations.

#include "aderweno/euler1d.hpp"
#include <vector>

namespace aderweno {

void godunovAdvance(std::vector<Conserved>& U,
                    double dx, double dt,
                    bool periodic = false);

void godunovRun(std::vector<Conserved>& U,
                double x0, double x1,
                double Tfinal, double CFL,
                bool periodic = false);

}