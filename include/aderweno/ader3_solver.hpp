#pragma once

// Third-order ADER solver: WENO5 + CK order 2 + TT-GRP.

#include "aderweno/euler1d.hpp"
#include "aderweno/tt_grp.hpp"
#include <vector>

namespace aderweno {

void ader3Advance(std::vector<Conserved>& U, double dx, double dt,
                  bool periodic, const TTGRPOptions& opt = TTGRPOptions{});

void ader3Run(std::vector<Conserved>& U,
              double x0, double x1, double Tfinal, double CFL,
              bool periodic, const TTGRPOptions& opt = TTGRPOptions{});

}