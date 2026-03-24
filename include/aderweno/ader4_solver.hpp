#pragma once

// Fourth-order ADER solver: WENO7 + CK order 3 + TT-GRP.

#include "aderweno/euler1d.hpp"
#include "aderweno/tt_grp.hpp"
#include <vector>

namespace aderweno {

void ader4Advance(std::vector<Conserved>& U, double dx, double dt,
                  bool periodic, const TTGRPOptions& opt = TTGRPOptions{});

void ader4Run(std::vector<Conserved>& U,
              double x0, double x1, double Tfinal, double CFL,
              bool periodic, const TTGRPOptions& opt = TTGRPOptions{});

}