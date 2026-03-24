#pragma once

// Second-order MUSCL-Hancock solver with slope limiting for the 1D Euler equations.

#include "aderweno/euler1d.hpp"
#include <vector>

namespace aderweno {

enum class LimiterType { Minmod, VanLeer, MC };

void musclHancockAdvance(std::vector<Conserved>& U,
                         double dx, double dt,
                         bool periodic = false,
                         LimiterType limiter = LimiterType::MC);

void musclHancockRun(std::vector<Conserved>& U,
                     double x0, double x1,
                     double Tfinal, double CFL,
                     bool periodic = false,
                     LimiterType limiter = LimiterType::MC);

}