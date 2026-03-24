#pragma once

// Finite volume update functions for the 1D Euler equations (Lax-Friedrichs, HLL, HLLC, exact).

#include "aderweno/euler1d.hpp"
#include <vector>

void setBoundaryConditions(std::vector<Conserved>& U);

void laxFriedrichsUpdate(std::vector<Conserved>& U, double dx, double dt);

void hllUpdate(std::vector<Conserved>& U, double dx, double dt);

void hllcUpdate(std::vector<Conserved>& U, double dx, double dt);

void exactUpdate(std::vector<Conserved>& U, double dx, double dt);