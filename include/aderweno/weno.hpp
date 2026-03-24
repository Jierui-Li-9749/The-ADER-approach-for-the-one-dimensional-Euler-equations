#pragma once

// WENO-DK reconstruction on a Legendre polynomial basis for the 1D Euler equations.

#include "aderweno/euler1d.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>

using VectOfDouble     = std::vector<double>;
using VectOfVectDouble = std::vector<VectOfDouble>;

enum class WenoBCType { Outflow, Periodic };

// Polynomial data at one side of a cell interface (value + spatial derivatives).
struct InterfacePoly {
    Conserved Q;      // cell-interface value
    Conserved Qx;     // first spatial derivative  (M >= 1)
    Conserved Qxx;    // second spatial derivative (M >= 2)
    Conserved Qxxx;   // third spatial derivative  (M >= 3)
    Conserved Qxxxx;  // fourth spatial derivative (M >= 4)
};

// Pre-allocated workspace to avoid per-step heap allocations.
struct WENOWorkspace {
    std::vector<Conserved>     Ubc_cons;
    VectOfVectDouble           Ubc_mat;
    std::vector<InterfacePoly> PolyL, PolyR;
};

class WENO1d {
public:
    explicit WENO1d(int polydegree, double dx, double epsilon = 1e-6, int qPower = 2);

    int    degree()       const { return m_M; }
    double dx()           const { return m_dx; }
    int    requiredGhost() const {
        if (m_M == 0) return 1;
        const int k = (m_M % 2 == 0) ? m_M / 2 : (m_M + 1) / 2;
        return 2 * k + 1;
    }

    void reconstruct_for_flux(
        const VectOfVectDouble& Ubc,
        int i_interface,
        VectOfVectDouble& U_WenoL,
        VectOfVectDouble& U_WenoR,
        int Nghost) const;

    void reconstruct_all_interfaces(
        const std::vector<Conserved>& U,
        std::vector<InterfacePoly>& PolyL,
        std::vector<InterfacePoly>& PolyR,
        WenoBCType bc) const;

    void reconstruct_all_interfaces(
        const std::vector<Conserved>& U,
        WenoBCType bc,
        WENOWorkspace& ws) const;

    WENOWorkspace alloc_workspace(int nx) const;

    static std::vector<Conserved> make_outflow_Ubc(const std::vector<Conserved>& U, int Nghost);
    static std::vector<Conserved> make_periodic_Ubc(const std::vector<Conserved>& U, int Nghost);
    static VectOfVectDouble       conserved_to_matrix(const std::vector<Conserved>& U);

    static void fill_periodic_Ubc(const std::vector<Conserved>& U, int Nghost,
                                   std::vector<Conserved>& Ubc);
    static void fill_outflow_Ubc(const std::vector<Conserved>& U, int Nghost,
                                  std::vector<Conserved>& Ubc);
    static void fill_matrix(const std::vector<Conserved>& Ubc, VectOfVectDouble& mat);

private:
    void getStencil(const VectOfVectDouble&, int, VectOfVectDouble&, int) const;
    void reconstructAtInterface(const VectOfDouble&, const VectOfDouble&,
                                VectOfDouble&, VectOfDouble&) const;
    void computeWeights(const VectOfDouble&, const VectOfDouble&,
                        VectOfDouble&, VectOfDouble&) const;
    void setCoefficients();

    double m_dx      = 0.0;
    int    m_M       = 0;
    int    m_TotalStencilsize = 1;
    int    m_PolyStencilsize  = 1;
    double m_epsilon = 1e-6;
    int    m_qPower  = 2;

    std::vector<VectOfVectDouble> m_CMatsL;
    std::vector<VectOfVectDouble> m_CMatsR;
    std::vector<VectOfVectDouble> m_BMats;
    VectOfDouble m_optWeightsL;
    VectOfDouble m_optWeightsR;
};