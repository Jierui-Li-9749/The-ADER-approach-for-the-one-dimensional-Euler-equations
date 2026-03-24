#pragma once

// Physical and numerical constants for the ADER-WENO solver.

extern const double Gamma;        // Specific heat ratio for ideal gas
extern const double RhoMin;       // Minimum allowable density
extern const double PMin;         // Minimum allowable pressure
extern const double PMax;         // Upper bound on Newton-Raphson p* iterates
extern const int    NewtonMaxIter;// Maximum Newton iterations for exact Riemann solver
extern const double NewtonTol;    // Convergence tolerance for p* iteration
extern const double WenoEpsilon;  // WENO smoothness indicator regularisation
extern const int    WenoQPower;   // Exponent in WENO-JS weight formula