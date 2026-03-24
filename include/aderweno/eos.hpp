#pragma once

// Equation of State for a perfect gas: pressure and sound speed from conserved variables.

#include "aderweno/constants.hpp"

double pressure(double rho, double mom, double E);

double soundSpeed(double rho, double mom, double E);